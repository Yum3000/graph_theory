#include "Graph.h"

void dfs1(int v, vector<char>* used, vector<int>* order, Graph graph) {
    (*used)[v] = true;

    for (size_t i = 0; i < graph.vertexCount; ++i) {
        if (graph.matrix[v][i] > 0 && !(*used)[i]) {
            dfs1(i, used, order, graph);
        }
    }

    order->push_back(v);
}

void dfs2(int v, vector<char>* used, vector<int>* component, int** matrixT, Graph graph) {
    (*used)[v] = true;

    component->push_back(v);

    for (size_t i = 0; i < graph.vertexCount; ++i) {
        if (matrixT[v][i] != 0 && !(*used)[i]) {
            dfs2(i, used, component, matrixT, graph);
        }
    }
}

vector<vector<int>> getComponentsDir(Graph graph) {
    vector<vector<int>> componentDir;

    vector<char> used;
    vector<int> order;

    int** matrixT = new int* [graph.vertexCount];
    for (int i = 0; i < graph.vertexCount; i++) {
        matrixT[i] = new int[graph.vertexCount];
    }

    for (int i = 0; i < graph.vertexCount; i++) {
        for (int j = 0; j < graph.vertexCount; j++) {
            matrixT[i][j] = graph.matrix[j][i];
        }
    }

    used.assign(graph.vertexCount, false);
    for (int i = 0; i < graph.vertexCount; ++i) {
        if (!used[i]) {
            dfs1(i, &used, &order, graph);
        }
    }
    used.assign(graph.vertexCount, false);
    for (int i = 0; i < graph.vertexCount; ++i) {
        int v = order[graph.vertexCount - 1 - i];
        if (!used[v]) {
            vector<int> component;
            dfs2(v, &used, &component, matrixT, graph);
            componentDir.push_back(component);
        }
    }
    return componentDir;

    // delete matricaT !!!
}