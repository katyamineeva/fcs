#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <limits.h>

using std::cout;
using std::vector;
using std::ifstream;
using std::pair;
using std::min;
using std::max;

int INF = INT_MAX;

typedef pair<int,int> pii;

void readData(vector<vector<pii>>& graph, int& start, int& finish) {
    ifstream fin("input.txt");

    int n = 0;
    fin >> n >> start >> finish;
    --start;
    --finish;

    int price;
    graph.resize(n, {});

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> price;
            if (price > 0) {
                graph[i].push_back({j, price});
            }
        }
    }

    fin.close();
}

int choose(vector<int>& dist, vector<bool>& used) {
    int ans = -1;
    int minDist = INF;
    for (int i = 0; i < dist.size(); ++i) {
        if (!used[i] && dist[i] < minDist) {
            ans = i;
            minDist = dist[i];
        }
    }
    return ans;
}

int dijkstra(vector<vector<pii>>& graph, int start, int finish) {
    int cntVertex = graph.size();
    vector<int> dist(cntVertex, INF);
    vector<bool> used(cntVertex, false);

    dist[start] = 0;
    int curVertex = 0;
    int vertex = 0;
    int price = 0;

    for (int i = 0; i < cntVertex; ++i) {
        curVertex = choose(dist, used);
        if (curVertex == -1) {
            break;
        }
        used[curVertex] = true;
        for (auto edge : graph[curVertex]) {
            vertex = edge.first;
            price = edge.second;
            dist[vertex] = min(dist[vertex], dist[curVertex] + price);
        }
    }
    return dist[finish];
}

int calculate_min_cost() {
    vector<vector<pii>> graph;
    int start = 0;
    int finish = 0;
    readData(graph, start, finish);
    int ans = dijkstra(graph, start, finish);
    if (ans == INF) {
        return -1;
    }
    return ans;
}

int main() {
    cout << calculate_min_cost();
    return 0;
}
