#include<iostream>
#include<vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::swap;
using std::endl;
using std::copy;

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

void myMerge(iter aBegin, iter aEnd, iter bBegin, iter bEnd, iter outBegin) {
    while ((aBegin != aEnd) && (bBegin != bEnd)) {
        if (*aBegin < *bBegin) {
            *outBegin = *aBegin;
            ++aBegin;
        } else {
            *outBegin = *bBegin;
            ++bBegin;
        }
        ++outBegin;
    }

    while (aBegin != aEnd) {
        *outBegin = *aBegin;
        ++aBegin;
        ++outBegin;
    }

    while (bBegin != bEnd) {
        *outBegin = *bBegin;
        ++bBegin;
        ++outBegin;
    }
}


void mergeSort(iter itBegin, iter itEnd) {
    int delta = itEnd - itBegin;
    if (delta > 1) {
        auto itMiddle = itBegin + 0.5 * delta;
        mergeSort(itBegin, itMiddle);
        mergeSort(itMiddle, itEnd);

        vector<int> buff(delta);
        myMerge(itBegin, itMiddle, itMiddle, itEnd, buff.begin());
        copy(buff.begin(), buff.end(), itBegin);
    }
}

int main() {
    vector<int> data;
    readData(data);
    mergeSort(data.begin(), data.end());
    writeData(data);
    return 0;
}
