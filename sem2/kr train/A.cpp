#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <limits.h>
#include <algorithm>


using std::cout;
using std::vector;
using std::ifstream;
using std::pair;
using std::min;
using std::max;
using std::sort;


class Dsu {
private:
    vector<long long> parent;
public:
    Dsu() {
    }

    Dsu(long long n) {
        for (int i = 0; i < n; ++i) {
            parent.push_back(i);
        }
    }

    long long getParent(long long a) {

        if (parent[a] != a) {
            long long parentA = this->getParent(parent[a]);
            parent[a] = parentA;
        }
        return parent[a];
    }

    bool join(long long a, long long b) {
        a = this->getParent(a);
        b = this->getParent(b);
        parent[a] = parent[b];
    }
};

void readData(vector<vector<long long>>& edges, int& cntVertex) {
    ifstream fin("input.txt");
    int m = 0;

    fin >> cntVertex >> m;

    long long u = 0;
    long long v = 0;
    long long price = 0;

    for (int i = 0; i < m; ++i) {
        fin >> u >> v >> price;
        --u;
        --v;
        edges.push_back({price, u, v});
    }

    sort(edges.begin(), edges.end());

    fin.close();
}

void mst(vector<vector<long long>>& edges, int cntVertex) {
    Dsu sets(cntVertex);
    int u = 0;
    int v = 0;
    long long price = 0;
    long long minCost = 0;

    for (vector<long long> edge : edges) {
        price = edge[0];
        u = edge[1];
        v = edge[2];

        if (sets.getParent(u) != sets.getParent(v)) {
            minCost += price;
            sets.join(u, v);
        }
    }
    cout << minCost;
}

int main() {
    vector<vector<long long>> edges;
    int cntVertex = 0;
    readData(edges, cntVertex);
    mst(edges, cntVertex);
    return 0;
}
