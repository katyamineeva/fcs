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


class ReallyLong {
private:
    vector<char> digits;

public:
    ReallyLong() {
    }

    ReallyLong(int num) {
        while (num != 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }

    ReallyLong& operator += (const ReallyLong& addNum) {
        int addNumLen = addNum.digits.size();
        int mainNumLen = digits.size();
        digits.resize(max(addNumLen, mainNumLen));
        char memory = 0;
        for (int i = 0; i < addNumLen; ++i) {
            digits[i] += addNum.digits[i] + memory;
            memory = digits[i] / 10;
            digits[i] %= 10;
        }
        for (int i = addNumLen; i < digits.size(); ++i) {
            digits[i] += memory;
            memory = digits[i] / 10;
            digits[i] %= 10;
        }

        if (memory != 0) {
            digits.push_back(memory);
        }
        return *this;
    }


    friend ostream& operator << (ostream& out, ReallyLong num) {
        for (int i = num.digits.size() - 1; i >= 0; --i) {
            out << int(num.digits[i]);
        }
        return out;
    }

};



int main() {
    vector<ReallyLong> b = {1, 57};

    cout << b[1];

    return 0;
}

