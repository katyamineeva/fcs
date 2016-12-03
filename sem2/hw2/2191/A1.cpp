#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::min;

void readData(vector<long long>& hotels) {
    ifstream fin("input.txt");
    int n = 0;
    fin >> n;

    hotels.resize(n);
    for (int i = 0; i < n; ++i) {
        fin >> hotels[i];
    }

    fin.close();
}

long long cntFine(long long h1, long long h2) {
    if (h1 == h2) {
        return 0;
    }
    return (200 - (h2 - h1)) * (200 - (h2 - h1));
}

long long cntMinFine(vector<long long>& hotels) {
    vector<long long> minFine(hotels.size());
    for (int i = 0; i < hotels.size(); ++i) {
        minFine[i] = cntFine(0, hotels[i]);
        for (int j = 0; j < i; ++j) {
            minFine[i] = min(minFine[j] + cntFine(hotels[j], hotels[i]), minFine[i]);
        }
    }
    return minFine[hotels.size() - 1];
}

int main() {
    vector<long long> hotels;
    readData(hotels);
    cout << cntMinFine(hotels);
    return 0;
}
