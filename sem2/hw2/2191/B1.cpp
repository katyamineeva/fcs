#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using std::ifstream;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::max;
using std::ostream;
using std::string;

const int BASE = 1000000;
const int CNTDIGITS = 6;


class ReallyLong {
private:
    vector<int> digits;

public:
    ReallyLong() {
    }

    ReallyLong(int num) {
        while (num != 0) {
            digits.push_back(num % BASE);
            num /= BASE;
        }
    }

    ReallyLong& operator += (const ReallyLong& addNum) {
        int addNumLen = addNum.digits.size();
        int mainNumLen = digits.size();
        digits.resize(max(addNumLen, mainNumLen));
        int memory = 0;
        for (int i = 0; i < addNumLen; ++i) {
            digits[i] += addNum.digits[i] + memory;
            memory = digits[i] / BASE;
            digits[i] %= BASE;
        }
        for (int i = addNumLen; i < digits.size(); ++i) {
            digits[i] += memory;
            memory = digits[i] / BASE;
            digits[i] %= BASE;
        }

        if (memory != 0) {
            digits.push_back(memory);
        }
        return *this;
    }


    friend ostream& operator << (ostream& out, ReallyLong num) {
        int cntDigits = 0;
        int tmp = 0;
        out << num.digits[num.digits.size() - 1];
        for (int i = num.digits.size() - 2; i >= 0; --i) {
            cntDigits = 1;
            tmp = num.digits[i];
            while (tmp > 9) {
                ++cntDigits;
                tmp /= 10;
            }
            for (int j = 0; j < (CNTDIGITS - cntDigits); ++j) {
                out << 0;
            }
            out << num.digits[i];
        }
        return out;
    }
};

ReallyLong cntNumbers(int numLen) {
    vector<vector<ReallyLong>> cntNum(numLen, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    cntNum[0] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1};
    vector<vector<int>> prevNum(10);
    prevNum[0] = {4, 6};
    prevNum[1] = {6, 8};
    prevNum[2] = {7, 9};
    prevNum[3] = {4, 8};
    prevNum[4] = {0, 3, 9};
    prevNum[5] = {};
    prevNum[6] = {0, 1, 7};
    prevNum[7] = {2, 6};
    prevNum[8] = {1, 3};
    prevNum[9] = {2, 4};
    for (int i = 1; i < numLen; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int prev : prevNum[j]) {
                cntNum[i][j] += cntNum[i - 1][prev];
            }
        }
    }

    ReallyLong ans = 0;
    for (int i = 0; i < 10; ++i) {
        ans += cntNum[numLen - 1][i];
    }
    return ans;
}
int main() {
    int numLen = 0;
    cin >> numLen;
    ReallyLong ans = cntNumbers(numLen);
    cout << ans;
    return 0;
}
