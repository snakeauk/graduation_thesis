#include "test.h"

void    my_array_printf(int **array);
void    print_network_group(t_node *network);
void    print_network(t_node *network);

void    print_network(t_node *network)
{
    t_node  *node;
    int     count;
    int     i;

    node = network;
    while (node)
    {
        printf("===:%d:===\n", node->name);
        count = node->connect_count;
        for (i = 0; i < count; i++)
        {
            printf("|");
            if (i != count - 1)
                printf("\t");
            else
                printf("\n");
        }
        i = 0;
        while (node->connected_node[i])
        {
            printf("%d", node->connected_node[i]->name);
            if (i != count - 1)
                printf("\t");
            else
                printf("\n");
            i++;
        }
        printf("\n");

        printf("=====================\n\n\n");

        node = node->next;
    }
}

void    print_network_group(t_node *network)
{
    t_node  *node;
    int     count;
    int     i;

    node = network;
    while (node)
    {
        printf("%d:===group_id: %d\n", node->name, node->group_id);
        printf("\n\n");
        node = node->next;
    }
}

void    my_array_printf(int **array)
{
    int node[M];
    int index;

    index = 0;
    for (int i = 0; array[i] != NULL; i++)
    {
        int count = 0;
        for (int j = 0; j < M; j++)
        {
            if (array[i][j] == 1)
                count++;
            printf("%d ", array[i][j]);
        }
        printf("\n");
        node[index] = count;
        index++;
    }

    for (int i = 0; i < M; i++)
    {
        printf("%d:\t%d \n", i + 1, node[i]);
    }
}
