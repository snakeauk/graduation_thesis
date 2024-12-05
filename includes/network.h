#ifndef NETWORK_H
#define NETWORK_H


#include <stdlib.h>
#include <stdio.h>
#include "utils.h"


// ======================================================================
// ======================== create_network.c ============================
// ======================================================================
typedef struct s_node t_node;
typedef struct s_node
{
    int      name;
    int      *array;
    int     group_id; // 初期化 = -1
    t_node   **conected_node; // 繋がっている先のノードのアドレスの配列
    t_node   *next; // 今回使わない　構造体をまとめるだけのやつ　最後はNULL
}               t_node;

t_node *input_network(int **array); // networkを作る関数。array[N][N]
t_node *create_node(int **array, int name); // nodeを初期化する関数
t_node  *search_node(t_node *network, int name); // nameのノードを返す関数
int     count_conect_node(int *conect); // nodeに接続されているnodeの個数を返す関数。
void    free_network(t_node *network); // networkをfreeする関数、メモリリーク対策。

// ======================================================================
// ======================================================================
// ======================================================================


// ======================================================================
// ======================== my_algo.c ===================================
// ======================================================================

int my_algo(int **array);
int search_start(int **array);
void    print_network(t_node *network);

// ======================================================================
// ======================================================================
// ======================================================================





// typedef struct s_node
// {
//     char         *name;
//     t_node       **next;
// }           t_node;


#define N 47

// t_edge structure
typedef struct s_edge {
    int src, dest, weight;
}           t_edge;

// t_subset structure for union-find
typedef struct s_subset {
    int parent;
    int rank;
}           t_subset;

// Function prototypes
t_edge *convert_matrix_to_edges(int **matrix, int *edge_count);
int find(t_subset *subsets, int i);
void Union(t_subset *subsets, int x, int y);
int compareEdges(const void *a, const void *b);
void KruskalMST(int **matrix);

#endif