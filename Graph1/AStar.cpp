#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include "Map.h"
using namespace std;

void AStar(
	Map field,
	Cell start,
	Cell finish,
	map<Cell, Cell>& parents,
	map<Cell, int>& distance,
	int (*heuristic)(Cell, Cell)
) {
	typedef pair<int, Cell> PCell;
	priority_queue<	PCell, vector<PCell>, greater<PCell>> frontier;

	frontier.push(pair<int, Cell>(0, start));

	parents[start] = start;
	distance[start] = 0;

	while (!frontier.empty()) {
		Cell current = frontier.top().second;
		frontier.pop();

		if (current.x == finish.x && current.y == finish.y) {
			break;
		}

		for (Cell neighbor : field.neighbors(current)) {
			int newCost = distance[current] + current.distanceTo(neighbor);
			bool notVisited = distance.find(neighbor) == distance.end();
			bool foundBetterCost = newCost < distance[neighbor];

			if (notVisited || foundBetterCost) {
				distance[neighbor] = newCost;
				int priority = newCost + heuristic(neighbor, finish);
				frontier.push(pair<int, Cell>(priority, neighbor));
				parents[neighbor] = current;
			}
		}
	}

	vector<Cell> result;
	Cell current = finish;

	while (current.x != start.x || current.y != start.y) {
		result.push_back(current);
		current = parents[current];
	}

	result.push_back(start);

	cout << distance[finish] << " - length of path between (" << start.x << ", " << start.y << ") and (" <<
		finish.x << ", " << finish.y << ") points." << endl;
	cout << "[";
	for (int i = result.size() - 1; i >= 0; i--) {
		cout << "(" << result[i].x << ", " << result[i].y;
		if (i != 0) {
			 cout << "), ";
		} else {
			cout << ")]";
		}

	}
	cout << endl;

}