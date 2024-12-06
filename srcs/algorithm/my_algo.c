#include "network.h"

int my_algo(int **array);
t_node *get_next_node(t_node *network, int cur_group_id);
int is_grouping(t_node *network);
int search_start(t_node *network)
t_node *search_node_grouping(t_node *cur);
int search_group(t_node *network, int start);

int my_algo(int **array)
{
    t_node *network;
    int edge_count;
    int start;
    int i, j;

    network = input_network(array);
    if (!network)
    {
        printf("Error: can't create map\n");
        return (EXIT_FAILURE);
    }
    printf("start: %d\n",start);
    int ret = search_group(network, start);
    if (ret != EXIT_FAILURE)
    {
        printf("Error: can't search\n");
        // free_network(network);
        // return (EXIT_FAILURE);
    }
    print_network_group(network);
    free_network(network);
    return (EXIT_SUCCESS);
}
int search_start(t_node *network)
{
    t_node  *node;

    node = network;
    while (node)
    {
        if (node->connect_count == 1)
            return (node->name);
        node = node->next;
    }
    return (-1);
}
t_node *get_next_node(t_node *network, int cur_group_id)
{
    t_node *node = network;

    while (node)
    {
        if (node->group_id == -1)
        {
            for (int j = 0; j < node->connect_count; j++)
            {
                if (node->connected_node[j]->group_id == cur_group_id)
                    return node;
            }
        }
        node = node->next;
    }
    return NULL; // 未割り当てノードが見つからない場合
}


// グルーピングできてるか調べる関数　返り値 0:未終了 1:終了
int is_grouping(t_node *network)
{
    t_node *node = network;

    while (node)
    {
        if (node->group_id == -1)
            return 0; // グループ分けが未完了
        node = node->next;
    }
    return 1; // 全てのノードがグループに割り当て済み
}

t_node *search_node_grouping(t_node *cur)
{
    for (int i = 0; i < cur->connect_count; i++)
    {
        if (cur->connected_node[i]->group_id == -1)
            return cur->connected_node[i];
    }
    return NULL; // 未割り当てノードが見つからない場合
}

int search_group(t_node *network, int start)
{
    t_node *cur = search_node(network, start);
    if (!cur)
        return EXIT_FAILURE; // ノードが見つからない場合

    int count = 1;   // グループ内のノード数
    int cur_id = 1;  // 現在のグループID

    cur->group_id = cur_id; // 最初のノードをグループに割り当て

    while (!is_grouping(network)) // グループ分けが完了するまでループ
    {
        t_node *node = search_node_grouping(cur);
        if (!node)
        {
            cur = get_next_node(network, cur_id); // 別の未割り当てノードを探索
            if (!cur)
            {
                cur_id++; // 新しいグループを作成
                cur = get_next_node(network, -1); // 全体から次の未割り当てノードを探索
                if (!cur) break; // 未割り当てノードがない場合、終了
                cur->group_id = cur_id;
                count = 1;
            }
            continue;
        }

        node->group_id = cur_id; // ノードを現在のグループに割り当て
        count++;

        if (count == GROUP_MAX)
        {
            cur_id++; // グループが最大サイズに達したら次のグループへ
            count = 0;
        }
        cur = node; // 現在のノードを更新
    }
    return EXIT_SUCCESS;
}