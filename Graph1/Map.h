#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

class Cell {
public:
	Cell(int x, int y, int elevation);
	Cell();
	int distanceTo(Cell c);
	int x, y, elevation;
	bool operator < (const Cell& rhs) const {
		return tie(x, y, elevation) < tie(rhs.x, rhs.y, rhs.elevation);
	}
};

class Map{
public:
	Map(string file, ostream *outStream);
	Cell cellAt(int x, int y);
	vector<Cell> neighbors(Cell c);
	~Map();

private:
	vector<vector<int>> map;
};


// эвристики
int ManhattanDist(Cell c, Cell dest);
int ChebyshevDist(Cell c, Cell dest);
int EuclidDist(Cell c, Cell dest);
int AbsenceDist(Cell c, Cell dest);

void AStar(
	Map field,
	Cell start,
	Cell finish,
	map<Cell, Cell>& parents,
	map<Cell, int>& distance,
	int (*heuristic)(Cell, Cell) = AbsenceDist
);