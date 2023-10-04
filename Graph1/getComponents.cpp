#include "Graph.h"
#include <queue>

vector<vector<int>> getComponents(Graph graph) {
    queue<int> q;
    vector < bool > used(graph.vertexCount);
    vector<vector<int>> components;

    for (int i = 0; i < used.size(); i++) {
        if (used[i]) continue;

        vector<int> curComp;
        used[i] = true;
        q.push(i);
        curComp.push_back(i);

        while (!q.empty()) {
            int cur = q.front();

            q.pop();
            vector<int> adj_list = graph.adjacency_list(cur, true);
            for (size_t j = 0; j < adj_list.size(); ++j) {
                int to = adj_list[j];

                if (!used[to]) {

                    used[to] = true;
                    q.push(to);
                    curComp.push_back(to);
                }
            }
        }

        components.push_back(curComp);
    }

    return components;
}


