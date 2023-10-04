#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include "Graph.h"
#include "utils.h"

Graph::Graph(string file, DataType dataType) {
	vector<vector<int>> data;

	bool fileReadError = readFile(file, data);

	if (fileReadError) {
		std::cout << "Не удалось открыть файл." << endl;
		exit(1);
	}

	if (dataType == DataType::m) {
		vertexCount = data.size(); // число строк и столбцов
		matrix = new int* [vertexCount];
		for (int i = 0; i < vertexCount; i++) {
			matrix[i] = new int[vertexCount];
		}

		edgesCount = 0;

		//Считаем матрицу из файла
		for (int i = 0; i < vertexCount; i++) {
			for (int j = 0; j < vertexCount; j++) {
				matrix[i][j] = data[i][j];
				if (matrix[i][j] != 0) {
					edgesCount++;
				}
			}
		}

		if (!is_directed()) {
			edgesCount = edgesCount / 2;
		}

	} else if (dataType == DataType::e) {

		string str;
		int v1, v2, temp;

		bool have_weight = data[0].size() > 2;
		int maxVer = data[0][0];

		for (int i = 0; i < data.size(); i++) {
			if (data[i][0] > maxVer) {
				maxVer = data[i][0];
			}
			if (data[i][1] > maxVer) {
				maxVer = data[i][1];
			}
		}

		vertexCount = maxVer;

		matrix = new int* [vertexCount];
		for (int i = 0; i < vertexCount; i++) {
			matrix[i] = new int[vertexCount];
		}

		for (int i = 0; i < vertexCount; i++) {
			for (int j = 0; j < vertexCount; j++) {
				matrix[i][j] = 0;
			}
		}

		for (int i = 0; i < data.size(); i++) {
			for (int j = 0; j < data[i].size(); j++) {
				int v1 = data[i][0] - 1;
				int v2 = data[i][1] - 1;
				int weight = 1;
				if (have_weight) {
					weight = data[i][2];
				}
				matrix[v1][v2] = weight;
			}
		}
		
		edgesCount = data.size();

		if (!is_directed()) {
			edgesCount = data.size() / 2;
		}

	} else if (dataType == DataType::l) {

		vertexCount = data.size();

		int maxVer = data[0][0];

		for (int i = 0; i < vertexCount; i++) {
			for (int j = 0; j < data[i].size(); j++) {
				if (data[i][j] > maxVer) {
					maxVer = data[i][j];
				}
			}
		}

		if (maxVer > vertexCount) {
			vertexCount = maxVer;
		}

		int** x = new int* [vertexCount];
		for (int i = 0; i < vertexCount; i++) {
			x[i] = new int[vertexCount];
		}

		for (int i = 0; i < vertexCount; i++) {
			for (int j = 0; j < vertexCount; j++) {
				x[i][j] = 0;
			}
		}

		for (int i = 0; i < vertexCount; i++) {
			for (int j = 0; j < data[i].size(); j++) {
				int ver1 = i;
				int ver2 = data[i][j] - 1;
				x[ver1][ver2] = 1;
			}
		}

		matrix = x;
	}
}
