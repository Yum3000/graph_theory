#include "Graph.h"
#include "utils.h"
#include <deque>

bool LevitMinDist(Graph graph, int x, vector<vector<pair<int, int>>> adj, vector<int>& d, vector<int>& p) {

	if (BellmanFordMinDist(graph, x, d, p)) {
		return true;
	}

	vector<int> state(graph.vertexCount, 0);
	state[x] = 1;
	d[x] = 0;
	deque<int> q; 
	q.push_back(x);

	while (!q.empty()) {
		int v = q.front();
		q.pop_front();

		for (int i = 0; i < adj[v].size(); i++) {
			int to = adj[v][i].first;
			int len = adj[v][i].second;

			if (state[to] == 0)	{
				d[to] = d[v] + len;
				state[to] = 1;
				q.push_back(to);
			} else if (state[to] == 1) {
				d[to] = min(d[to], d[v] + len);
			}
			else if (state[to] == 2) {
				if (d[to] > d[v] + len) {
					d[to] = d[v] + len;
					state[to] = 1;
					//q.push_back(to);
					q.push_front(to);
				}
			}
			p[to] = v;
			state[to] = 2;
		}
	}
	return false;
}