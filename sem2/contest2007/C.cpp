#include<iostream>
#include<vector>

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

int main() {
    vector<int> v1, v2;
    readData(v1);
    readData(v2);
    vector<int> ans(v1.size() + v2.size());
    myMerge(v1.begin(), v1.end(), v2.begin(), v2.end(), ans.begin());
    writeData(ans);
    return 0;
}
