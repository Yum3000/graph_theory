#include "Graph.h"

int** get_distances(Graph graph) {
    // fixme разобраться, почему настоящий maxint сам с собой не сравнивается
    int fakeMaxInt = 1234567;
    int** matrix_distances = new int* [graph.vertexCount];

    for (int i = 0; i < graph.vertexCount; i++) {
        matrix_distances[i] = new int[graph.vertexCount];
    }

    for (int i = 0; i < graph.vertexCount; i++) {
        for (int j = 0; j < graph.vertexCount; j++) {
            matrix_distances[i][j] = graph.matrix[i][j];
            if (graph.matrix[i][j] == 0) {
                matrix_distances[i][j] = fakeMaxInt;
            }
        }
    }

    for (int v = 0; v < graph.vertexCount; v++) {
        for (int i = 0; i < graph.vertexCount; i++) {
            for (int j = 0; j < graph.vertexCount; j++) {
                //if (i != j && matrix_distances[i][j] != 0) {
                if (matrix_distances[i][v] < fakeMaxInt && matrix_distances[v][j] < fakeMaxInt) {
                    //cout << matrix_distances[i][j] << "|" <<matrix_distances[i][v]<< "|" <<matrix_distances[v][j] << "|" <<matrix_distances[i][v] + matrix_distances[v][j] << endl;
                    matrix_distances[i][j] = min(matrix_distances[i][j], matrix_distances[i][v] + matrix_distances[v][j]);

                }
            }
        }
    }

    //for (int i = 0; i < graph.vertexCount; i++) {
    //    for (int j = 0; j < graph.vertexCount; j++) {
    //        if (matrix_distances[i][j] == fakeMaxInt) {
    //            matrix_distances[i][j] = 0;
    //        }

    //    }
    //}

    return matrix_distances;
}