#pragma once
#include <string>
#include "Graph.h"

const int fakeINF = 100000;

std::string& rtrim(std::string& s);
std::string& ltrim(std::string& s);
std::string& trim(std::string& s);
vector <string> split(string& s);
vector <int> string_to_ints(vector<string> strs);
vector <int> parse_data_string(string& s);
void printNumVect(ostream& out, vector<int> data, bool plusOne = false);
void printNumVectVect(ostream& out, vector<vector<int>> data, bool plusOne = false);
void printVertVect(ostream& out, vector<int> data);
void printVertVectVect(ostream& out, vector<vector<int>> data);
bool hasNegative(Graph graph);
bool readFile(string fileName, vector<vector<int>>& data);
//void printPathAStar(Cell start, Cell finish, map<Cell, Cell> parents, map<Cell, int> distance);