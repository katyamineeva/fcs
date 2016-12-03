#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <utility>
#include <vector>

using std::cout;
using std::vector;
using std::ifstream;
using std::pair;
using std::min;
using std::max;
using std::sort;
using std::swap;

int INF = INT_MAX;

typedef pair<int, int> pii;
typedef pair<int, size_t> node;



class Heap {
private:
    vector<node> tree;
    vector<int> indByKey;

public:
    Heap() {
    }

    Heap(int length, size_t value = 0) {
        for (int i = 0; i < length; ++i) {
            tree.push_back({value, i});
            indByKey.push_back(i);
        }
    }

    Heap(std::initializer_list<int> lst) {
        size_t curNum = 0;
        for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
            tree.push_back({static_cast<size_t>(*iter), curNum});
            ++curNum;
        }
        sort(tree.begin(), tree.end());

        indByKey.resize(tree.size());
        for (int i = 0; i < tree.size(); ++i) {
            indByKey[tree[i].second] = i;
        }
    }


    template<typename T>
    Heap(T lstBegin, T lstEnd) {
        int curNum = 0;
        for (T i = lstBegin; i != lstEnd; ++i) {
            tree.push_back({static_cast<size_t>(*i), curNum});
            ++curNum;
        }
        sort(tree.begin(), tree.end());
        indByKey.resize(tree.size());
        for (int i = 0; i < tree.size(); ++i) {
            indByKey[tree[i].second] = i;
        }
    }


    bool empty() const {
        return tree.empty();
    }

    size_t size() const {
        return tree.size();
    }

    size_t top() const {
        if (this->empty()) {
            throw std::exception();
        }
        return tree[0].second;
    }

    int minValue() const {
        return tree[0].first;
    }

    int valueByKey(size_t key) const {
        int ind = indByKey[key];
        if (ind < 0) {
            return ind;
        }
        return tree[ind].first;
    }

    void siftDown(int ind) {
        int curInd = ind;
        int leftChildInd = 0;
        int rightChildInd = 0;
        size_t leftChildVal = 0;
        size_t rightChildVal = 0;
        size_t curVal = 0;

        while (curInd * 2 + 1 < this->size()) {
            leftChildInd = curInd * 2 + 1;
            rightChildInd = leftChildInd + 1;

            curVal = tree[curInd].first;
            leftChildVal = tree[leftChildInd].first;
            if (rightChildInd < this->size()) {
                rightChildVal = tree[rightChildInd].first;
            } else {
                rightChildVal = INF;
            }
            if (curVal <= min(leftChildVal, rightChildVal)) {
                break;
            }
            if (leftChildVal < min(curVal, rightChildVal)) {
                swap(tree[curInd], tree[leftChildInd]);
                swap(curInd, leftChildInd);
                indByKey[tree[leftChildInd].second] = leftChildInd;
                indByKey[tree[curInd].second] = curInd;

            } else {
                swap(tree[curInd], tree[rightChildInd]);
                swap(curInd, rightChildInd);
                indByKey[tree[rightChildInd].second] = rightChildInd;
                indByKey[tree[curInd].second] = curInd;
            }
        }
    }

    void pop() {
        if (this->empty()) {
            throw std::exception();
        }
        indByKey[tree[0].second] = -1;
        tree[0] = tree.back();
        indByKey[tree[0].second] = 0;
        tree.pop_back();
        this->siftDown(0);
    }

    void siftUp(int ind) {
        int curInd = ind;
        int parentInd = (ind - 1) / 2;
        while (curInd > 0 && tree[parentInd].first > tree[curInd].first) {
            swap(tree[curInd], tree[parentInd]);
            swap(curInd, parentInd);
            indByKey[tree[curInd].second] = curInd;
            indByKey[tree[parentInd].second] = parentInd;
            parentInd = (curInd - 1) / 2;
        }
    }

    void decrease_key(size_t key, int newValue) {
        tree[indByKey[key]].first = newValue;
        this->siftUp(indByKey[key]);
    }
};


void readData(vector<vector<pii>>& graph, int& start, int& finish) {
    ifstream fin("input.txt");

    int n = 0;
    int m = 0;
    fin >> n >> m;

    int u = 0;
    int v = 0;
    int price = 0;

    graph.resize(n, {});

    for (int i = 0; i < m; ++i) {
        fin >> u >> v;
        --u;
        --v;
        graph[u].push_back({v, 0});
        graph[v].push_back({u, 0});
    }

    int k = 0;
    fin >> k;
    for (int i = 0; i < k; ++i) {
        fin >> u >> v >> price;
        --u;
        --v;
        graph[u].push_back({v, price});
        graph[v].push_back({u, price});
    }
    fin >> start >> finish;
    --start;
    --finish;

    fin.close();
}


int dijkstra(vector<vector<pii>>& graph, int start, int finish) {
    size_t cntVertex = graph.size();
    Heap priorityQueue(cntVertex, INF);


    priorityQueue.decrease_key(start, 0);
    int curVertex = 0;
    int curDist = 0;
    int vertex = 0;
    int price = 0;
    while (!priorityQueue.empty() && priorityQueue.minValue() < INF) {
        curVertex = priorityQueue.top();
        curDist = priorityQueue.minValue();
        if (curVertex == finish) {
            return curDist;
        }
        priorityQueue.pop();
        for (auto edge : graph[curVertex]) {
            vertex = edge.first;
            price = edge.second;
            if (curDist + price < priorityQueue.valueByKey(vertex)) {
                priorityQueue.decrease_key(vertex, curDist + price);
            }
        }
    }
    return priorityQueue.valueByKey(finish);
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
