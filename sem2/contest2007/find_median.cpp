#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::swap;
using std::endl;
using std::pair;

typedef vector<int>::iterator iter;


void readData(vector<int>& data) {
    int n = 0;
    cin >> n;
    data.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }
}

void writeData(vector<int>& data) {
    for (auto elem : data) {
        cout << elem << ' ';
    }
}

void insertionSort(iter itBegin, iter itEnd, int step) {
    for (auto i = itBegin + step; i < itEnd; i += step) {
        auto j = i;
        while (j > itBegin && *j < *(j - step)) {
            swap(*j, *(j - step));
            j -= step;
        }
    }
}

int findMedian(iter itBegin, iter itEnd, int step) {
    cout << "itBegin = " << *itBegin << " itEnd = " << *(itEnd - 1) << " step = " << step << endl;
    int length = itEnd - itBegin;
    if (length <= 5 * step) {
        vector<int> tmp;
        for (int i = 0; i < length; i += step) {
            tmp.push_back(*(itBegin + i));
        }
        insertionSort(tmp.begin(), tmp.end(), 1);
        return tmp[tmp.size() / 2];
    }

    for (int i = 0; i <= length / (step * 5); i += step) {
        insertionSort(itBegin + i * step, min(itBegin + (i + step) * step, itEnd), step);
    }
    return findMedian(itBegin + step * 5 / 2, min(itEnd, itEnd), step * 5);
}

int main() {
    vector<int> data;
    readData(data);
    cout << findMedian(data.begin(), data.end(), 1);
    return 0;
}
