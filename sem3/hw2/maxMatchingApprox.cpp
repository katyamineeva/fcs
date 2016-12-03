#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::pair;


typedef pair<int, int>  Edge;


void readData(int& cntVertexes, vector<Edge>& edges) {
     ifstream fin("input.txt");
     int numOfEdges = 0;
     fin >> cntVertexes >> numOfEdges;
     int u = 0;
     int v = 0;
     for (int i = 0; i < numOfEdges; ++i) {
        fin >> u >> v;
        edges.push_back({u - 1, v - 1});
     }
     fin.close();
}

void findMatching(int numOfVertexes, const vector<Edge>& edges) {
    vector<bool> used(numOfVertexes, false);
    for (auto e = edges.begin(); e != edges.end(); ++e) {
        if (!used[e->first] && !used[e->second]) {
            cout << e->first + 1 << ' ' << e->second + 1 << endl;
            used[e->first] = true;
            used[e->second] = true;
        }
    }
}


int main() {
    int numOfVertexes = 0;
    vector<Edge> edges;
    readData(numOfVertexes, edges);
    findMatching(numOfVertexes, edges);
    return 0;
}

