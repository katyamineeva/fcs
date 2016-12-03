#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

void readData(vector<vector<int>>& graph, vector<int>& inCount) {
    ifstream fin("input.txt");
    int n = 0;
    fin >> n;
    inCount.resize(n, 0);
    graph.resize(n, {});
    int m = 0;
    fin >> m;

    int v = 0;
    int u = 0;

    for (int i = 0; i < m; ++i) {
        fin >> v >> u;
        --v;
        --u;
        graph[v].push_back(u);
        inCount[u] += 1;
    }
    fin.close();
}


void printVect(vector<int>& v) {
    for (auto elem : v) {
        cout << elem + 1 << ' ';
    }
    cout << endl;
}

bool topSort(vector<vector<int>>& graph, vector<int>& inCount, vector<int>& active) {
    int cntVertex = graph.size();
    for (int i = 0; i < cntVertex; ++i) {
        if (inCount[i] == 0) {
            active.push_back(i);
        }
    }
    int curInd = 0;
    int curVertex = 0;
    while (active.size() != cntVertex) {
        if (curInd >= active.size()) {
            return false;
        }
        curVertex = active[curInd];

        for (auto vertex : graph[curVertex]) {
            --inCount[vertex];
            if (inCount[vertex] == 0) {
                active.push_back(vertex);
            }
        }
        ++curInd;
    }
    return true;
}


int main() {
    vector<vector<int>> graph;
    vector<int> inCount;
    readData(graph, inCount);
    vector<int> active;

    if (topSort(graph, inCount, active)) {
        printVect(active);
    } else {
        cout << -1;
    }
    return 0;
}
