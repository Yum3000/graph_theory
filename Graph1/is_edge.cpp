#include "Graph.h"

bool Graph::is_edge(int Vertex_vi, int Vertex_vj) {
    return matrix[Vertex_vi][Vertex_vj] != 0 ||
        matrix[Vertex_vj][Vertex_vi] != 0;
}