#include "Graph.h"
#include "utils.h"

// https://e-maxx.ru/algo/ford_bellman

// Возвращает наличие оттрицательного цикла.
bool BellmanFordMinDist(Graph graph, int start,	vector<int>& minDistances, vector<int>& minDistanceParents) {
	auto edges = graph.list_of_edges();
	int edgesCount = graph.edgesCount;
	if (!graph.is_directed()) {
		for (int i = 0; i < graph.edgesCount; i++) {
			Edge ed;
			ed.v1 = edges[i].v2;
			ed.v2 = edges[i].v1;
			ed.weight = edges[i].weight;
			edges.push_back(ed);
		}
		edgesCount = graph.edgesCount * 2;
	}

	bool relaxation;

	minDistances.assign(graph.vertexCount, fakeINF);
	minDistanceParents.assign(graph.vertexCount, -1);
	minDistances[start] = 0;

	// Без учёта отрицательных циклов достаточно vertexCount - 1 итераций.
	// Релаксация произойдёт в дополнительной итерация только при наличии отрицательного цикла.
	for (int i = 0; i < graph.vertexCount; i++) {
		relaxation = false;

		for (int j = 0; j < edgesCount; j++) {
			int from = edges[j].v1;
			int to = edges[j].v2;
			int weight = edges[j].weight;

			if (minDistances[from] == fakeINF) continue;

			if (minDistances[to] > minDistances[from] + weight) {
				minDistances[to] = minDistances[from] + weight;
				minDistanceParents[to] = from;

				relaxation = true;
			}
		}
	}

	return relaxation;
}