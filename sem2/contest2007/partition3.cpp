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


void writeData(vector<int>& data) {
    for (auto elem : data) {
        cout << elem << ' ';
    }
}

typedef vector<int>::iterator iter;
void printData(iter a, iter b) {
    for (auto i = a; i < b; ++i) {
        cout << *i << ' ';
    }
    cout << '\n';
}

iter partition3(iter itBegin, iter itEnd, int pivot) {
    if (itEnd - itBegin < 2) {
        return itBegin;
    }
    auto a = itBegin;
    auto b = itEnd;

    auto left = itBegin;    // left boarder of part of numbers which are equal to pivot
    auto right = itEnd;     // right boarder of part of numbers which are equal to pivot

    while (itBegin < itEnd) {
        while (*itBegin <= pivot && itBegin < itEnd) {

            if (*itBegin < pivot) {
                cout << "in if " << *itBegin << endl;
                swap(*itBegin, *left);
                ++left;
            }
            ++itBegin;
            printData(a, b);

        }
        while (*(itEnd - 1) > pivot && itBegin < itEnd) {
            --itEnd;
            --right;
        }
        if (*itBegin > *(itEnd - 1) && itBegin < itEnd) {
            cout << "swap " << *itBegin << " " << *(itEnd - 1) << endl;
            swap(*itBegin, *(itEnd - 1));
        }

    }
    return itEnd;
}


int main() {
    vector<int> data;
    readData(data);
    partition3(data.begin(), data.end(), 5);
    writeData(data);
    return 0;
}
