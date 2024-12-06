#include "network.h"

t_node *input_network(int **array); // networkを作る関数。array[N][N]
t_node *create_node(int **array, int name); // nodeを初期化する関数
t_node  *search_node(t_node *network, int name); // nameのノードを返す関数
int     count_connect_node(int *connect); // nodeに接続されているnodeの個数を返す関数。
void    free_network(t_node *network); // networkをfreeする関数、メモリリーク対策。

void free_network(t_node *network)
{
    t_node *current;
    t_node *next;

    current = network;
    while (current)
    {
        next = current->next;  // 次のノードを事前に保存
        if (current->connected_node)  // connected_nodeを解放
            free(current->connected_node);
        free(current);  // 現在のノードを解放
        current = next; // 次のノードに進む
    }
}

t_node *create_node(int **array, int name)
{
    t_node  *node;

    node = (t_node *)malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    node->name = name;
    node->group_id = 0;
    node->array = array[name];
    node->connected_node = NULL;
    node->next = NULL;
    return (node);
}

int count_connect_node(int *connect)
{
    int count;
    int i;

    count = 0;
    for (i = 0; i < N; i++)
    {
        if (connect[i] == 1)
            count++;
    }
    return (count);
}

t_node  *search_node(t_node *network, int name)
{
    t_node *node;

    node = network;
    while (node)
    {
        if (node->name == name)
            return (node);
        node = node->next;
    }
    return (NULL);
}

t_node *input_network(int **array)
{
    t_node  *network;
    t_node  *last;
    t_node  *node;
    int     i;

    network = create_node(array, 0);
    if (!network)
        return (NULL);
    last = network;
    // create network
    for (i = 1; i < N; i++)
    {
        node = create_node(array, i);
        if (!node)
        {
            free_network(network);
            return (NULL);
        }
        last->next = node;
        last = node;
    }

    // chain network
    t_node  *current = network;
    int     cn_i;

    while (current)
    {
        current->connect_count = count_connect_node(current->array);
        current->connected_node = (t_node **)malloc(sizeof(t_node *) * (current->connect_count + 1));
        if (!current->connected_node)
        {
            perror("Error: create node:");
            free_network(network);
            return (NULL);
        }

        cn_i = 0;
        for (i = 0; i < N; i++)
        {
            if (current->array[i] == 1 && i != current->name)
            {
                current->connected_node[cn_i] = search_node(network, i);
                cn_i++;
            }
        }
        current->connected_node[cn_i] = NULL;

        current = current->next;
    }

    return (network);
}