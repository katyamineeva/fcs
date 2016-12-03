#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#include <limits.h>
#include <algorithm>


using std::cout;
using std::vector;
using std::ifstream;
using std::pair;
using std::min;
using std::max;
using std::sort;

const int INF = INT_MAX;

void readData(vector<int>& inmerge) {
    ifstream fin("input.txt");
    int n = 0;
    fin >> n;
    inmerge.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> inmerge[i];
    }
    int newSize = 1;
    while (newSize < inmerge.size()) {
        newSize = newSize * 2;
    }
    inmerge.resize(newSize, INF);
    fin.close();
}

void printVect(vector<int>& v) {
    for (int elem : v) {
        cout << elem << " ";
    }
    cout << '\n';
}

void copyFromBuff(vector<int>& inmerge, vector<int>& buff, int start) {
    for (int i = 0; i < buff.size(); ++i) {
        inmerge[start + i] = buff[i];
    }
}

long long calculeteInMerge(vector<int>& inmerge, int start, int mid, int finish) {
    long long cntInv = 0;
    vector<int> buff(finish - start);
    int i = 0;
    int j = 0;
    while ((start + i < mid) && (mid + j < finish)) {
        if (inmerge[start + i] <= inmerge[mid + j]) {
            buff[i + j] = inmerge[start + i];
            ++i;
        } else {
            buff[i + j] = inmerge[mid + j];
            ++j;
            cntInv = cntInv + (mid - start) - i;
        }
    }
    while (start + i < mid) {
        buff[j + i] = inmerge[start + i];
        ++i;
    }
    while (mid + j < finish) {
        buff[i + j] = inmerge[mid + j];
        ++j;
    }
    copyFromBuff(inmerge, buff, start);
    return cntInv;
}


    /*
    int newSize = 1;
    while (newSize < inmerge.size()) {
        newSize = newSize * 2;
    }
    inmerge.resize(newSize, INF);
    */

long long calculeteCntInv(vector<int>& inmerge, int start, int finish) {
    if (finish - start < 2) {
        return 0;
    }
    if (finish - start == 2) {
        if (inmerge[start] <= inmerge[start + 1]) {
            return 0;
        } else {
            return 1;
        }
    }

    int mid = start + (finish - start) / 2;
    cout << start << " " << mid << " " << finish   << '\n';
    calculeteCntInv(inmerge, start, mid);
    calculeteCntInv(inmerge, mid, finish);
    return 0;
}

int main() {
    vector<int> inmerge;
    readData(inmerge);
    printVect(inmerge);
    cout << calculeteCntInv(inmerge, 0, inmerge.size());
    return 0;
}
