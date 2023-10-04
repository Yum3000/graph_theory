#include "Graph.h"
#include <cmath>
#include <vector>
#include <iostream>


using namespace std;

bool createsMST(int u, int v, vector<bool> inMST) {
    if (u == v)
        return false;
    if (inMST[u] == false && inMST[v] == false)
        return false;
    else if (inMST[u] == true && inMST[v] == true)
        return false;
    return true;
}

vector<vector<int>> PrimMST(Graph graph) {

    vector<vector<int>> resMST;
    int INF = 100000;

    int** matrixSp = new int* [graph.vertexCount];
    for (int i = 0; i < graph.vertexCount; i++) {
        matrixSp[i] = new int[graph.vertexCount];
    }

    for (int i = 0; i < graph.vertexCount; i++) {
        for (int j = 0; j < graph.vertexCount; j++) {
            if (graph.matrix[i][j] == 0) {
                matrixSp[i][j] = INF;
            }
            else {
                matrixSp[i][j] = graph.matrix[i][j];
            }
        }
    }

    vector<bool> inMST(graph.vertexCount, false);
    inMST[0] = true;
    int edgeNo = 0, MSTcost = 0;
    
    while (edgeNo < graph.vertexCount - 1) {
        vector<int> curMST;
        int min = INF, a = -1, b = -1;
        for (int i = 0; i < graph.vertexCount; i++) {
            for (int j = 0; j < graph.vertexCount; j++) {
                if (matrixSp[i][j] < min) {
                    if (createsMST(i, j, inMST)) {
                        min = matrixSp[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        if (a != -1 && b != -1) {
            
            //std::cout << "Edge " << edgeNo+1 << " : (" << a + 1<< " , " << b + 1 << " ) : cost = " << min << endl;
            MSTcost += min;
            inMST[b] = inMST[a] = true;
            edgeNo++;

            curMST.push_back(a + 1);
            curMST.push_back(b + 1);
            curMST.push_back(min);
            
        }
        resMST.push_back(curMST);

    }
    cout << "Weight of spanning tree: " << MSTcost << endl;
    return resMST;
}

