#include "Graph.h"
#include "utils.h"

// https://www.cyberforum.ru/post12429012.html

void DijkstraMinDist(Graph graph, int start, vector<int>& minDistances,	vector<int>& minDistanceParents) {
	int n = graph.vertexCount;
	vector<bool> visited(n, false);

	minDistances.assign(n, fakeINF);
	minDistanceParents.assign(n, -1);

	minDistances[start] = 0;

	for (int i = 0; i < n; i++) {
		int minDist = fakeINF;
		int minDistVert = -1;

		for (int j = 0; j < n; j++) {
			if (visited[j]) continue;

			if (minDistances[j] < minDist) {
				minDist = minDistances[j];
				minDistVert = j;
			}
		}

		if (minDistVert == -1) break;

		visited[minDistVert] = true;

		for (auto edge : graph.list_of_edges(minDistVert)) {
			int to = edge.v2;

			if (visited[to]) continue;

			int distTo = minDist + edge.weight;

			if (distTo < minDistances[to]) {
				minDistances[to] = distTo;
				minDistanceParents[to] = minDistVert;
			}
		}
	}
}