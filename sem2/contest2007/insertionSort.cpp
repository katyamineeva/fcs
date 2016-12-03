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


void insertionSort(iter itBegin, iter itEnd) {
    for (auto i = itBegin + 1; i < itEnd; ++i) {
        auto j = i;
        while (j > itBegin && *j < *(j - 1)) {
            swap(*j, *(j - 1));
            --j;
        }
    }
}

int main() {
    vector<int> data;
    readData(data);
    insertionSort(data.begin(), data.end());
    writeData(data);
    return 0;
}
