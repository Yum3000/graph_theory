#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
#include "Graph.h"
#include "utils.h"
using namespace std;

bool bfs(vector<vector<int>> rGraph, int s, int t, vector<int>& parent, int vertexCount) {

    vector<bool> visited(vertexCount, false);

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;


    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < vertexCount; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {

                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}



int fordFulkerson(Graph graph, int s, int t, vector<int>& parent, vector<vector<int>>& rGraph) {
    int u, v;
    int V = graph.vertexCount;


    //vector<vector<int>> rGraph; 

    for (u = 0; u < V; u++) {
        vector<int> temp;
        for (v = 0; v < V; v++) {
            temp.push_back(graph.matrix[u][v]);
        }
        rGraph.push_back(temp);
    }


    int max_flow = 0; 


    while (bfs(rGraph, s, t, parent, V)) {

        int path_flow = fakeINF;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}