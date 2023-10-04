#include "Graph.h"

using namespace std;

void DFS(int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<pair<int, int>>& bridge, vector<vector<int>>& adj, vector<bool>& cutVer) {
	static int time = 0; // ???
	disc[u] = low[u] = time;
	time += 1;
	int count = 0;

	for (int v : adj[u]) {
		if (disc[v] == -1) {
			parent[v] = u;
			DFS(v, disc, low, parent, bridge, adj, cutVer);

			low[u] = min(low[u], low[v]);

			if (low[v] > disc[u]) {
				bridge.push_back({u, v});
				if (adj[u].size() > 1) {
					cutVer[u] = true;
				}
				if (adj[v].size() > 1) {
					cutVer[v] = true;
				}
			}
			count++;
		}
		else if (v != parent[u]) {
			low[u] = min(low[u], disc[v]);
		}

	}

	if (count > 1) {//parent[neighbour] == -1 && count > 1) {
		cutVer[u] = true;
	}
}


const int maxn = 1e5;
bool used[maxn];
int h[maxn], dist[maxn];

void dfs2(Graph graph, int currentVert, int parent = -1) {
	used[currentVert] = 1;
	dist[currentVert] = h[currentVert] = (parent == -1 ? 0 : h[parent] + 1);
	int children = 0;
	auto directNeighbours = graph.adjacency_list(currentVert);

	for (int i = 0; i < directNeighbours.size(); i++) {
		int neighbour = directNeighbours[i];

		if (neighbour == parent) continue;

		if (used[neighbour]) {
			dist[currentVert] = min(dist[currentVert], h[neighbour]);
		} else {
			dfs2(graph, neighbour, currentVert);

			dist[currentVert] = min(dist[currentVert], dist[neighbour]);

			// корень (parent == -1) обрабатываем отдельно
			if (h[currentVert] <= dist[neighbour] && parent != -1) {
				cout << currentVert + 1<< ", ";
			}
			children++;
		}

	}

	if (parent == -1 && children > 1) {
		// v -- корень и точка сочленения
		cout << currentVert + 1<< ", ";
	}
}


void findBridges(Graph graph, vector<vector<int>> adj, vector<bool>& cutVer, vector<pair<int, int>>& bridges) {
	vector<int> disc(graph.vertexCount, -1), low(graph.vertexCount, -1), parent(graph.vertexCount, -1);

	cutVer.assign(graph.vertexCount, false);

	for (int i = 0; i < graph.vertexCount; ++i) {
		if (disc[i] == -1) {
			DFS(i, disc, low, parent, bridges, adj, cutVer);
	 		//dfs2(graph, i);
		}
	}
	cout << endl;

}