#include "network.h"

t_edge *convert_matrix_to_edges(int **matrix, int *edge_count);
int find(t_subset *subsets, int i);
void Union(t_subset *subsets, int x, int y);
int compareEdges(const void *a, const void *b);
void KruskalMST(int **matrix);

// Convert adjacency matrix to edge list
t_edge *convert_matrix_to_edges(int **matrix, int *edge_count)
{
    int max_edges = N * (N - 1) / 2; // Maximum possible edges in an undirected graph
    t_edge *edges = malloc(max_edges * sizeof(t_edge));
    if (!edges) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int k = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) { // Only upper triangular part
            if (matrix[i][j] != 0) { // Only include valid edges
                edges[k].src = i;
                edges[k].dest = j;
                edges[k].weight = matrix[i][j];
                k++;
            }
        }
    }
    *edge_count = k;
    return edges;
}

// Find function for union-find
int find(t_subset *subsets, int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union function for union-find
void Union(t_subset *subsets, int x, int y)
{
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Compare function for qsort
int compareEdges(const void *a, const void *b)
{
    t_edge *edgeA = (t_edge*)a;
    t_edge *edgeB = (t_edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Kruskal's MST algorithm
void KruskalMST(int **matrix)
{
    int edge_count;
    t_edge *edges = convert_matrix_to_edges(matrix, &edge_count);

    // Sort edges by weight
    qsort(edges, edge_count, sizeof(edges[0]), compareEdges);

    // Allocate memory for subsets
    t_subset *subsets = malloc(N * sizeof(t_subset));
    if (!subsets) {
        perror("Memory allocation failed");
        free(edges);
        exit(EXIT_FAILURE);
    }

    // Initialize subsets
    for (int v = 0; v < N; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    t_edge result[N - 1];
    int e = 0; // Index for result[]
    int i = 0; // Index for sorted edges

    while (e < N - 1 && i < edge_count) {
        t_edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the constructed MST
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);

    free(edges);
    free(subsets);
}