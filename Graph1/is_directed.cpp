#include "Graph.h"

bool Graph::is_directed() {
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return true;
            }
        }
    }

    return false;
}