#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>

using std::cout;
using std::vector;
using std::ifstream;
using std::min;
using std::queue;


int INF = INT_MAX;


void readData(vector<vector<int>>& residualNetwork) {
    ifstream fin("input.txt");

    int n = 0;
    int m = 0;

    fin >> n >> m;

    vector<int> pattern(n, 0);
    residualNetwork.resize(n, pattern);

    int u = 0;
    int v = 0;
    int capacity = 0;
    for (int i = 0; i < m; ++ i) {
        fin >> u >> v >> capacity;
        --u;
        --v;
        residualNetwork[u][v] = capacity;
    }

    fin.close();
}

void recoverPath(vector<int>& path, vector<int>& prevVertex, int lastVertex) {
    path.clear();

    int curVertex = lastVertex;
    while (prevVertex[curVertex] != curVertex) {
        path.push_back(curVertex);
        curVertex = prevVertex[curVertex];
    }
    path.push_back(curVertex);
    reverse(path.begin(), path.end());
}

int findAugmentingPath(int start,
                       int finish,
                       vector<vector<int>>& residualNetwork,
                       vector<int>& augmentingPath) {
    queue<int> q;
    vector<int> prevVertex(residualNetwork.size(), -1);

    q.push(start);
    prevVertex[start] = start;

    int curVertex = 0;
    while (!q.empty()) {
        curVertex = q.front();
        q.pop();
        for (int i = 0; i < residualNetwork.size(); ++i) {
            if (residualNetwork[curVertex][i] > 0 && prevVertex[i] == -1) {
                q.push(i);
                prevVertex[i] = curVertex;
            }
        }
    }

    if (prevVertex[finish] == -1) {
        return 0;
    }

    recoverPath(augmentingPath, prevVertex, finish);
    int curEdgeCapacity = 0;
    int pathCapacity = INF;

    for (int i = 0; i < augmentingPath.size() - 1; ++i) {
        curEdgeCapacity = residualNetwork[augmentingPath[i]][augmentingPath[i + 1]];
        pathCapacity = min(pathCapacity, curEdgeCapacity);
    }
    return pathCapacity;
}


int edmondsKarp(vector<vector<int>>& residualNetwork, int start, int finish) {
    vector<int> pattern(residualNetwork.size(), 0);
    vector<vector<int>> flow(residualNetwork.size(), pattern);

    vector<int> augmentingPath;
    int u = 0;
    int v = 0;
    int augmentingPathCapacity = findAugmentingPath(start, finish, residualNetwork, augmentingPath);

    while (augmentingPathCapacity > 0) {
        for (int i = 0; i < augmentingPath.size() - 1; ++i) {
            u = augmentingPath[i];
            v = augmentingPath[i + 1];
            flow[u][v] += augmentingPathCapacity;
            flow[v][u] -= augmentingPathCapacity;

            residualNetwork[u][v] -= augmentingPathCapacity;
            residualNetwork[v][u] += augmentingPathCapacity;
        }
        augmentingPathCapacity = findAugmentingPath(start, finish, residualNetwork, augmentingPath);
    }

    int flowCapacity = 0;
    for (int i = 0; i < flow.size(); ++i) {
        flowCapacity += flow[start][i];
    }
    return flowCapacity;
}

void getMaxFlow() {
    vector<vector<int>> residualNetwork;
    readData(residualNetwork);
    int start = 0;
    int finish = residualNetwork.size() - 1;
    cout << edmondsKarp(residualNetwork, start, finish);
}

int main() {
    getMaxFlow();
    return 0;
}

