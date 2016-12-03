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


pair<iter, iter> partition3(iter itBegin, iter itEnd, int pivot) {
    auto left = itBegin;    // left boarder of part of numbers which are equal to pivot
    auto right = itEnd;     // right boarder of part of numbers which are equal to pivot

    while (itBegin < itEnd) {
        while (*itBegin <= pivot && itBegin < itEnd) {
            if (*itBegin < pivot) {
                swap(*itBegin, *left);
                ++left;
            }
            ++itBegin;
        }

        while (*(itEnd - 1) > pivot && itBegin < itEnd) {
            --itEnd;
            --right;
        }

        if (*itBegin > *(itEnd - 1) && itBegin < itEnd) {
            swap(*itBegin, *(itEnd - 1));
        }
    }
    pair<iter, iter> ans(left, right);
    return ans;
}

void quickSort(iter itBegin, iter itEnd) {
    if (itBegin < itEnd) {
        int pivot = findMedian(itBegin, itEnd, 1);
        auto equalPart = partition3(itBegin, itEnd, pivot);
        quickSort(itBegin, equalPart.first);
        quickSort(equalPart.second, itEnd);
    }
}

int main() {
    vector<int> data;
    readData(data);
    quickSort(data.begin(), data.end());
    writeData(data);
    return 0;
}
