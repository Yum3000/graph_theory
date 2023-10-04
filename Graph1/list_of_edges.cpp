#include "Graph.h"

vector<Edge> Graph::list_of_edges() {

    vector < Edge > list_of_edges;
    bool directed = is_directed();

    for (int i = 0; i < vertexCount; i++) {
        int initJ = 0;
        if (!directed) {
            initJ = i + 1;
        }
        for (int j = initJ; j < vertexCount; j++) {

            if (matrix[i][j] != 0) {
                Edge edge;
                edge.v1 = i;
                edge.v2 = j;
                edge.weight = matrix[i][j];
                list_of_edges.push_back(edge);
            }
        }
    }

    return list_of_edges;
}