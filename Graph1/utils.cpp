#include <string>
#include <iostream>
#include <vector>
#include "Graph.h"
#include "Map.h"

using namespace std;
const char* spaceSym = " \t\n\r\f\v";

string& rtrim(string& s)
{
    s.erase(s.find_last_not_of(spaceSym) + 1);
    return s;
}

string& ltrim(string& s)
{
    s.erase(0, s.find_first_not_of(spaceSym));
    return s;
}

string& trim(string& s)
{
    return ltrim(rtrim(s));
}

vector <string> split(string& s) {
    vector <string> result;
    size_t pos = s.find(" ");
    string token;

    while (pos != string::npos) {
        token = s.substr(0, pos);

        result.push_back(token);

        s.erase(0, pos + 1);

        pos = s.find(" ");
    }

    if (s.size() != 0) result.push_back(s);

    return result;
}

vector <int> string_to_ints(vector<string> strs) {
    vector <int> ints;

    for (int i = 0; i < strs.size(); i++) {
        int num = stoi(strs[i]);
        ints.push_back(num);
    }
    return ints;
}

vector <int> parse_data_string(string& s) {
    return string_to_ints(split(s));
}

void printNumVect(ostream& out, vector<int> data, bool plusOne = false) {
    int n = 0;
    if (plusOne) {
        n = 1;
    }
    out << "[";
    for (int i = 0; i < data.size(); i++) {
        out << data[i] + n;
        if (i != data.size() - 1) {
            out << ", ";
        }
    }
    out << "]";
}

void printNumVectVect(ostream& out, vector<vector<int>> data, bool plusOne = false) {
    out << "[";
    for (int i = 0; i < data.size(); i++) {
        printNumVect(out, data[i], plusOne);
        if (i != data.size() - 1) {
            out << ", ";
        }
    }
    out << "]";
}

void printVertVect(ostream& out, vector<int> data) {
    return printNumVect(out, data, true);
}

void printVertVectVect(ostream& out, vector<vector<int>> data) {
    return printNumVectVect(out, data, true);
}

bool hasNegative(Graph graph) {
    auto matrix = graph.adjacency_matrix();

    for (int i = 0; i < graph.vertexCount; i++) {
        for (int j = 0; j < graph.vertexCount; j++) {
            if (matrix[i][j] < 0) return true;
        }
    }

    return false;
}

bool readFile(string fileName, vector<vector<int>> &data) {
    ifstream in(fileName);

    if (!in.is_open()) return true;

    string str;
    while (getline(in, str)) {
        data.push_back(parse_data_string(str));
    }

    in.close();

    return false;
}

//void printPathAStar(Cell start, Cell finish, map<Cell, Cell> parents, map<Cell, int> distance) {
//    vector<Cell> result;
//    Cell current = finish;
//
//    while (current.x != start.x || current.y != start.y) {
//        result.push_back(current);
//        current = parents[current];
//    }
//
//    result.push_back(start);
//
//    for (int i = result.size() - 1; i >= 0; i--) {
//        cout << "(" << result[i].x << ", " << result[i].y << ")" << endl;
//    }
//}