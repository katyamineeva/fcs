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
using std::istream;
using std::string;

const int BASE = 1000000;
const int CNTDIGITS = 6;
const int MAX_NUM = 240;


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

    friend istream& operator >> (istream& in, ReallyLong& num) {
        string bigNum;
        in >> bigNum;

        int curDigit = 0;
        int curNumSize = bigNum.size();
        while (curNumSize - CNTDIGITS >= 0) {
            // cout << bigNum << ' ' << bigNum.size() - CNTDIGITS << endl;
            for (int i = 0; i < CNTDIGITS; ++i) {
                curDigit = curDigit * 10 + int(bigNum[curNumSize - CNTDIGITS + i] - '0');
            }
            num.digits.push_back(curDigit);
            curNumSize -= CNTDIGITS;
            curDigit = 0;
        }
        for (int i = 0; i < curNumSize; ++i) {
            curDigit = curDigit * 10 + int(bigNum[i] - '0');
        }
        if (curDigit != 0) {
            num.digits.push_back(curDigit);
        }
        return in;
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


ReallyLong operator + (const ReallyLong& a, const ReallyLong& b) {
    ReallyLong sum = a;
    sum += b;
    return sum;
}

void generateFibonacci(vector<ReallyLong>& fibonacci) {
    ReallyLong f01(1);

    fibonacci.push_back(f01);
    fibonacci.push_back(f01);
    for (int i = 2; i < MAX_NUM; ++i) {
        fibonacci.push_back(fibonacci[i - 1] + fibonacci[i - 2]);
        // cout << fibonacci[i] << endl;
    }
}

void checkNumbers(vector<ReallyLong>& fibonacci) {
    int cntNumbers = 0;
    cin >> cntNumbers;
    ReallyLong curNum;
    for (int i = 0; i < cntNumbers; ++i) {
        cin >> curNum;
        cout << curNum;
    }

}

int main() {
    vector<ReallyLong> fibonacci;
    generateFibonacci(fibonacci);
    checkNumbers(fibonacci);

    return 0;
}

