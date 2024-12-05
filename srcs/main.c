#include "test.h"

int main(int argc, char **argv)
{
    int **array;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    array = create_array(argv[1]);
    if (!array)
    {
        fprintf(stderr, "Error creating array\n");
        return EXIT_FAILURE;
    }

    // KruskalMST(array);
    my_algo(array);

    // my_array_printf(array);

    free_array2((void **)array);
    return 0;
}
