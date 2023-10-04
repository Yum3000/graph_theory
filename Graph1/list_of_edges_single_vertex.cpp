#include "Graph.h"

vector <Edge> Graph::list_of_edges(int Vertex_v) {

    vector <Edge> list_of_edges_Ver;

    for (int j = 0; j < vertexCount; j++) {

        if (matrix[Vertex_v][j] != 0) {
            Edge edge;
            edge.v1 = Vertex_v;
            edge.v2 = j;
            edge.weight = matrix[Vertex_v][j];
            list_of_edges_Ver.push_back(edge);
        }
    }
    return list_of_edges_Ver;

}