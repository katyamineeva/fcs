#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

void readData(vector<vector<int>>& graph) {
    ifstream fin("input.txt");
    int n = 0;
    fin >> n;
    graph.resize(n, {});
    int m = 0;
    fin >> m;

    int v = 0;
    int u = 0;

    for (int i = 0; i < m; ++i) {
        fin >> v >> u;
        graph[v - 1].push_back(u - 1);
        graph[u - 1].push_back(v - 1);
    }
    fin.close();
}

void dfs(vector<vector<int>>& graph, vector<bool>& used, int curVertex) {
    used[curVertex] = true;
    for (auto vertex : graph[curVertex]) {
        if (!used[vertex]) {
            dfs(graph, used, vertex);
        }
    }
}

void printData(vector<bool> used) {
    int cnt = 0;
    for (int i = 0; i < used.size(); ++i) {
        if (used[i]) {
            cnt += 1;
        }
    }
    cout << cnt << endl;

    for (int i = 0; i < used.size(); ++i) {
        if (used[i]) {
            cout << i + 1 << ' ';
        }
    }
}

int main() {
    vector<vector<int>> graph;
    readData(graph);
    vector<bool> used(graph.size(), false);
    dfs(graph, used, 0);
    printData(used);
    return 0;
}
