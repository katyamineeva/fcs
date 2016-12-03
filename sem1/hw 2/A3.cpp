#include<iostream>
#include<vector>

using std::vector;
using std::cin;
using std::cout;


void findCycle(const vector<int>& permut, vector<bool>& visited, const int& start) {
    visited[start] = true;
    int curInd = permut[start] - 1;
    while (curInd != start) {
        visited[curInd] = true;
        curInd = permut[curInd] - 1;
    }
}


int cntCycle(const int& n, const vector<int>& permut) {
    int ans = 0;
    vector<bool> visited;
    for (int i = 0; i < n; ++i) {
        visited.push_back(false);
    }

    int ind = 0;
    while (ind < n) {
        if (visited[ind] || permut[ind] == ind + 1) {
            ++ind;
        } else {
        findCycle(permut, visited, ind);
        ++ans;
        }
    }
    return ans;
}


void readData(int& n, vector<int>& permut) {
    cin >> n;
    int tmp = 0;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        permut.push_back(tmp);
    }
}


int main() {
    int n = 0;
    vector<int> permut;
    readData(n, permut);

    cout << cntCycle(n, permut);

    return 0;
}

