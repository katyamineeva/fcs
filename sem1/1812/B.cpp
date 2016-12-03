#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::vector;

void merge(vector<int>& v1, vector<int>& v2, vector<int>& res) {
    int i = 0;
    int j = 0;
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] <= v2[j]) {
            res.push_back(v1[i]);
            ++i;
        } else {
            res.push_back(v2[j]);
            ++j;
        }
    }
    if (i < v1.size()) {
        while (i < v1.size()) {
            res.push_back(v1[i]);
            ++i;
        }
    }
    if (j < v2.size()) {
        while (j < v2.size()) {
            res.push_back(v2[j]);
            ++j;
        }
    }
}


int main() {
    int n = 0;
    int tmp = 0;
    vector<int> v1;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        v1.push_back(tmp);
    }

    cin >> n;
    vector<int> v2;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        v2.push_back(tmp);
    }
    vector<int> res;
    merge(v1, v2, res);

    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << ' ';
    }
    return 0;
}

