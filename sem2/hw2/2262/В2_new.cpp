#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>

int INF = 57000;

using std::cout;
using std::ifstream;
using std::vector;
using std::queue;
using std::map;
using std::pair;
using std::set;
using std::max;
using std::min;

typedef map<int, set<pair<int, int>>> CityInfo;

// key - previous vertex
// value - set which contains pairs (length, petrol)

void readData(vector<vector<int>>& graph,
              vector<int>& petrol,
              int& start,
              int& finish,
              vector<int>& inCount) {
    ifstream fin("input.txt");
    int n = 0;
    int m = 0;
    fin >> n >> m;

    petrol.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> petrol[i];
    }

    vector<int> pattern(n, INF);
    graph.resize(n, pattern);
    int u = 0;
    int v = 0;
    int price = 0;
    inCount.resize(n, 0);

    for (int i = 0; i < m; ++i) {
        fin >> u >> v >> price;
        graph[u - 1][v - 1] = price;
        ++inCount[v];
    }

    fin >> start >> finish;
    --start;
    --finish;
}


void topSort(vector<vector<int>>& graph, vector<int>& inCount, vector<int>& active) {
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

void findOptSolution(vector<vector<int>>& graph, vector<int> petrol, int start, int finish, vector<int>& inCount) {
    vector<int> topSortedGraph;
    topSort(graph, inCount)
    vector<CityInfo> dp;
    queue
}

int main() {
    vector<vector<int>> graph;
    vector<int> petrol;
    int start = 0;
    int finish = 0;
    vector<int> inCount;
    readData(graph, petrol, start, finish, inCount);
    return 0;
}

