#include <fstream>
#include <iostream>
#include <vector>


using std::cout;
using std::vector;
using std::ifstream;

void readData(vector<int>& inmerge) {
    ifstream fin("input.txt");
    int n = 0;
    fin >> n;
    inmerge.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> inmerge[i];
    }

    fin.close();
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

long long calculeteCntInv(vector<int>& inmerge, int start, int finish) {
    if (finish - start < 2) {
        return 0;
    }
    int mid = start + (finish - start) / 2;
    long long ans = 0;
    ans += calculeteCntInv(inmerge, start, mid);
    ans += calculeteCntInv(inmerge, mid, finish);
    ans += calculeteInMerge(inmerge, start, mid, finish);
    return ans;
}

int main() {
    vector<int> inmerge;
    readData(inmerge);
    cout << calculeteCntInv(inmerge, 0, inmerge.size());
    return 0;
}
