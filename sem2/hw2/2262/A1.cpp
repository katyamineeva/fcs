#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>

using std::vector;
using std::string;
using std::cout;
using std::ifstream;
using std::stack;

bool flag = false;

void readData(vector<vector<short>>& graph) {
    ifstream fin("input.txt");

    int n = 0;
    fin >> n;
    graph.resize(n, {});

    string data;
    for (int i = 0; i < n - 1; ++i) {
        fin >> data;
        for (int j = 0; j < data.size(); ++j) {
            if (data[j] == 'S') {
                graph[i].push_back(i + j + 1);
            } else {
                graph[i + j + 1].push_back(i);
            }
        }
    }
    fin.close();
}


void thereIsCycle(short curVertex, vector<vector<short>>& graph, vector<short>& used) {
    used[curVertex] = 0;
    for (short vertex : graph[curVertex]) {
        if (used[vertex] == 0) {
            flag = true;
        }
        if (used[vertex] == -1) {
            thereIsCycle(vertex, graph, used);
        }
    }
    used[curVertex] = 1;
}


bool check(vector<vector<short>>& graph) {
    vector<short> used(graph.size(), -1);
    for (int start = 0; start < graph.size(); ++start) {
        if (used[start] == -1) {
            flag = false;
            thereIsCycle(start, graph, used);
            if (flag) {
                cout << "NO";
                return false;
            }
        }
    }
    cout << "YES";
}



int main() {
    vector<vector<short>> graph;
    readData(graph);
    check(graph);
    return 0;
}
