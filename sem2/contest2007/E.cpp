#include<iostream>
#include<vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::swap;
using std::endl;

void readData(vector<int>& data) {
    int n = 0;
    cin >> n;
    data.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }
}
typedef vector<int>::iterator iter;

void printAns(iter itBegin, iter itEnd, iter itPivot) {
    cout << itPivot - itBegin << endl;
    cout << itEnd - itPivot << endl;
}

iter myPartition(iter itBegin, iter itEnd, int pivot) {
    if (itBegin == itEnd) {
        return itEnd;
    }

    while (itBegin != (itEnd - 1)) {
        while (*itBegin < pivot && itBegin != (itEnd - 1)) {
            ++itBegin;
        }
        while (*(itEnd - 1) >= pivot && itBegin != (itEnd - 1)) {
            --itEnd;
        }
        swap(*itBegin, *(itEnd - 1));
    }

    if (*itBegin >= pivot) {
        return itBegin;
    }
    return itEnd;
}

int main() {
    vector<int> data;
    readData(data);
    int pivot = 0;
    cin >> pivot;

    iter itPivot = myPartition(data.begin(), data.end(), pivot);
    printAns(data.begin(), data.end(), itPivot);

    return 0;
}
