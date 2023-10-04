#include "Graph.h"
#include "utils.h"

// https://e-maxx.ru/algo/ford_bellman

// Возвращает наличие оттрицательного цикла.
bool BellmanFordForJohnson(vector<Edge> edges, int vertexCount, int start, vector<int>& minDistances, vector<int>& minDistanceParents) {

	int edgesCount = edges.size();

	bool relaxation;

	minDistances.assign(vertexCount+1, fakeINF);
	minDistanceParents.assign(vertexCount+1, -1);
	minDistances[start] = 0;

	// Без учёта отрицательных циклов достаточно vertexCount - 1 итераций.
	// Релаксация произойдёт в дополнительной итерация только при наличии отрицательного цикла.
	for (int i = 0; i < vertexCount + 1; i++) {
		relaxation = false;

		for (int j = 0; j < edgesCount; j++) {
			int from = edges[j].v1;
			int to = edges[j].v2;
			int weight = edges[j].weight;

			if (minDistances[from] == fakeINF) {
				continue;
			}

			if (minDistances[to] > minDistances[from] + weight) {
				minDistances[to] = minDistances[from] + weight;
				minDistanceParents[to] = from;

				relaxation = true;
			}
		}
	}

	return relaxation;
}