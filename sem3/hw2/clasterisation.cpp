#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <vector>
#include <ctime>
#include <unordered_map>


using std::cout;
using std::vector;
using std::ifstream;
using std::max;
using std::sort;
using std::swap;
using std::unordered_map;

using String = vector<bool>;
using Number = unsigned int;
//using Map = unordered_map<Number, int>;
using Map = unordered_map<String, int>;


class Dsu {
private:
    mutable vector<int> parent;
    vector<int> rank;
    size_t dsc = 0;

public:
    Dsu() {
    }

    template<typename T>
    explicit Dsu(T n) {
        for (T i = 0; i < n; ++i) {
            parent.push_back(static_cast<int>(i));
        }
        rank.resize(n, 0);
        dsc = static_cast<int>(n);
    }

    void insert() {
        parent.push_back(parent.size());
        rank.push_back(0);
        ++dsc;
    }

    size_t size() const {
        return parent.size();
    }

    size_t disjoint_sets_count() const {
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
        --(this->dsc);
        return true;
    }
};



/// if using Numbers in Map (vector<bool> is faster)

/*
String numToStr(Number num) {
    String str = {};
    while (num > 0) {
        str.push_back(num % 2);
        num /= 2;
    }
    std::reverse(str.begin(), str.end());
    return str;
}

Number strToNum(String& str) {
    Number num = 0;
    for (auto i : str) {
        num *= 2;
        num += static_cast<Number>(i);
    }
    return num;
}



void joinNeighbour(int index, String neighbour, const Map& data, Dsu& clusters) {
    auto neighbourIt = data.find(strToNum(neighbour));
    if (neighbourIt != data.end()) {
        clusters.join(index, neighbourIt->second);
    }
}

void joinNeighbours(Number num, int strInd, const Map& data, Dsu& clusters) {
    String neighbour = numToStr(num);
    for (int i = 0; i < neighbour.size(); ++i) {
        neighbour[i] = !neighbour[i];
        joinNeighbour(strInd, neighbour, data, clusters);
        for (int j = i + 1; j < neighbour.size(); ++j) {
            neighbour[j] = !neighbour[j];
            joinNeighbour(strInd, neighbour, data, clusters);
            neighbour[j] = !neighbour[j];
        }
        neighbour[i] = !neighbour[i];
    }
}
*/

void joinNeighbour(int index, String& neighbour, Map& data, Dsu& clusters) {
    auto neighbourIt = data.find(neighbour);
    if (neighbourIt != data.end()) {
        clusters.join(index, neighbourIt->second);
    }
}

void joinNeighbours(String& str, int strInd, Map& data, Dsu& clusters) {
    String neighbour = str;
    for (int i = 0; i < neighbour.size(); ++i) {
        neighbour[i] = !neighbour[i];
        joinNeighbour(strInd, neighbour, data, clusters);
        for (int j = i + 1; j < neighbour.size(); ++j) {
            neighbour[j] = !neighbour[j];
            joinNeighbour(strInd, neighbour, data, clusters);
            neighbour[j] = !neighbour[j];
        }
        neighbour[i] = !neighbour[i];
    }
}


int maxClustersNum(Map& data) {
    int n = 0;
    int m = 0;
    Dsu clusters;

    ifstream fin("big_test.txt");
    fin >> n >> m;

    String str(m, 0);
    //Number num = 0;
    int counter = 0;
    char tmp = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> tmp;
            str[j] = (tmp == '1');
        }
        //num = strToNum(str);
        if (data.find(str) == data.end()) {
            data[str] = counter;
            ++counter;
            clusters.insert();
            joinNeighbours(str, data.size() - 1, data, clusters);
        }
    }
    fin.close();
    return clusters.disjoint_sets_count();}


int main() {
    double start = clock();
    Map data;
    cout << maxClustersNum(data);
    cout << "\n time: " << (clock() - start) / CLK_TCK;
    return 0;
}
