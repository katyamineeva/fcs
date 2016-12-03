#include<vector>
#include<iostream>

using std::vector;
using std::cout;

template<typename T>
class Fraction {
private:
    vector<T> coeffNum = {0};
    vector<T> coeffDenom = {1};
public:
    Fraction(T c) {
        coeffNum = {c};
    }

    Fraction(vector<T>& num, vector<T>& denom) {
        coeffNum = num;
        coeffDenom = denom;
    }

    void inverse() {
        std::swap(coeffDenom, coeffNum);
    }

    typename vector<T>::const_iterator numerator_begin() const {
        return coeffNum.begin();
    }

    typename vector<T>::const_iterator numerator_end() const {
        return coeffNum.end();
    }
    typename vector<T>::const_iterator denominator_begin() const {
        return coeffDenom.begin();
    }

    typename vector<T>::const_iterator denominator_end() const {
        return coeffDenom.end();
    }
    int numerator_degree() const {
        return coeffNum.size() - 1;
    }
    int denominator_degree() const {
        return coeffDenom.size() - 1;
    }
};

template <typename T>
vector<T>& MultVect(typename vector<T>::const_iterator v1_begin,
                    typename vector<T>::const_iterator v1_end,
                    int v1_size,
                    typename vector<T>::const_iterator v2_begin,
                    typename vector<T>::const_iterator v2_end,
                    int v2_size) {
    size_t len = v1_size + v2_size + 1;
    vector<T> res(len, 0);
    int i = 0;
    int j = 0;
    for (; v1_begin != v1_end; ++v1_begin) {
        for (; v2_begin != v2_end; ++v2_begin) {
            res[i + j] += (*v1_begin) * (*v2_begin);
            ++j;
        }
        ++i;
    }
    return res;
}

template<typename T>
Fraction<T>& operator * (const Fraction<T>& f1, const Fraction<T>& f2) {
    vector<T> num = MultVect<T>(f1.numerator_begin(), f1.numerator_end(), f1.numerator_degree(),
                             f2.numerator_begin(), f2.numerator_end(), f2.numerator_degree());
    vector<T> denom = MultVect<T>(f1.denominator_begin(), f1.denominator_end(), f1.denominator_degree(),
                             f2.denominator_begin(), f2.denominator_end(), f2.denominator_degree());
    Fraction<T> res(num, denom);
    return res;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const Fraction<T>& frac) {
    out << '(';
    int pow = 0;
    for (typename vector<T>::const_iterator it = frac.numerator_begin(); it != frac.numerator_end(); ++it) {
        out << '+' << *it << "x^" << pow << ' ';
        ++pow;
    }
    out << ") / (";
    pow = 0;
    for (typename vector<T>::const_iterator it = frac.denominator_begin(); it != frac.denominator_end(); ++it) {
        out << '+' << *it << "x^" << pow << ' ';
        ++pow;
    }
    out << ") \n";
    return out;
}


template <typename T>
std::ostream& operator << (std::ostream& out, const vector<T>& v) {
    for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
        out << *it << ' ';
    }
    out << '\n';
    return out;
}


int main() {
    vector<int> n1 = {1, 2};
    vector<int> d12 = {1};
    vector<int> n2 = {1, -2};

    Fraction<int> frac1(n1, d12);
    Fraction<int> frac2(n1, d12);

    Fraction<int> frac3 = frac1 * frac2;
    cout << frac3;

    return 0;
}
