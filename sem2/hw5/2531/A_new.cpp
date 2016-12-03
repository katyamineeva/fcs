#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <map>
#include <string>

using std::cout;
using std::vector;
using std::ifstream;
using std::min;
using std::queue;
using std::map;
using std::string;


int INF = INT_MAX;


void readData(vector<map<int, int>>& residualNetwork) {
    ifstream fin("input.txt");

    int n = 0;
    int m = 0;

    fin >> n >> m;
    residualNetwork.resize(n);

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
                       vector<map<int, int>>& residualNetwork,
                       vector<int>& augmentingPath) {
    queue<int> q;
    vector<int> prevVertex(residualNetwork.size(), -1);

    q.push(start);
    prevVertex[start] = start;

    int curVertex = 0;
    int nextVertex = 0;
    int capacity = 0;

    while (!q.empty()) {
        curVertex = q.front();
        q.pop();
        for (auto elem : residualNetwork[curVertex]) {
            nextVertex = elem.first;
            capacity = elem.second;
            if (capacity > 0 && prevVertex[nextVertex] == -1) {
                q.push(nextVertex);
                prevVertex[nextVertex] = curVertex;
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



int edmondsKarp(vector<map<int, int>>& residualNetwork, int start, int finish) {

    vector<map<int, int>> flow(residualNetwork.size());

    vector<int> augmentingPath;
    int curVertex = 0;
    int nextVertex = 0;
    int augmentingPathCapacity = findAugmentingPath(start, finish, residualNetwork, augmentingPath);

    while (augmentingPathCapacity > 0) {
        for (int i = 0; i < augmentingPath.size() - 1; ++i) {
            curVertex = augmentingPath[i];
            nextVertex = augmentingPath[i + 1];

            flow[curVertex][nextVertex] += augmentingPathCapacity;
            flow[nextVertex][curVertex] -= augmentingPathCapacity;

            residualNetwork[curVertex][nextVertex] -= augmentingPathCapacity;
            residualNetwork[nextVertex][curVertex] += augmentingPathCapacity;
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
    vector<map<int, int>> residualNetwork;
    readData(residualNetwork);
    int start = 0;
    int finish = residualNetwork.size() - 1;
    cout << edmondsKarp(residualNetwork, start, finish);
}


int main() {
    getMaxFlow();
    return 0;
}


