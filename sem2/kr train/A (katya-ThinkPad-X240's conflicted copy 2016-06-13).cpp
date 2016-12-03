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
using std::sort;


class Dsu {
private:
    vector<int> parent;
    size_t cntComponent;
public:
    Dsu() {
    }

    Dsu(int n) {
        for (int i = 0; i < n; ++i) {
            parent.push_back(i);
        }
    }

    getParent(int a) {
        if (parent[a] != a) {
            int parent = getParent(parent[a]);
            parent[a] = parent;
        } else {
            return a;
        }
    }

    join(int a, int b) {
        a = getParent(a);
        b = getParent(b);
        parent[a] = parent[b];
    }
}

void readData(vector<vector<long long>>& edges, int& cntVertex) {
    ifstream fin("input.txt");
    int m = 0;

    fin >> cntVertex >> m;

    long long u = 0;
    long long v = 0;
    long long price = 0;

    for (int i = 0; i < m; ++i) {
        fin >> u >> v >> price;
        edges.push_back({price, u, v});
    }

    edges.sort();

    fin.close();
}


void mst(vector<vector<long long>>& edges, int cntVertex) {
    Dsu sets(cntVertex);
    int u = 0;
    int v = 0;
    long long price = 0;
    long long minCost;

    for (auto edge : edges) {
        price = edge[0];
        u = edge[1];
        v = edge[2];

        if (sets.getParent(u) != sets.getParent(v)) {
            minCost += price;
            sets.join(u, v);
        }
    }
    cout >> minCost;
}

int main() {
    mst();
    return 0;
}
