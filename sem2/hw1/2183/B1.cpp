#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using std::ifstream;
using std::cout;
using std::endl;
using std::sort;
using std::vector;
using std::pair;


void readData(vector<pair<int, int>>& segments) {
    ifstream fin("input.txt");
    int n = 0;
    fin >> n;

    int segBegin = 0;
    int segEnd = 0;
    for (int i = 0; i < n; ++i) {
        fin >> segBegin >> segEnd;
        segments.push_back({segBegin, 0});
        segments.push_back({segEnd, 1});
    }
}

int cntPainted(vector<pair<int, int>>& segments) {
    if (segments.size() == 0) {
        return 0;
    }

    sort(segments.begin(), segments.end());
    int res = 0;
    int curBalance = 0;
    int lastBegin = -1;
    for (auto point : segments) {
        if (point.second == 0) {
            if (curBalance == 0) {
                lastBegin = point.first;
            }
            ++curBalance;
        } else {
            --curBalance;
            if (curBalance == 0) {
                res += (point.first - lastBegin + 1);
            }
        }
    }
    return res;
}


int main() {
    vector<pair<int, int>> segments;
    readData(segments);
    cout << cntPainted(segments);
    return 0;
}
