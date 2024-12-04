#include "test.h"

int *input_array(char *line);
int **create_array(char *filename);

int *input_array(char *line)
{
    char **line_split;
    char **str;
    int *array;
    int i = 0;

    line_split = my_split(line, ' ');
    if (!line_split)
        return NULL;

    array = (int *)malloc(sizeof(int) * M);
    if (!array)
    {
        free_array2((void **)line_split);
        return NULL;
    }

    while (line_split[i] != NULL && i < M)
    {
        str = my_split(line_split[i], ',');
        array[i] = atoi(str[0]);
        free_array2((void **)str);
        i++;
    }
    free_array2((void **)line_split);
    return array;
}

int **create_array(char *filename)
{
    int **array;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return NULL;
    }

    FILE *file = fdopen(fd, "r");
    if (file == NULL)
    {
        perror("Error converting file descriptor to stream");
        close(fd);
        return NULL;
    }

    array = (int **)malloc(sizeof(int *) * (N + 1));
    if (array == NULL)
    {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    int i = 0;
    while ((read = getline(&line, &len, file)) != -1 && i < N)
    {
        array[i] = input_array(line);
        if (array[i] == NULL)
        {
            fprintf(stderr, "Error processing line %d\n", i);
            break;
        }
        i++;
    }
    array[i] = NULL;

    free(line);
    fclose(file);
    return array;
}
