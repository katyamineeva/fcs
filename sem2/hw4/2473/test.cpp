#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <utility>
#include <vector>
#include <stack>

using std::cout;
using std::vector;
using std::ifstream;
using std::pair;
using std::min;
using std::max;
using std::sort;
using std::swap;
using std::stack;

int INF = INT_MAX;

typedef pair<int, int> pii;
typedef pair<int, size_t> node;


class DSU {
private:
    mutable vector<int> parent;
    mutable vector<int> rank;
    size_t dsc = 0;
public:
    DSU() {
    }

    template<typename T>
    explicit DSU(T n) {
        for (T i = 0; i < n; ++i) {
            parent.push_back(static_cast<int>(i));
        }
        rank.resize(n, 0);
        dsc = static_cast<size_t>(n);
    }

    size_t size() {
        return parent.size();
    }

    size_t disjoint_sets_count() {
        return dsc;
    }

    int find_parent(int a) const {
        if (parent[a] != a) {
            parent[a] = find_parent(parent[a]);
        }
        return parent[a];
    }

    bool are_joined(int a, int b) const {
        a = find_parent(a);
        b = find_parent(b);
        if (a == b) {
            return true;
        }
        return false;
    }

    bool join(int a, int b) {
        a = find_parent(a);
        b = find_parent(b);
        if (a == b) {
            return false;
        }
        if (rank[a] > rank[b]) {
            parent[b] = a;
        } else {
            parent[a] = b;
            if (rank[a] == rank[b]) {
                ++rank[b];
            }
        }
        --this->dsc;
        return true;
    }


};


void readData(vector<vector<int>>& edges) {
    ifstream fin("input.txt");

    int n = 0;
    int m = 0;
    fin >> n >> m;

    int marked = 0;
    int rightPrice = 0;
    int downPrice = 0;

    int firstMarkedVertex = 0;
    bool thereWasMarkedVertex = false;
    vector<bool> markedVertex(n * m, false);

    for (int i = 0; i < n * m; ++i) {
        fin >> marked;
        if (marked == 1) {
            markedVertex[i] = true;
            if (!thereWasMarkedVertex) {
                thereWasMarkedVertex = true;
                firstMarkedVertex = i;
            }
        }
        if ((i + 1) % m != 0) {
            fin >> rightPrice;
            edges.push_back({rightPrice, i, i + 1});
        }
        if (i < m * (n - 1)) {
            fin >> downPrice;
            edges.push_back({downPrice, i, i + m});
        }
    }
/*
    int i = 0;
    while (i < edges.size()) {
        if (markedVertex[edges[i][1]]) {
            edges[i][1] = firstMarkedVertex;
        }
        if (markedVertex[edges[i][2]]) {
            edges[i][2] = firstMarkedVertex;
        }
        if (edges[i][1] == edges[i][2]) {
            swap(edges[i], edges[edges.size() - 1]);
            edges.pop_back();
        }
        ++i;
    } */
    fin.close();
}
/*
    for (int i = 0; i < edges.size(); ++i) {
        cout << edges[i][1] << ' ' << edges[i][2] << ' ' << edges[i][0] << '\n';
    }


void readData(vector<vector<int>>& edges, int& cntVertex) {
    ifstream fin("input.txt");
    int n = 0;
    int m = 0;
    fin >> n >> m;
    cntVertex = n;

    int u = 0;
    int v = 0;
    int price = 0;

    for (int i = 0; i < m; ++i) {
        fin >> u >> v >> price;
        --u;
        --v;
        edges.push_back({price, u, v});
    }
    fin.close();
}

bool areConnected(int start, int finish, vector<vector<int>>& graph) {
    vector<bool> used(graph.size(), false);
    stack<int> myStack;
    myStack.push(start);
    used[start] = true;
    int curVertex = 0;
    while (!myStack.empty()) {
        curVertex = myStack.top();
        myStack.pop();
        for (auto vertex : graph[curVertex]) {
            if (!used[vertex]) {
                if (vertex == finish) {
                    return true;
                }
                myStack.push(vertex);
                used[vertex] = true;
            }
        }
    }
    return false;
}
*/

int kruskal(vector<vector<int>>& edges, int cntVertex) {
    sort(edges.begin(), edges.end());
    int minCost = 0;
    int u = 0;
    int v = 0;
    DSU forest(cntVertex);
    for (auto edge : edges) {
        u = edge[1];
        v = edge[2];
        if (!forest.are_joined(u, v)) {
            minCost += edge[0];
            forest.join(u, v);
        }
    }
    return minCost;
}

size_t calculate_answer() {
    vector<vector<int>> edges;
    int cntVertex = 0;
    readData(edges, cntVertex);
    size_t ans = kruskal(edges, cntVertex);
    return ans;
}

int main() {
    cout << calculate_answer();
    return 0;
}
