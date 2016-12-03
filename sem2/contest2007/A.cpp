#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;
using std::swap;

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

void maxToEnd(iter itBegin, iter itEnd) {
    auto itMax = itBegin;
    for (auto i = itBegin; i != itEnd; ++i) {
        if (*i > *itMax) {
            itMax = i;
        }
    }
    if (itBegin != itEnd) {
        swap(*itMax, *(itEnd - 1));
    }
}

int main() {
    vector<int> data;
    readData(data);
    maxToEnd(data.begin(), data.end());
    writeData(data);
    return 0;
}
