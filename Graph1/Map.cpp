#include <vector>
#include <iostream>
#include "Map.h"
#include "utils.h"


Map::Map(string file, ostream *outStream) {
	bool fileReadError = readFile(file, map);

	if (fileReadError) {
		*outStream << "Не удалось открыть файл." << endl;
		exit(1);
	}
}

Map::~Map() {
	for (int i = 0; i < map.size(); i++) {
		map[i].clear();
	}

	map.clear();
}

Cell Map::cellAt(int x, int y) {
	return Cell(x, y, map[x][y]);
}

vector<Cell> Map::neighbors(Cell c) {
	vector<Cell> result;
	int maxY = map.size() - 1;
	int maxX = map[0].size() - 1;

	// top
	if (c.y > 0) result.push_back(Cell(c.x, c.y - 1, map[c.x][c.y - 1]));
	// bottom
	if (c.y < maxY) result.push_back(Cell(c.x, c.y + 1, map[c.x][c.y + 1]));
	// left
	if (c.x > 0) result.push_back(Cell(c.x - 1, c.y, map[c.x - 1][c.y]));
	// right
	if (c.x < maxX) result.push_back(Cell(c.x + 1, c.y, map[c.x + 1][c.y]));

	return result;
}

Cell::Cell(int inX, int inY, int inElevation) {
	x = inX;
	y = inY;
	elevation = inElevation;
}

Cell::Cell() {
	x = 0;
	y = 0;
	elevation = 0;
}

int Cell::distanceTo(Cell c) {
	// h(ij, kl) = abs(k - i) + abs(l - j) + abs(akl - aij)
	// i = x
	// j = y
	// k = c.x
	// l = c.y
	// akl = c.elevation
	// aij = elevation
	return abs(c.x - x) + abs(c.y - y) + abs(c.elevation - elevation);
}

int ManhattanDist(Cell c, Cell dest) {
	return abs(dest.x - c.x) + abs(dest.y - c.y);
}

int ChebyshevDist(Cell c, Cell dest) {
	return max(abs(dest.x - c.x), abs(dest.y - c.y));
}

int EuclidDist(Cell c, Cell dest) {
	return round(sqrt(pow((dest.x - c.x), 2) + pow((dest.y - c.y), 2)));
}

int AbsenceDist(Cell c, Cell dest) {
	return 0;
}