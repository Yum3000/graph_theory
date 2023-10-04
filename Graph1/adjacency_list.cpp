#include "Graph.h"

vector <int> Graph::adjacency_list(int Vertex_v, bool ignoreDirection) {
    vector <int> adjacency_list;
    vector<bool> conected;
    conected.assign(vertexCount, false);

    for (int j = 0; j < vertexCount; j++) {
        if (matrix[Vertex_v][j] != 0) {
            conected[j] = true;
        }
    }

    if (ignoreDirection) {
        for (int j = 0; j < vertexCount; j++) {
            if (matrix[j][Vertex_v] != 0) {
                conected[j] = true;
            }
        }
    }

    for (int j = 0; j < vertexCount; j++) {
        if (conected[j]) {
            adjacency_list.push_back(j);
        }
    }


    return adjacency_list;
}