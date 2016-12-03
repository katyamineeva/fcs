#include <iostream>
#include <fstream>
#include <vector>

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

bool dfs(int curVertex, vector<vector<int>>& graph, vector<int>& used, vector<int>& topSorted) {
    ++used[curVertex];

    ++used[curVertex];
}

int topSortByDFS(vector<vector<int>>& graph) {
    vector<int> used(graph.size(), -1);
    vector<int> topSorted;
    int curVertex = 0;
    while (curVertex < graph.size()) {
        while (used[curVertex] == 1) {
            ++curVertex;
        }
        if (!dfs(curVertex, graph, used, topSorted)) {
            cout << "-1";
            return 0;
        }
    }

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
