#include "Graph.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool edgesComparer(Edge left, Edge right)
{	return (left.weight < right.weight);
}

vector<vector<int>> KruskalMST(Graph graph, vector<Edge> edges) {
	sort(edges.begin(), edges.end(), edgesComparer);
	//for (int i = 0; i < edges.size(); i++) {
		//cout << edges[i].v1 << "->" << edges[i].v2 << "=" << edges[i].weight << endl;
	//}

    vector<int> tree_id(graph.vertexCount);
    vector<vector<int>> res;
    int cost = 0;

    for (int i = 0; i < graph.vertexCount; i++)
        tree_id[i] = i;

    for (int i = 0; i < edges.size(); i++)
    {
        int a = edges[i].v1;
        int b = edges[i].v2;
        int weight = edges[i].weight;

        if (tree_id[a] != tree_id[b])
        {
            cost+= weight;
            res.push_back({ a+1, b+1, weight});
            int old_id = tree_id[b];
            int new_id = tree_id[a];
            for (int j = 0; j < graph.vertexCount; ++j)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
        }
    }
    cout << "Weight of spanning tree: " << cost << endl;
    return res;
}