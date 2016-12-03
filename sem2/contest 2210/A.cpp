#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1000000000 + 8;

const int MOD = 1000000000 + 7;

void readData(vector<vector<int>>& graph, int& start, int& finish) {
    ifstream fin("input.txt");
    fin >> start;
    fin >> finish;
    --start;
    --finish;

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


int cntWays(vector<vector<int>>& graph, int start, int finish) {
    vector<int> lenWays(graph.size(), INF);
    vector<int> cntWays(graph.size(), 0);
    vector<bool> used(graph.size(), false);
    cntWays[start] = 1;
    lenWays[start] = 0;

    queue<int> myQueue;
    myQueue.push(start);
    used[start] = true;
    int curVertex = 0;
    while (!myQueue.empty()) {
        curVertex = myQueue.front();
        myQueue.pop();
        for (auto vertex : graph[curVertex]) {
            if (!used[vertex]) {
                myQueue.push(vertex);
                used[vertex] = true;
            }
            if (lenWays[vertex] > lenWays[curVertex] + 1) {
                lenWays[vertex] = lenWays[curVertex] + 1;
                cntWays[vertex] = cntWays[curVertex];
            } else {
                if (lenWays[vertex] == lenWays[curVertex] + 1) {
                    cntWays[vertex] += cntWays[curVertex];
                    cntWays[vertex] %= MOD;
                }
            }

        }
    }
    return cntWays[finish] % MOD;
}


int main() {
    int start = 0;
    int finish = 0;
    vector<vector<int>> graph;
    readData(graph, start, finish);
    cout << cntWays(graph, start, finish);
    return 0;
}
