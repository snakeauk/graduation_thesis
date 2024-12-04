#include "test.h"

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
