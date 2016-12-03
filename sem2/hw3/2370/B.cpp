#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

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
const int MAX_NUM = 24000;


class ReallyLong {
private:
    vector<int> digits;

public:
    ReallyLong() {
        digits.push_back(0);
    }

    explicit ReallyLong(int num) {
        while (num != 0) {
            digits.push_back(num % BASE);
            num /= BASE;
        }
    }

    void clear() {
        digits.clear();
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

    friend bool operator < (const ReallyLong& a, const ReallyLong& b) {
        if (a.digits.size() < b.digits.size()) {
            return true;
        }
        if (a.digits.size() > b.digits.size()) {
            return false;
        }
        for (int i = a.digits.size() - 1; i >= 0; --i) {
            if (a.digits[i] < b.digits[i]) {
                return true;
            }
            if (a.digits[i] > b.digits[i]) {
                return false;
            }
        }
        return false;
    }

    friend bool operator == (const ReallyLong& a, const ReallyLong& b) {
        if (a.digits.size() != b.digits.size()) {
            return false;
        }

        for (int i = 0; i < a.digits.size(); ++i) {
            if (a.digits[i] != b.digits[i]) {
                return false;
            }
        }
        return true;
    }


    friend istream& operator >> (istream& in, ReallyLong& num) {
        num.clear();
        string bigNum;
        in >> bigNum;

        int curDigit = 0;
        int curSize = bigNum.size();
        int nextSymb = 0;
        while (curSize - CNTDIGITS >= 0) {
            for (int i = 0; i < CNTDIGITS; ++i) {
                nextSymb = static_cast<int>(bigNum[curSize - CNTDIGITS + i] - '0');
                curDigit = curDigit * 10 + nextSymb;
            }
            num.digits.push_back(curDigit);
            curSize -= CNTDIGITS;
            curDigit = 0;
        }
        for (int i = 0; i < curSize; ++i) {
            curDigit = curDigit * 10 + static_cast<int>(bigNum[i] - '0');
        }
        if (curDigit != 0) {
            num.digits.push_back(curDigit);
        }
        return in;
    }

    friend ostream& operator << (ostream& out, ReallyLong& num) {
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
    }
}

bool binSearch(ReallyLong num, vector<ReallyLong>& fibonacci) {
    int left = 0;
    int right = fibonacci.size();
    int mid = 0;
    while ((right - left) > 1) {
        mid = (right + left) / 2;
        if (num == fibonacci[mid]) {
            return true;
        }
        if (num < fibonacci[mid]) {
            right = mid;
        } else {
            left = mid;
        }
    }
    if (fibonacci[left] == num) {
        return true;
    }
    return false;
}

void checkNumbers(vector<ReallyLong>& fibonacci) {
    ifstream fin("input.txt");
    int cntNumbers = 0;
    fin >> cntNumbers;
    ReallyLong curNum;
    for (int i = 0; i < cntNumbers; ++i) {
        fin >> curNum;
        if (binSearch(curNum, fibonacci)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    fin.close();
}

int main() {
    vector<ReallyLong> fibonacci;
    generateFibonacci(fibonacci);
    checkNumbers(fibonacci);

    return 0;
}
