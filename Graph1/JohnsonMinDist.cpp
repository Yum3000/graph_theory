#include "Graph.h"
#include "utils.h"

bool JohnsonMinDist(Graph graph, vector<Edge>& E, vector<vector<int>>& distances) {

	vector<int> d;
	d.assign(graph.vertexCount + 1, fakeINF);
	vector<int> p;
	vector<int> h;
	h.assign(graph.vertexCount, 0);
	bool hasCycle;

	int firstEdgesSize = E.size();

	for (int i = 0; i < graph.vertexCount; i++) {
		Edge ed;
		ed.v1 = graph.vertexCount;
		ed.v2 = i;
		ed.weight = 0;
		E.push_back(ed);
	}

	//for (int i = 0; i < E.size(); i++) {
		//cout << E[i].v1 << "->" << E[i].v2 << "=" << E[i].weight << endl;
	//}

	for (int i = 0; i <= graph.vertexCount; i++) {
		hasCycle = BellmanFordForJohnson(E, graph.vertexCount, i, d, p);
		distances.push_back(d);
		if (hasCycle) {
			cout << "Graph contains a negative cycle." << endl;
			return true;
		}
	}

	while (E.size() != firstEdgesSize) {
		E.pop_back();
	}
	distances.pop_back();

	for (int i = 0; i < E.size(); i++) {
		int from = E[i].v1;
		int to = E[i].v2;
		E[i].weight = E[i].weight + h[from] - h[to];
	}

	for (int i = 0; i < graph.vertexCount; i++) {
		DijkstraMinDist(graph, i, d, p);
	}
	for (int i = 0; i < graph.vertexCount; i++) {
		for (int u = 0; u < graph.vertexCount; u++)
		{
			distances[i][u] = distances[i][u] + h[i] - h[u];
		}
	}

	return false;
}