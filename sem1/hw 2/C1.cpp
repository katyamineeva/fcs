#include<iostream>
#include<vector>

using std::vector;
using std::cin;
using std::cout;


void getPositiveRemainder(int& k, const int& n) {
    while (k < 0) {
        k += n;
    }
    k = k % n;
}

void rotateVect(vector<int>& data, int shift) {
    getPositiveRemainder(shift, data.size());
    vector<int> tmpV;
    for (int i = data.size() - shift; i < data.size(); ++i) {
        tmpV.push_back(data[i]);
    }
    for (int i = 0; i < data.size() - shift; ++i) {
        tmpV.push_back(data[i]);
    }
    data = tmpV;
}

void readData(vector<int>& v, int& shift) {
    int n = 0;
    cin >> n;
    int tmp = 0;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        v.push_back(tmp);
    }
    cin >> shift;
}

void printData(vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }
}


int main() {
    int shift = 0;
    vector<int> v;
    readData(v, shift);

    if (v.size() > 0) {
        rotateVect(v, shift);
        printData(v);
    }

    return 0;
}
