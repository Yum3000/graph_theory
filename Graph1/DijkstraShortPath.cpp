#include "Graph.h"
#include "utils.h"

void DijkstraShortPath(int st, vector<vector<pair<int, int>>> adj, vector<int>& d, vector<int>& p, bool ignoreWeight) {
	int n = adj.size();
	d.assign(n, fakeINF);
	p.assign(n, -1);
	vector<bool> u(n, false);
	vector<vector<int>> path;

	d[st] = 0;
	for (int i = 0; i < n; i++) {
		int v = -1;
		for (int j = 0; j < n; j++) {
			if (!u[j] && (v == -1 || d[j] < d[v])) {
				v = j;
			}
		}

		if (d[v] == fakeINF) {
			break;
		}

		u[v] = true;
		for (auto edge : adj[v]) {
			int to = edge.first;
			int len = ignoreWeight ? 1 : edge.second;

			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
			}
		}

	}
}