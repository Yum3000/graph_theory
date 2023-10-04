#include "Graph.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

int find(vector<pair<int, int>>& trees, int i)
{
    if (trees[i].second != i) {
        trees[i].second = find(trees, trees[i].second);
    }
    return trees[i].second;
}


void Union(vector<pair<int, int>>& trees, int a, int b)
{
    int rootA = find(trees, a);
    int rootB = find(trees, b);
    if (trees[rootA].first < trees[rootB].first) {
        trees[rootA].second = rootB;
    } else if (trees[rootA].first > trees[rootB].first) {
        trees[rootB].second = rootA;
    } else {
        trees[rootB].second = rootA;
        trees[rootA].first++;
    }
}

vector<vector<int>> BoruvkaMST(Graph graph, vector<Edge> edges) {

    vector<pair<int, int>>trees;
    vector<vector<int>> resMST;

    for (int i = 0; i < graph.vertexCount; i++)
    {
        trees.push_back(make_pair(0, i));
    }
    int TotalTrees = graph.vertexCount;
    int MST_total_weight = 0;

    while (TotalTrees > 1)
    {
        vector<int> smallest_edge(graph.vertexCount, -1);
        for (int i = 0; i < edges.size(); i++)
        {
            int setA = find(trees, edges[i].v1);
            int setB = find(trees, edges[i].v2);
            if (setA == setB) {
                continue;
            } else {
                if (smallest_edge[setA] == -1 ||
                    edges[smallest_edge[setA]].weight > edges[i].weight) {
                    smallest_edge[setA] = i;
                }

                if (smallest_edge[setB] == -1 ||
                    edges[smallest_edge[setB]].weight > edges[i].weight) {
                    smallest_edge[setB] = i;
                }
            }
        }

        for (int i = 0; i < graph.vertexCount; i++)
        {
            if (smallest_edge[i] != -1)
            {
                int setA = find(trees, edges[smallest_edge[i]].v1);
                int setB = find(trees, edges[smallest_edge[i]].v2);
                if (setA == setB)
                    continue;
                MST_total_weight += edges[smallest_edge[i]].weight;

                //cout << "Edge (" << edges[smallest_edge[i]].v1 << ","
                    //<< edges[smallest_edge[i]].v2 << ") " << "weight "
                    //<< edges[smallest_edge[i]].weight << endl;

                resMST.push_back({ edges[smallest_edge[i]].v1 + 1, edges[smallest_edge[i]].v2 + 1, edges[smallest_edge[i]].weight });


                Union(trees, setA, setB);
                TotalTrees--;
            }
        }
    }
    cout << "Weight of spanning tree: " << MST_total_weight << endl;
    return resMST;
}