#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

int INF = 57000;

using std::cout;
using std::ifstream;
using std::vector;
using std::queue;
using std::max;
using std::min;

void readData(vector<vector<int>>& graph, vector<int>& petrol, int& start, int& finish) {
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

    for (int i = 0; i < m; ++i) {
        fin >> u >> v >> price;
        graph[u - 1][v - 1] = price;
    }

    fin >> start >> finish;
    --start;
    --finish;
}

void recoverAnswer(int finish,
                   vector<vector<int>>& graph,
                   vector<int>& petrol,
                   vector<int>& wayLen,
                   vector<int>& prevVertex) {
    if (wayLen[finish] >= INF) {
        cout << -1;
    } else {
        cout << wayLen[finish] << '\n';
        vector<int> way;
        way.push_back(finish);
        while (prevVertex[way[way.size() - 1]] != -1) {
            way.push_back(prevVertex[way[way.size() - 1]]);
        }
        vector<int> takePetrol(graph.size());
        int petrolNeed = 0;


        for (int i = 1; i < way.size(); ++i) {
            takePetrol[way[i]] = min(petrol[way[i]], graph[way[i]][way[i - 1]] + petrolNeed);
            petrolNeed = max(0, graph[way[i]][way[i - 1]] + petrolNeed - petrol[way[i]]);
        }

        for (int i = 0; i < graph.size(); ++i) {
            cout << takePetrol[i] << ' ';
        }
        cout << '\n';

        cout << way.size() << '\n';
        for (int i = way.size() - 1; i >= 0; --i) {
            cout << way[i] + 1 << '\n';
        }
    }
}

void getOptSolution(vector<vector<int>>& graph, vector<int>& petrol, int start, int finish) {


int main() {
    vector<vector<int>> graph;
    vector<int> petrol;
    int start = 0;
    int finish = 0;
    readData(graph, petrol, start, finish);
    getOptSolution(graph, petrol, start, finish);
}
