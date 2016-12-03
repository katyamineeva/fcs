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

int INF = INT_MAX;

typedef pair<int,int> pii;
typedef pair<int, size_t> node;


class Heap {
private:
    vector<node> tree;
public:
    Heap() {
    }

    Heap(int length, int value = 0) {
        tree.resize(length, {value, 0});
    }

    template<typename T>
    Heap(T lstBegin, T lstEnd) {
        size_t curNum = 0;
        node tmp;
        for (T iter = lstBegin; iter != lstEnd; ++iter) {
            tmp = {static_cast<size_t>(*iter), curNum};
            tree.push_back(tmp);
            ++curNum;
        }
        sort(tree.begin(), tree.end());
    }

    Heap(std::initializer_list<int> lst) {
        size_t curNum = 0;
        for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
            tree.push_back({static_cast<size_t>(*iter), curNum});
            ++curNum;
        }
        sort(tree.begin(), tree.end());
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
                rightChildVal = tree[rightChildInd];
            } else {
                rightChildVal = INF;
            }

            if (curVal <= min(leftChildVal, rightChildVal)) {
                break;
            }
            if (leftChildInd < min(curVal, rightChildVal)) {
                swap(tree[curInd], tree[leftChildInd]);
                curInd = leftChildInd;
            } else {
                swap(tree[curInd], tree[rightChildInd]);
                curInd = rightChildInd;
            }
        }
    }

    void pop() {
        if (this->empty()) {
            throw std::exception();
        }
        tree[0] = tree.back();
        tree.pop_back();
        this->siftDown(0);
    }

};


int main() {
    return 0;
}
