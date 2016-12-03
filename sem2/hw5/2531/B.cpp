#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <queue>
#include <map>


using std::cout;
using std::vector;
using std::ifstream;
using std::min;
using std::queue;
using std::map;


int INF = INT_MAX;


void createNetwork(vector<map<int, int>>& residualNetwork,
                   vector<int>& rowCapacities,
                   vector<int>& columnCapacities,
                   const vector<vector<int>>& table) {
    int n = rowCapacities.size();
    int m = columnCapacities.size();

    residualNetwork.resize(m * n + n + m + 2);

    int start = residualNetwork.size() - 2;
    int finish = residualNetwork.size() - 1;

    int vertex = 0;
    int capacity = 0;
    int rowVertex = 0;
    int columnVertex = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            vertex = i * m + j;
            capacity = table[i][j];
            rowVertex = m * n + i;
            columnVertex = m * n + n + j;
            if (capacity == -1) {
                residualNetwork[rowVertex][vertex] = INF;
                residualNetwork[vertex][columnVertex] = INF;
            } else {
                rowCapacities[i] -= capacity;
                columnCapacities[j] -= capacity;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        rowVertex = m * n + i;
        residualNetwork[start][rowVertex] = rowCapacities[i];
    }

    for (int j = 0; j < m; ++j) {
        columnVertex = m * n + n + j;
        residualNetwork[columnVertex][finish] = columnCapacities[j];
    }
}

bool checkTable(const vector<vector<int>>& table,
                const vector<int>& rowCapacities,
                const vector<int>& columnCapacities) {
    int n = table.size();
    int m = table[0].size();

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum = 0;
        for (int j = 0; j < m; ++j) {
            if (table[i][j] != -1) {
                sum += table[i][j];
            }
        }
        if (sum > rowCapacities[i]) {
            return false;
        }
    }

    for (int j = 0; j < m; ++j) {
        sum = 0;
        for (int i = 0; i < n; ++i) {
            if (table[i][j] != -1) {
                sum += table[i][j];
            }
        }
        if (sum > columnCapacities[j]) {
            return false;
        }
    }
    return true;
}

bool readData(vector<map<int, int>>& residualNetwork,
              vector<vector<int>>& table, int& n, int& m) {
    ifstream fin("input.txt");

    fin >> n >> m;

    vector<int> rowCapacities(n);
    for (int i = 0; i < n; ++i) {
        fin >> rowCapacities[i];
    }

    vector<int> columnCapacities(m);
    for (int i = 0; i < m; ++i) {
        fin >> columnCapacities[i];
    }

    vector<int> emptyRow(m, 0);
    table.resize(n, emptyRow);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> table[i][j];
        }
    }

    fin.close();

    if (!checkTable(table, rowCapacities, columnCapacities)) {
        return false;
    }
    createNetwork(residualNetwork, rowCapacities, columnCapacities, table);
    return true;
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


void edmondsKarp(vector<map<int, int>>& residualNetwork,
                vector<map<int, int>>& flow,
                int start, int finish) {
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
}


void getMaxFlow() {
    int n = 0;
    int m = 0;

    vector<map<int, int>> residualNetwork;
    vector<vector<int>> table;
    if (!readData(residualNetwork, table, n, m)) {
        cout << -1;
    } else {
        int start = residualNetwork.size() - 2;
        int finish = residualNetwork.size() - 1;

        vector<map<int, int>> flow(residualNetwork.size());
        edmondsKarp(residualNetwork, flow, start, finish);

        int rowVertex = 0;
        int vertex = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                rowVertex = n * m + i;
                vertex = i * m + j;
                if (table[i][j] == -1) {
                    cout << flow[rowVertex][vertex] << ' ';
                } else {
                    cout << table[i][j] << ' ';
                }
            }
            cout << '\n';
        }
    }
}

int main() {
    getMaxFlow();
    return 0;
}
