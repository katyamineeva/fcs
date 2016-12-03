#define EPS 0.0000000057
#include<vector>
#include<iostream>
#include<math.h>

using std::vector;
using std::cout;
using std::ostream;

template<typename T>
void deleteZeros(vector<T>& v) {
    size_t newSize = v.size();
    while (v[newSize - 1] == 0 && newSize > 1) {
        newSize -= 1;
    }
    v.resize(newSize);
}

template<typename T>
class Fraction {
private:
    vector<T> coeffNum = {0};
    vector<T> coeffDenom = {1};
public:
    Fraction() {
    }
    Fraction(T c) {
        coeffNum = {c};
    }

    Fraction(vector<T>& num, vector<T>& denom) {
        if (num.size() == 0) {
            num = {0};
        }
        if (denom.size() == 0) {
            denom = {0};
        }
        deleteZeros(num);
        deleteZeros(denom);
        coeffNum = num;
        coeffDenom = denom;
    }

    Fraction<T>& inverse() {
        std::swap(coeffDenom, coeffNum);
        return *this;
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

    Fraction<T>& operator *= (const Fraction<T>& a) {
        Fraction<T> tmp = *this * a;
        *this = tmp;
        return *this;
    }

    Fraction<T>& operator /= (const Fraction<T>& a) {
        Fraction<T> tmp = *this / a;
        *this = tmp;
        return *this;
    }

    Fraction<T>& operator += (const Fraction<T>& a) {
        Fraction<T> tmp = *this + a;
        *this = tmp;
        return *this;
    }

    Fraction<T>& operator -= (const Fraction<T>& a) {
        Fraction<T> tmp = *this - a;
        *this = tmp;
        return *this;
    }

    T operator () (const T x) {
        double denom = 0;
        for (int i = 0; i < coeffDenom.size(); ++i) {
            denom += coeffDenom[i] * pow(x, i);
        }
        if (denom < EPS && -EPS < denom) {
            throw std::exception();
        } else {
            double num = 0;
            for (int i = 0; i < coeffNum.size(); ++i) {
                num += coeffNum[i] * pow(x, i);
            }
            return (num / denom);
        }

    }

    friend ostream& operator << (ostream& out, Fraction<T> a) {
        out << '(' << a.coeffNum << ")/(" << a.coeffDenom << ')';
        return out;
    }

    Fraction<T>& operator *= (const T c) {
        for (int i = 0; i < coeffNum.size(); ++i) {
            coeffNum[i] *= c;
        }
        return *this;
    }

    Fraction<T>& operator /= (const T c) {
        if (c == 0) {
            throw std::exception();
        } else {
            *this *= (1/c);
        }
    }
};

template<typename T>
vector<T> vectorMult(typename vector<T>::const_iterator a_begin,
                     size_t a_len,
                     typename vector<T>::const_iterator b_begin,
                     size_t b_len) {
    vector<T> res(a_len + b_len - 1, 0);
    for (int i = 0; i < a_len; ++i) {
        for (int j = 0; j < b_len; ++j) {
            res[i + j] += (*(a_begin + i) * (*(b_begin + j)));
        }
    }
    deleteZeros(res);
    return res;
}

template<typename T>
Fraction<T> operator * (const Fraction<T>& a, const Fraction<T>& b) {
    vector<T> num = vectorMult<T>(a.numerator_begin(),
                                  a.numerator_degree() + 1,
                                  b.numerator_begin(),
                                  b.numerator_degree() + 1);
    vector<T> denom = vectorMult<T>(a.denominator_begin(),
                                    a.denominator_degree() + 1,
                                    b.denominator_begin(),
                                    b.denominator_degree() + 1);
    Fraction<T> res(num, denom);
    return res;
}

template<typename T>
Fraction<T> operator / (const Fraction<T>& a, const Fraction<T>& b) {
    Fraction<T> res = b;
    res.inverse();
    res *= a;
    return res;
}

template<typename T>
Fraction<T> operator + (const Fraction<T>& a, const Fraction<T>& b) {
    vector<T> denom = vectorMult<T>(a.denominator_begin(),
                                    a.denominator_degree() + 1,
                                    b.denominator_begin(),
                                    b.denominator_degree() + 1);
    vector<T> num1 = vectorMult<T>(a.numerator_begin(),
                                   a.numerator_degree() + 1,
                                   b.denominator_begin(),
                                   b.denominator_degree() + 1);
    vector<T> num2 = vectorMult<T>(b.numerator_begin(),
                                   b.numerator_degree() + 1,
                                   a.denominator_begin(),
                                   a.denominator_degree() + 1);
    vector<T> num = num1 + num2;
    Fraction<T> res(num, denom);
    return res;
}


template<typename T>
Fraction<T> operator - (const Fraction<T>& a, const Fraction<T>& b) {
    Fraction<T> res = b;
    res *= -1;
    res += a;
    return res;
}

template<typename T>
bool operator == (const Fraction<T>& a, const Fraction<T>& b) {
    vector<T> mult1 = vectorMult<T>(a.numerator_begin(),
                                    a.numerator_degree() + 1,
                                    b.denominator_begin(),
                                    b.denominator_degree() + 1);
    vector<T> mult2 = vectorMult<T>(b.numerator_begin(),
                                    b.numerator_degree() + 1,
                                    a.denominator_begin(),
                                    a.denominator_degree() + 1);
    return (mult1 == mult2);
}

template<typename T>
bool operator != (const Fraction<T>& a, const Fraction<T>& b) {
    return !(a == b);
}

template<typename T>
vector<T> operator + (const vector<T>& a, const vector<T>& b) {
    vector<T> res;
    if (a.size() > b.size()) {
        res = a;
        for (int i = 0; i < b.size(); ++i) {
            res[i] += b[i];
        }
    } else {
        res = b;
        for (int i = 0; i < a.size(); ++i) {
            res[i] += a[i];
        }
    }
    deleteZeros(res);
    return res;
}



template<typename T>
vector<T> operator * (const T c, const Fraction<T>& frac) {
    Fraction<T> res = frac;
    res *= c;
    deleteZeros(res);
    return res;
}


template<typename T>
vector<T> operator / (const T c, const Fraction<T>& frac) {
    Fraction<T> res = frac;
    res /= c;
    return res;
}


template<typename T>
ostream& operator << (ostream& out, const vector<T>& coeff) {
    if (coeff.size() == 1) {
        out << coeff[0];
    } else {
        for (int i = coeff.size() - 1; i > 0; --i) {
            if (coeff[i] > 0) {
                if (i != coeff.size() - 1) {
                    out << '+';
                }
                if (coeff[i] != 1) {
                    out << coeff[i] << '*';
                }
                out << 'x';
                if (i > 1) {
                    out << '^' << i;
                }
            }
            if (coeff[i] < 0) {
                if (coeff[i] == -1) {
                    out << '-';
                } else {
                    out << coeff[i] << '*';
                }
                out << 'x';
                if (i > 1) {
                    out << '^' << i;
                }
            }
        }
        if (coeff[0] > 0){
            out << '+' << coeff[0];
        }
        if (coeff[0] < 0) {
            out << coeff[0];
        }
    }
    return out;
}



int main() {
    vector<float> n1 = {1, 1};
    vector<float> d1 = {0, 2};
    vector<float> n2 = {1, -3};
    vector<float> d2 = {-1};
    vector<float> u = {1};
    vector<float> pn = {0};
    vector<float> pd = {0, 0, 4};
    //Fraction<float> p(pn, pd);



    Fraction<float> f1(n1, d1);
    Fraction<float> f2(n2, d2);
    Fraction<float> unit(u, u);
    Fraction<float> zero(0);
    Fraction<float> antizero = zero;
    antizero.inverse();

    Fraction<float> p = ((f1 - f1) * zero);
    cout << ((f1 - f1) * antizero) << '\n' << ((f1 - f1) == zero) << '\n';

    return 0;
}
