#include "network.h"

int my_algo(int **array);
int search_start(int **array);
void    print_network(t_node *network);

int search_start(int **array)
{
    int start;
    int count;
    int i, j;

    i = 0;
    for (i = 0; i < N; i++)
    {
        count = 0;
        j = 0;
        for (j = 0; j < N; j++)
        {
            if (array[i][j] == 1)
                count++;
        }
        if (count == 1)
            return (i);
    }
    return (-1);
}

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
    print_network(network);
    start = search_start(array);

    free_network(network);
    return (EXIT_SUCCESS);
}
