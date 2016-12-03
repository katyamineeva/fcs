#include <iostream>
#include<fstream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::ifstream;
using std::max;

void readData(vector<vector<double>>& segments) {
    int n = 0;
    ifstream fin("input.txt");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        segments.push_back({0, 0, 0});
        fin >> segments[i][0] >> segments[i][1] >> segments[i][2];
    }
    fin.close();
}


bool isCompatible(int first, int second, vector<vector<double>>& segments) {
    return second < segments.size() && segments[first][1] <= segments[second][0];
}

int findNearest(int ind, int left, int right, vector<vector<double>>& segments) {
    if (right - left <= 1) {
        if (isCompatible(ind, left, segments)) {
            return left;
        }
        return right;
    } else {
        int middle = (left + right) / 2;
        if (!isCompatible(ind, middle, segments)) {
            findNearest(ind, middle, right, segments);
        } else {
            findNearest(ind, left, middle, segments);
        }
    }
}

double maxWeight(vector<vector<double>>& segments) {
    if (segments.size() == 0) {
        return 0;
    }
    int len = segments.size();
    sort(segments.begin(), segments.end());
    vector<int> nearestInd(len);

    vector<double> optSolution(len + 1, 0);
    optSolution[len] = 0;
    for (int i = len - 1; i >= 0; --i) {
        int nearestInd = findNearest(i, i, segments.size(), segments);
        optSolution[i] = max(optSolution[i + 1], segments[i][2] + optSolution[nearestInd]);
    }
    return optSolution[0];

}

int main() {
    vector<vector<double>> segments;
    readData(segments);
    cout << maxWeight(segments);
    return 0;
}
