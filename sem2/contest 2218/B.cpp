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

int bfs(vector<vector<int>>& graph, vector<int>& used, int curVertex) {
    queue<int> myQueue;
    myQueue.push(curVertex);
    used[curVertex] = 0;
    while (!myQueue.empty()) {
        curVertex = myQueue.front();
        myQueue.pop();
        for (auto vertex : graph[curVertex]) {
            if (used[vertex] == -1) {
                myQueue.push(vertex);
                used[vertex] = (used[curVertex] + 1) % 2;
            }
            if (used[vertex] == used[curVertex]) {
                cout << "NO";
                return 0;
            }
        }
    }
    return 1;
}

int exploreGraph(vector<vector<int>>& graph) {
    vector<int> used(graph.size(), -1);
    int curInd = 0;
    while (curInd < graph.size()) {
        if (used[curInd] == -1) {
            int res = bfs(graph, used, curInd);
            if (res == 0) {
                return 0;
            }
        }
        while (curInd < graph.size() && used[curInd] != -1) {
            ++curInd;
        }
    }
    cout << "YES";
}


int main() {
    vector<vector<int>> graph;
    readData(graph);
    exploreGraph(graph);
    return 0;
}
