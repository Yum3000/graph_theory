#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <regex>
#include <climits>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include "Graph.h"
#include "utils.h"
#include "Map.h"


using namespace std;

void help() {
	cout << "Программу выполнила Балина Ю., группа М3О-219Б-21.\n";
	cout << "Список ключей: " << endl;
	cout << "-h/--help			справка" << endl;
	cout << "-e				список ребер" << endl;
	cout << "-m				матрица смежности" << endl;
	cout << "-l				список смежности" << endl;
	cout << "-o				вывод результатов в файл" << endl;
}

CLIargs getCLIargs(int argc, char* argv[]) {
	CLIargs args;
	args.task = -1;
	args.m = false;
	args.l = false;
	args.h = false;
	args.e = false;
	args.k = false;
	args.p = false;
	args.b = false;
	args.s = false;
	args.d = false;
	args.t = false;
	args.bl = false;
	args.n = false;
	args.wrongArg = false;
	args.o = false;
	args.file = "";
	args.beginVerNum = -1;
	args.endVerNum = -1;
	args.startX = -1;
	args.startY = -1;
	args.finishX = -1;
	args.finishY = -1;
	int nextFileName = 0;
	int nextN = 0;
	int nextD = 0;
	int nextStartX = 0;
	int nextStartY = 0;
	int nextFinishX = 0;
	int nextFinishY = 0;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];

		if (arg == "-h" || arg == "--help") {
			args.h = true;
		}
		else if (arg.substr(0, 4) == "task" && (stoi(arg.substr(4)) >= 1 && stoi(arg.substr(4)) <= 11)) {
			args.task = stoi(arg.substr(4));
		}
		else if (arg == "-m") {
			args.m = true;
			nextFileName = 2;
		}
		else if (arg == "-l") {
			args.l = true;
			nextFileName = 2;
		}
		else if (arg == "-e") {
			args.e = true;
			nextFileName = 2;
		}
		else if (arg == "-k") {
			args.k = true;
		}
		else if (arg == "-p") {
			args.p = true;
		}
		else if (arg == "-b") {
			args.b = true;
		}
		else if (arg == "-s") {
			args.s = true;
		}
		else if (arg == "-o") {
			args.o = true;
		}
		else if (arg == "-d") {
			args.d = true;
			if (args.task == 5) {
				nextD = 2;
			}
			else if (args.task == 8) {
				nextFinishX = 2;
			}
		}
		else if (arg == "-t") {
			args.t = true;
		}
		else if (arg == "-n") {
			args.n = true;
			if (args.task == 8) {
				nextStartX = 2;
			}
			else {
				nextN = 2;
			}
		}
		else {
			if (nextFileName == 1) {
				args.file = arg;
			}
			else if (nextN == 1) {
				if (stoi(arg) >= 1 && stoi(arg) <= 50) {
					args.beginVerNum = stoi(arg);
				}
				else {
					args.wrongArg = true;
				}
			}
			else if (nextD == 1) {
				if (stoi(arg) >= 1 && stoi(arg) <= 50) {
					args.endVerNum = stoi(arg);
				}
				else {
					args.wrongArg = true;
				}
			}
			else if (nextStartX == 1) {
				if (stoi(arg) >= 0 && stoi(arg) <= 50) {
					args.startX = stoi(arg);
					nextStartY = 2;
				}
				else {
					args.wrongArg = true;
				}
			}
			else if (nextStartY == 1) {
				if (stoi(arg) >= 0 && stoi(arg) <= 50) {
					args.startY = stoi(arg);
				}
				else {
					args.wrongArg = true;
				}
			}
			else if (nextFinishX == 1) {
				if (stoi(arg) >= 0 && stoi(arg) <= 50) {
					args.finishX = stoi(arg);
					nextFinishY = 2;
				}
				else {
					args.wrongArg = true;
				}
			}
			else if (nextFinishY == 1) {
				if (stoi(arg) >= 0 && stoi(arg) <= 50) {
					args.finishY = stoi(arg);
				}
				else {
					args.wrongArg = true;
				}
			}
		}

		if (nextFileName > 0) {
			nextFileName--;
		}

		if (nextN > 0) {
			nextN--;
		}

		if (nextD > 0) {
			nextD--;
		}

		if (nextStartX > 0) {
			nextStartX--;
		}
		if (nextStartY > 0) {
			nextStartY--;
		}

		if (nextFinishX > 0) {
			nextFinishX--;
		}
		if (nextFinishY > 0) {
			nextFinishY--;
		}
	}

	if (args.task == -1) {
		args.wrongArg = true;
	}

	return args;
}

// используется в 4 задании
bool compareEdges(vector<int> left, vector<int> right) {
	return left[2] < right[2];
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "RUSSIAN");
	CLIargs arguments = getCLIargs(argc, argv);

	DataType dataType = m;

	if (arguments.h) {
		help();
		return 0;
	}

	if ((arguments.m || arguments.l || arguments.e) && arguments.file == "") {
		cout << "Ошибка! Введите имя файла после параметра!" << endl;
		return 0;
	}

	cout << "ИМЯ ФАЙЛА: " << arguments.file << endl;

	if (arguments.wrongArg || (!arguments.h && !arguments.task && !arguments.m && !arguments.l && !arguments.e)) {
		cout << "***Ошибка! Неверный ввод параметров!" << endl;
		return 0;
	}

	if (arguments.task == 4) {
		int counter = 0;
		if (arguments.k) {
			counter++;
		}
		if (arguments.p) {
			counter++;
		}
		if (arguments.b) {
			counter++;
		}
		if (arguments.s) {
			counter++;
		}
		if (counter != 1) {
			cout << "Ошибка! Неверный ввод параметров!" << endl;
			return 0;
		}
	}

	if (arguments.task == 5) {
		if (arguments.beginVerNum == -1) {
			arguments.wrongArg = true;
		}
		if (arguments.endVerNum == -1) {
			arguments.wrongArg = true;
		}
	}

	if (arguments.task == 6) {
		int counter = 0;

		if (arguments.d) counter++;
		if (arguments.b) counter++;
		if (arguments.t) counter++;

		if (arguments.beginVerNum == -1) {
			arguments.wrongArg = true;
		}

		if (counter != 1) {
			cout << "Ошибка! Неверный ввод параметров!" << endl;
			return 0;
		}
	}

	if (arguments.task == 8) {
		if (arguments.startX == -1 || arguments.startY == -1) {
			arguments.wrongArg = true;
		}

		if (arguments.finishX == -1 || arguments.finishY == -1) {
			arguments.wrongArg = true;
		}
	}

	if (arguments.m) {
		dataType = m;
	}
	if (arguments.e) {
		dataType = e;
	}
	if (arguments.l) {
		dataType = l;
	}

	std::ostream& output = cout;

	std::streambuf* buf;
	std::ofstream of;

	if (arguments.o) {
		of.open("file.txt");
		buf = of.rdbuf();
	}
	else {
		buf = cout.rdbuf();
	}

	std::ostream out(buf);

	if (arguments.task == 8) {

		Map mp = Map(arguments.file, &out);
		Cell start = mp.cellAt(arguments.startX, arguments.startY);
		Cell finish = mp.cellAt(arguments.finishX, arguments.finishY);
		map<Cell, Cell> parents;
		map<Cell, int> distance;

		cout << "Manhattan path: " << endl;
		AStar(mp, start, finish, parents, distance, ManhattanDist);
		cout << "\nChebyshev path: " << endl;
		AStar(mp, start, finish, parents, distance, ChebyshevDist);
		cout << "\nEuclid path: " << endl;
		AStar(mp, start, finish, parents, distance, EuclidDist);
		cout << "\nAbsence path: " <<endl;
		AStar(mp, start, finish, parents, distance, AbsenceDist);
		cout << endl;

		//vector<Cell> result;
		//Cell current = finish;

		//while (current.x != start.x || current.y != start.y) {
		//	result.push_back(current);
		//	current = parents[current];
		//}

		//result.push_back(start);

		//for (int i = result.size() - 1; i >= 0; i--) {
		//	out << "(" << result[i].x << ", " <<  result[i].y << ")" << endl;
		//}

		return 0;
	}

	Graph ob(arguments.file, dataType);

	switch (arguments.task) {
	case 1: {

		int** matrica = ob.adjacency_matrix();

		int fakeMaxInt = 1234567;

		int verCount = ob.getVertexCount();
		int edgCount = ob.getEdgesCount();
		vector < int > list_degrees_plus;
		vector < int > list_degrees_minus;

		if (!ob.is_directed()) {
			for (int i = 0; i < verCount; i++) {
				int degree = ob.list_of_edges(i).size();
				list_degrees_plus.push_back(degree);
			}

			out << "[";
			for (int j = 0; j < list_degrees_plus.size(); j++) {
				if (j == list_degrees_plus.size() - 1) {
					out << list_degrees_plus[j];
				}
				else {
					out << list_degrees_plus[j] << ", ";
				}
			}
			out << "]" << endl;
		}
		else {

			for (int i = 0; i < verCount; i++) {
				int degree_plus = 0;
				int degree_minus = ob.list_of_edges(i).size();
				list_degrees_minus.push_back(degree_minus);

				for (int j = 0; j < verCount; j++) {
					if (matrica[j][i] != 0) {
						degree_plus += 1;
					}
				}
				list_degrees_plus.push_back(degree_plus);
			}

			out << "deg+ = [";
			for (int j = 0; j < list_degrees_plus.size(); j++) {
				if (j == 0) {
					out << list_degrees_plus[j];
				}
				else {
					out << ", " << list_degrees_plus[j];
				}
			}
			out << "]" << endl;
			out << "deg- = [";
			for (int j = 0; j < list_degrees_minus.size(); j++) {
				if (j == 0) {
					out << list_degrees_minus[j];
				}
				else {
					out << ", " << list_degrees_minus[j];
				}
			}
			out << "]" << endl;
		}

		out << "\nDistances:" << endl;
		int** matrica_distances = get_distances(ob);

		for (int i = 0; i < verCount; i++) {
			out << "[";
			for (int j = 0; j < verCount; j++) {
				if (i == j) {
					out << 0;
				}
				else if (matrica_distances[i][j] == fakeMaxInt) {
					out << "X";
				}
				else {
					out << matrica_distances[i][j];
				}

				if (j != verCount - 1) {
					out << " ";
				}

			}
			out << "]" << endl;
		}
		out << "\nEccentricity: [";
		vector < int > eccentr;
		for (int i = 0; i < verCount; i++) {
			int maxVer = -1;
			for (int j = 0; j < verCount; j++) {

				if (matrica_distances[i][j] > maxVer) {
					maxVer = matrica_distances[i][j];
				}
			}
			eccentr.push_back(maxVer);
			if (i == 0 && maxVer != fakeMaxInt) {
				out << maxVer;
			}
			else if (maxVer != fakeMaxInt) {
				out << ", " << maxVer;
			}
		}
		out << "]" << endl;

		int diametr = eccentr[0];
		int radius = eccentr[0];

		for (int i = 0; i < eccentr.size(); i++) {
			if (eccentr[i] > diametr) {
				diametr = eccentr[i];
			}
			if (eccentr[i] < radius) {
				radius = eccentr[i];
			}
		}

		out << "\nD = ";
		if (diametr != fakeMaxInt) {
			out << diametr << endl;
		}
		out << "\nR = ";
		if (radius != fakeMaxInt) {
			out << radius << endl;
		}

		out << "\nZ = [";
		vector<int> z;
		for (int i = 0; i < eccentr.size(); i++) {
			if (eccentr[i] == radius) {
				z.push_back(i + 1);
			}
		}
		for (int i = 0; i < z.size(); i++) {

			if (i != z.size() - 1 && (diametr != fakeMaxInt || radius != fakeMaxInt)) {
				out << z[i] << ", ";
			}
			else if (diametr != fakeMaxInt || radius != fakeMaxInt) {
				out << z[i];
			}
		}

		out << "]" << endl;
		out << "P = [";
		vector<int> p;
		for (int i = 0; i < eccentr.size(); i++) {
			if (eccentr[i] == diametr) {
				p.push_back(i + 1);
			}
		}
		for (int i = 0; i < p.size(); i++) {

			if (i != p.size() - 1 && (diametr != fakeMaxInt || radius != fakeMaxInt)) {
				out << p[i] << ", ";
			}
			else if (diametr != fakeMaxInt || radius != fakeMaxInt) {
				out << p[i];
			}
		}

		out << "]" << endl;

		break;
	}
	case 2: {
		vector<vector<int>> comp = getComponents(ob);

		if (comp.size() == 1) {
			out << "Graph is connected." << endl;
		}
		else {
			out << "Graph is not connected and contains " << comp.size() << " connected components." << endl;
		}

		for (int i = 0; i < comp.size(); i++) {
			sort(comp[i].begin(), comp[i].end());
		}
		out << "Connected components: " << endl;
		printVertVectVect(out, comp);
		out << endl;

		if (ob.is_directed()) { //&& comp.size() == 1) {
			comp = getComponentsDir(ob);
			if (comp.size() == 1) {
				out << "Digraph is strongly connected." << endl;
			}
			else {
				out << "Digraph is weakly connected and contains " << comp.size() << " strongly connected components." << endl;
				out << "Strongly connected components:" << endl;
				printVertVectVect(out, comp);
				out << endl;
			}
		}

		break;
	}
	case 3: {
		vector<pair<int, int>> bridges;
		vector<bool> cutVer;
		vector<vector<int>> adj;
		for (int i = 0; i < ob.vertexCount; i++) {
			adj.push_back(ob.adjacency_list(i));
		}

		findBridges(ob, adj, cutVer, bridges);
		cout << "Bridges: \n[";
		for (auto bridge : bridges) {
			cout << "(" << bridge.first + 1 << ", " << bridge.second + 1 << ") ";
		}
		cout << "]\n Cut Vertices:" << endl;
		for (int i = 0; i < cutVer.size(); i++) {
			if (cutVer[i]) {
				if (i != cutVer.size() - 1) {
					cout << i + 1 << ", ";
				}
				else {
					cout << i + 1;
				}

			}
		}

		break;
	}
	case 4: {
		vector<vector<int>> MST;

		if (arguments.k) {
			cout << "Kruskal" << endl;
			if (arguments.e || arguments.m) {
				vector<Edge> ed = ob.list_of_edges();
				MST = KruskalMST(ob, ed);
			}
		}
		if (arguments.p) {
			cout << "Prim" << endl;
			MST = PrimMST(ob);
		}
		if (arguments.b) {
			cout << "Boruvka" << endl;
			vector<Edge> ed = ob.list_of_edges();
			MST = BoruvkaMST(ob, ed);
		}
		if (arguments.k || arguments.p || arguments.b) {
			sort(MST.begin(), MST.end(), compareEdges);
			cout << "\n[";
			for (int i = 0; i < MST.size(); i++) {
				cout << "(";
				for (int j = 0; j < 3; j++) {

					if (j == 2) {
						cout << MST[i][j];
					}
					else {
						cout << MST[i][j] << ", ";
					}
				}
				if (i != MST.size() - 1) {
					cout << "), ";
				}
				else {
					cout << ")";
				}
			}
			cout << "]" << endl;
		}

		if (arguments.s) {

			vector<Edge> ed = ob.list_of_edges();

			for (int i = 0; i < 3; i++) {
				if (i == 0) {
					cout << "Kruskal start" << endl;
					auto start = std::chrono::high_resolution_clock::now();
					MST = KruskalMST(ob, ed);
					auto stop = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
					cout << "\nKruskal's algorithm time is " << duration.count();
				}
				if (i == 1) {
					cout << endl;
					cout << "Prim start" << endl;
					auto start = std::chrono::high_resolution_clock::now();
					vector<vector<int>> MST2 = PrimMST(ob);
					auto stop = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
					cout << "\nPrim's algorithm time is " << duration.count();
					MST = MST2;
				}
				if (i == 2) {
					cout << endl;
					cout << "Boruvka start" << endl;
					auto start = std::chrono::high_resolution_clock::now();
					vector<vector<int>> MST3 = BoruvkaMST(ob, ed);
					auto stop = std::chrono::high_resolution_clock::now();
					auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
					cout << "\nBoruvka's algorithm time is " << duration.count();
					MST = MST3;

				}
				sort(MST.begin(), MST.end(), compareEdges);
				cout << "\n[";
				for (int i = 0; i < MST.size(); i++) {
					cout << "(";
					for (int j = 0; j < 3; j++) {

						if (j == 2) {
							cout << MST[i][j];
						}
						else {
							cout << MST[i][j] << ", ";
						}
					}
					if (i != MST.size() - 1) {
						cout << "), ";
					}
					else {
						cout << ")";
					}
				}
				cout << "]" << endl;
			}
		}



		break;
	}
	case 5: {
		int num1 = arguments.beginVerNum - 1;
		int num2 = arguments.endVerNum - 1;
		vector<int> d;
		vector<int> p;

		vector<vector<pair<int, int>>> data;
		for (int i = 0; i < ob.vertexCount; i++) {
			vector<pair<int, int>> pairs;
			vector<Edge> edges = ob.list_of_edges(i);

			for (int j = 0; j < edges.size(); j++) {
				pair<int, int> p(edges[j].v2, edges[j].weight);
				pairs.push_back(p);
			}

			data.push_back(pairs);
		}
		DijkstraShortPath(num1, data, d, p);

		vector<Edge> printEdges;
		int pathWeight = 0;

		int cur = num2;
		do {
			// fixme: сделать глобальный fakeintmax
			if (d[cur] == 100000) break;
			//cout << cur + 1 << "->";
			Edge edge;
			edge.v2 = cur;
			edge.v1 = p[cur];
			edge.weight = ob.matrix[p[cur]][cur];
			pathWeight += ob.matrix[p[cur]][cur];
			printEdges.push_back(edge);
			cur = p[cur];

		} while (cur != num1);
		if (pathWeight == 0) {
			cout << "There is no path between the vertices " << num1 + 1 << " and " << num2 + 1 << "." << endl;
		}
		else {
			cout << "Shortest path length between " << num1 + 1 << " and " << num2 + 1 << " vertices: ";
			cout << pathWeight << endl;
			cout << "[";
			for (int i = printEdges.size() - 1; i >= 0; i--) {
				if (i != 0) {
					if (printEdges[i].weight == 1) {
						cout << "(" << printEdges[i].v1 + 1 << ", " << printEdges[i].v2 + 1 << "), ";
					}
					else {
						cout << "(" << printEdges[i].v1 + 1 << ", " << printEdges[i].v2 + 1 << ", " << printEdges[i].weight << "), ";
					}
				}
				else {
					if (printEdges[i].weight == 1) {
						cout << "(" << printEdges[i].v1 + 1 << ", " << printEdges[i].v2 + 1 << ")]";
					}
					else {
						cout << "(" << printEdges[i].v1 + 1 << ", " << printEdges[i].v2 + 1 << ", " << printEdges[i].weight << ")]";
					}
				}
			}
		}

		break;
	}
	case 6: {
		int start = arguments.beginVerNum - 1;
		int fakeIntMax = 100000;
		vector<int> minDistances;
		vector<int> minDistanceParents;

		if (arguments.d) {
			if (hasNegative(ob)) {
				cout << "Graph contains edges with negative weight." << endl;
				return 0;
			}
			else {
				cout << "Graph does not contain edges with negative weight." << endl;
			}

			DijkstraMinDist(ob, start, minDistances, minDistanceParents);
		}

		if (arguments.b) {
			if (hasNegative(ob)) {
				cout << "Graph contains edges with negative weight." << endl;
			}
			else {
				cout << "Graph does not contain edges with negative weight." << endl;
			}
			bool hasNegativeCycle = BellmanFordMinDist(ob, start, minDistances, minDistanceParents);

			if (hasNegativeCycle) {
				cout << "Graph contains a negative cycle" << endl;
				return 0;
			}
		}

		if (arguments.t) {
			if (hasNegative(ob)) {
				cout << "Graph contains edges with negative weight." << endl;
			}
			else {
				cout << "Graph does not contain edges with negative weight." << endl;
			}

			vector<vector<pair<int, int>>> adj;
			minDistances.assign(ob.vertexCount, fakeINF);
			vector<int> p(ob.vertexCount, -1);
			for (int i = 0; i < ob.vertexCount; i++) {
				vector<pair<int, int>> pairs;
				vector<Edge> edges = ob.list_of_edges(i);

				for (int j = 0; j < edges.size(); j++) {
					pair<int, int> p(edges[j].v2, edges[j].weight);
					pairs.push_back(p);
				}

				adj.push_back(pairs);
			}
			bool hasNegativeCycle = LevitMinDist(ob, start, adj, minDistances, p);
			if (hasNegativeCycle) {
				cout << "Graph contains a negative cycle" << endl;
				return 0;
			}
		}

		if (arguments.d || arguments.b || arguments.t) {
			cout << "Shortest paths lengths: " << endl;
			for (int i = 0; i < minDistances.size(); i++) {
				if (start + 1 != i + 1) {
					if (minDistances[i] != fakeIntMax) {
						cout << start + 1 << " - " << i + 1 << ": " << minDistances[i] << endl;
					}
					else {
						cout << start + 1 << " - " << i + 1 << ": X" << endl;
					}
				}
			}
		}

		break;
	}
	case 7: {
		vector<Edge> ed = ob.list_of_edges();
		vector<vector<int>> pairDistances;
		bool hasCycle = JohnsonMinDist(ob, ed, pairDistances);

		if (hasCycle) {
			break;
		}
		else {
			if (hasNegative(ob)) {
				cout << "Graph contains edges with negative weight." << endl;
			}
			else
			{
				cout << "Graph does not contain edges with negative weight." << endl;
			}
			cout << "Shortest paths lengths:" << endl;
			for (int i = 0; i < pairDistances.size(); i++) {
				for (int u = 0; u < pairDistances[i].size(); u++) {
					if (i != u && pairDistances[i][u] != fakeINF) {
						cout << i + 1 << " - " << u + 1 << " : " << pairDistances[i][u] << endl;
					}
				}
			}
		}

		break;
	}
		  // case 8 обрабатываем отдельно, выше в if'е
	case 9: {

		break;
	}
	case 10: {
		int sourceNum = -1;
		int sinkNum = -1;
		bool source = false;
		bool sink = false;
		for (int i = 0; i < ob.vertexCount; i++) {
			int j;
			for (j = 0; j < ob.vertexCount; j++) {
				if (ob.matrix[i][j] != 0) break;
			}
			if (j == ob.vertexCount) {
				sinkNum = i;
			}
		}
		
		for (int i = 0; i < ob.vertexCount; i++) {
			int j;
			for (j = 0; j < ob.vertexCount; j++) {
				if (ob.matrix[j][i] != 0) break;
			}
			if (j == ob.vertexCount) {
				sourceNum = i;
			}
		}

		cout << endl;
		
		int res = 0;
		vector<vector<int>> rGraph;
		vector<int> parent(ob.vertexCount);
		res = fordFulkerson(ob, sourceNum, sinkNum, parent, rGraph);
		cout << res << " - maximum flow from " << sourceNum + 1 << " to " << sinkNum + 1 << ". " << endl;

		vector<Edge> edges = ob.list_of_edges();
		for (int i = 0; i < edges.size(); i++) {
			cout << edges[i].v1 + 1 << " " << edges[i].v2 + 1 << " " << edges[i].weight - rGraph[edges[i].v1][edges[i].v2] << "/" << edges[i].weight << endl;
		}



		//int res = fordFulkerson(ob, source - 1, sink - 1);
		//cout << res << endl;
		break;
	}
	}
}