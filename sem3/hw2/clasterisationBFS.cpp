#include <fstream>
#include <iostream>
#include <limits.h>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <queue>

using std::cout;
using std::vector;
using std::ifstream;
using std::unordered_map;
using std::queue;

using String = vector<bool>;
using Map = unordered_map<String, int>;
using Graph = vector<vector<int>>;


void readData(Map& data) {
    int n = 0;
    int m = 0;

    ifstream fin("big_test.txt");
    fin >> n >> m;

    String str(m, 0);
    int counter = 0;
    char tmp = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> tmp;
            str[j] = (tmp == '1');
        }
        if (data.find(str) == data.end()) {
            data[str] = counter;
            ++counter;
        }
    }

    fin.close();
}

void connectNeighbour(int index, String neighbour, const Map& data, Graph& graph) {
    auto neighbourIt = data.find(neighbour);
    if (neighbourIt != data.end()) {
        graph[index].push_back(neighbourIt->second);
    }
}

void connectNeighbours(String str, int strInd, const Map& data, Graph& graph) {
    String neighbour = str;
    for (int i = 0; i < str.size(); ++i) {
        neighbour[i] = !neighbour[i];
        connectNeighbour(strInd, neighbour, data, graph);
        for (int j = i + 1; j < str.size(); ++j) {
            neighbour[j] = !neighbour[j];
            connectNeighbour(strInd, neighbour, data, graph);
            neighbour[j] = !neighbour[j];
        }
        neighbour[i] = !neighbour[i];
    }
}

Graph buildGraph(Map& data) {
    vector<int> emptyVect = {};
    Graph graph(data.size(), emptyVect);
    String str;
    int strInd = 0;
    for (auto it = data.begin(); it != data.end(); ++it) {
        str = it->first;
        strInd = it->second;
        connectNeighbours(str, strInd, data, graph);
    }
    return graph;
}

// BFS is faster
void dfs(int curVertex, const Graph& graph, vector<bool>& used) {
    used[curVertex] = true;
    for (int vertex : graph[curVertex]) {
        if (!used[vertex]) {
            dfs(vertex, graph, used);
        }
    }
}

void bfs(int curVertex, const Graph& graph, vector<bool>& used) {
    queue<int> vertexQueue;
    vertexQueue.push(curVertex);
    used[curVertex] = true;
    while (!vertexQueue.empty()) {
        curVertex = vertexQueue.front();
        vertexQueue.pop();
        for (int vertex : graph[curVertex]) {
            if (!used[vertex]) {
                used[vertex] = true;
                vertexQueue.push(vertex);
            }
        }
    }
}

int countConnectedComponent(const Graph& graph) {
    vector<bool> used(graph.size(), false);
    int cntConnectedComponent = 0;
    for (int i = 0; i < graph.size(); ++i) {
        if (!used[i]) {
            bfs(i, graph, used);
            ++cntConnectedComponent;
        }
    }
    return cntConnectedComponent;
}

int maxClustersNum(Map& data) {
    Graph graph = buildGraph(data);
    return countConnectedComponent(graph);
}

int main() {
    double start = clock();
    Map data;
    readData(data);
    cout << maxClustersNum(data);
    cout << "\n time: " << (clock() - start) / CLK_TCK;
    return 0;
}
