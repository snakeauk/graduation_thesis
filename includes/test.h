#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "network.h"
#include "utils.h"

#define N 47
#define M 47

// main.c
int main(int argc, char **argv);

// input.c
int *input_array(char *line);
int **create_array(char *filename);

// print.c
void    my_array_printf(int **array);

#endif