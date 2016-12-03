#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::vector;
using std::pair;
using std::ifstream;
using std::sort;
using std::min;
using std::max;
using std::fixed;

typedef pair<double, long long> doubleLL;

void readData(long long& maxWeight, double& startProfit , vector<doubleLL>& mercury) {
    ifstream fin("input.txt");
    int n = 0;
    fin >> n >> maxWeight;

    long long price = 0;
    long long weight = 0;
    for (int i = 0; i < n; ++i) {
        fin >> price >> weight;
        if (weight > 0 && price > 0) {
            mercury.push_back({price * ( - 1.0) / weight, weight});
        }
        if (weight == 0) {
            startProfit += price;
        }
    }
    sort(mercury.begin(), mercury.end());
    fin.close();
}

void cntMaxProfit(long long maxWeight, double curProfit, vector<doubleLL>& mercury) {
    long long curWeight = 0;
    long long addWeight = 0;
    for (auto curMercury : mercury) {
        addWeight = min(curMercury.second, maxWeight - curWeight);
        curWeight += addWeight;
        curProfit += (-1) * curMercury.first * addWeight;
        if (curWeight == maxWeight) {
            break;
        }
    }
    cout << fixed << curProfit;
}

int main() {
    long long maxWeight = 0;
    double startProfit = 0;
    vector<doubleLL> mercury;
    readData(maxWeight, startProfit, mercury);
    cntMaxProfit(maxWeight, startProfit, mercury);
    return 0;
}
