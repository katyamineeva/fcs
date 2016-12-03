#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using std::ifstream;
using std::cout;
using std::endl;
using std::sort;
using std::vector;
using std::max;

ifstream fin("input.txt");

void readData(vector<int>& diegoCollection) {
    int n = 0;
    fin >> n;

    vector<int> tmpVect(n);
    for (int i = 0; i < n; ++i) {
        fin >> tmpVect[i];
    }
    sort(tmpVect.begin(), tmpVect.end());

    int prevElem = -1;
    for (auto elem : tmpVect) {
        if (elem != prevElem) {
            diegoCollection.push_back(elem);
            prevElem = elem;
        }
    }
}


int binSearch(int lowerBound, vector<int>& diegoCollection) {
    if (diegoCollection[0] >= lowerBound || diegoCollection.size() == 0) {
        return 0;
    }
    if (diegoCollection[diegoCollection.size() - 1] < lowerBound) {
        return diegoCollection.size();
    }
    int left = 0;
    int right =  diegoCollection.size();
    int mid = (left + right) / 2;
    while (right - left > 1) {
        if (diegoCollection[mid] == lowerBound) {
            return mid;
        }
        if (diegoCollection[mid] < lowerBound) {
            left = mid;
        } else {
            right = mid;
        }
        mid = (left + right) / 2;
    }
    return left + 1;
}


void dealWithCollectioners(vector<int>& diegoCollection) {
    int cntCollectioners = 0;
    fin >> cntCollectioners;

    int lowerBound = 0;
    for (int i = 0; i < cntCollectioners; ++i) {
        fin >> lowerBound;
        cout << binSearch(lowerBound, diegoCollection) << endl;
    }
    fin.close();
}

int main() {
    vector<int> diegoCollection;
    readData(diegoCollection);
    dealWithCollectioners(diegoCollection);
    return 0;
}
