#include <iostream>
#include<fstream>
#include <vector>
#include <algorithm>
#include <climits>

const long long INF = INT_MAX;

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

void readData(int& strLen, vector<int>& wordsLen) {
    int n = 0;
    ifstream fin("input.txt");

    fin >> strLen;
    fin >> n;
    wordsLen.resize(n + 1);
    wordsLen[0] = 0;
    int tmp = 0;
    for (int i = 0; i < n; ++i) {
        fin >> tmp;
        wordsLen[i + 1] = wordsLen[i] + tmp;
    }
    fin.close();
}

long long cntFine(int left, int right, int strLen, vector<int>& wordsLen) {
    long long res = strLen - (wordsLen[right + 1] - wordsLen[left]) - (right - left);
    if (res < 0) {
        return INF;
    }
    return res * res * res;
}


int optSolution(int strLen, vector<int>& wordsLen) {
    int n = wordsLen.size() - 1;
    if (n == 0) {
        return 0;
    }

    vector<long long> minFine(n, INF);
    vector<int> history(n, -1);
    long long newFine = 0;

    for (int i = n - 1; i >= 0; --i) {
        minFine[i] = cntFine(i, n - 1, strLen, wordsLen);
        for (int j = i + 1; j < n; ++j) {
            newFine = minFine[j] + cntFine(i, j - 1, strLen, wordsLen);
            if (newFine <= minFine[i]) {
                minFine[i] = newFine;
                history[i] = j;
            }
        }
    }

    int prevSplit = 0;
    int curSplit = history[0];

    while (curSplit >= 0) {
        cout << (curSplit - prevSplit) << ' ';
        prevSplit = curSplit;
        curSplit = history[prevSplit];
    }
    cout << n - prevSplit;
}

int main() {
    int strLen = 0;
    vector<int> wordsLen;
    readData(strLen, wordsLen);
    optSolution(strLen, wordsLen);

    return 0;
}
