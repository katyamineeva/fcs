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


void readData(vector<vector<bool>>& field, int& aNum, int& bNum, int& cNum) {
    ifstream fin("input.txt");

    int hight = 0;
    int width = 0;

    fin >> hight >> width;

    vector<bool> pattern(width + 2, false);
    field.resize(hight + 2, pattern);

    char cell = 0;
    int cellNum = 0;

    for (int i_ind = 1; i_ind < hight + 1; ++i_ind) {
        for (int j_ind = 1; j_ind < width + 1; ++j_ind) {
            fin >> cell;
            cellNum = i_ind * (width + 2) + j_ind;
            if (cell != '#') {
                field[i_ind][j_ind] = true;
            }
            if (cell == 'A') {
                aNum = cellNum;
            }
            if (cell == 'B') {
                bNum = cellNum;
            }
            if (cell == 'C') {
                cNum = cellNum;
            }
        }
    }
    fin.close();
}


void addToNetwork(vector<map<int, int>>& residualNetwork, int x_coord, int y_coord) {
    int xIn = x_coord * 2 + 1;
    int xOut = x_coord * 2;
    int yIn = y_coord * 2 + 1;
    int yOut = y_coord * 2;

    residualNetwork[xIn][xOut] = 1;

    residualNetwork[yIn][yOut] = 1;

    residualNetwork[xOut][yIn] = 1;
    residualNetwork[yOut][xIn] = 1;
}

void createNetwork(vector<map<int, int>>& residualNetwork,
                   vector<vector<bool>>& field, int aNum, int bNum, int cNum) {
    int hight = field.size();
    int width = field[0].size();
    residualNetwork.resize(width * hight * 2 + 1);

    int centerNum = 0;
    int leftNum = 0;
    int rightNum = 0;
    int topNum = 0;
    int bottomNum = 0;


    for (int i_ind = 1; i_ind < hight - 1; ++i_ind) {
        for (int j_ind = 1; j_ind < width - 1; ++j_ind) {
            if (!field[i_ind][j_ind]) {
                continue;
            }

            centerNum = i_ind * width + j_ind;
            leftNum = i_ind * width + j_ind - 1;
            rightNum = i_ind * width + j_ind + 1;
            topNum = (i_ind - 1) * width + j_ind;
            bottomNum = (i_ind + 1) * width + j_ind;

            if (field[i_ind][j_ind - 1]) {
                addToNetwork(residualNetwork, centerNum, leftNum);
            }

            if (field[i_ind][j_ind + 1]) {
                addToNetwork(residualNetwork, centerNum, rightNum);
            }

            if (field[i_ind - 1][j_ind]) {
                addToNetwork(residualNetwork, centerNum, topNum);
            }

            if (field[i_ind + 1][j_ind]) {
                addToNetwork(residualNetwork, centerNum, bottomNum);
            }
        }
    }
    int start = 0;
    residualNetwork[start][bNum * 2 + 1] = 2;

    residualNetwork[bNum * 2 + 1][bNum * 2] = 2;

    int finish = residualNetwork.size() - 1;

    residualNetwork[aNum * 2][finish] = 1;
    residualNetwork[cNum * 2][finish] = 1;
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
    vector<vector<bool>> field;
    vector<map<int, int>> residualNetwork;
    int aNum = 0;
    int bNum = 0;
    int cNum = 0;

    readData(field, aNum, bNum, cNum);
    createNetwork(residualNetwork, field, aNum, bNum, cNum);
    int start = 0;
    int finish = residualNetwork.size() - 1;

    if (edmondsKarp(residualNetwork, start, finish) == 2) {
        cout << "Yes";
    } else {
        cout << "No";
    }
}


int main() {
    getMaxFlow();
    return 0;
}


