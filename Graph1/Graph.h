#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;


struct Edge {

	int v1;
	int v2;
	int weight;

};

struct CLIargs {
	int task;
	int beginVerNum, endVerNum;
	bool m, l, e, h, o, k, p, b, s, d, t, bl, n;
	int startX, startY, finishX, finishY;
	bool wrongArg;
	string file;
};

enum DataType {
	e, m, l			// todo: исправить переменные на полные имена
};


class Graph {

public:
	string file;
	int j;
	int** matrix;
	int vertexCount;
	int edgesCount;

public:
	Graph(string a, DataType b);
	int** adjacency_matrix();
	vector<int> adjacency_list(int Vertex_v, bool ignoreDirecition = false);
	int getVertexCount();
	int getEdgesCount();
	bool is_edge(int Vertex_vi, int Vertex_vj);
	int weight(int Vertex_vi, int Vertex_vj);
	vector<Edge> list_of_edges();
	vector<Edge> list_of_edges(int Vertex_v);
	bool is_directed();

};

int** get_distances(Graph graph);
vector<vector<int>> getComponents(Graph graph);
void dfs1(int v, vector<char>* used, vector<int>* order, Graph graph);
void dfs2(int v, vector<char>* used, vector<int>* component, int** matrixT, Graph graph);
vector<vector<int>> getComponentsDir(Graph graph);

vector<vector<int>> PrimMST(Graph graph);
vector<vector<int>> KruskalMST(Graph graph, vector<Edge> edges);
vector<vector<int>> BoruvkaMST(Graph graph, vector<Edge> edges);

void findBridges(Graph graph, vector<vector<int>> adj, vector<bool>& cutVer, vector<pair<int, int>>& bridges);

void DijkstraShortPath(int st, vector<vector<pair<int, int>>> adj, vector<int>& d, vector<int>& p, bool ignoreWeight = false);

void DijkstraMinDist(Graph graph, int st, vector<int>& minDistances, vector<int>& minDistanceParents);
bool BellmanFordMinDist(Graph graph, int start, vector<int>& minDistances, vector<int>& minDistanceParents);
bool LevitMinDist(Graph graph, int x, vector<vector<pair<int, int>>> adj, vector<int>& d, vector<int>& p);

bool JohnsonMinDist(Graph graph, vector<Edge>& E, vector<vector<int>>& distances);
bool BellmanFordForJohnson(vector<Edge> edges, int vertexCount, int start, vector<int>& minDistances, vector<int>& minDistanceParents);

int fordFulkerson(Graph graph, int s, int t, vector<int>& parent, vector<vector<int>>& rGraph);