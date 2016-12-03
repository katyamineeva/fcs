#define EPS 0.0000000000057
#include <iostream>
#include <math.h>

template <typename T = double, int N = 1>
class MathVector {
public:
    T coords[N];

    MathVector() {
        for (int i = 0; i < N; ++i) {
            coords[i] = 0;
        }
    }

    MathVector(std::initializer_list<T> data) {
        //coords = new T * [N];
        std::copy(data.begin(), data.end(), coords);
    }
    const T& operator [] (size_t i) const {
        return coords[i];
    }
    T& operator [] (size_t i) {
        return coords[i];
    }
    friend T operator * (MathVector<T, N> u, MathVector<T, N> v) {
        T res = 0;
        for (size_t i = 0; i != N; ++i)
            res += u[i] * v[i];
        return res;
    }

    double Abs() const {
        T res = 0;
        for (const T xi : coords)
            res += xi * xi;
        return sqrt(res);
    }
};

template <typename T, int N>
std::ostream& operator << (std::ostream& o, MathVector<T, N>& v) {
    o << "(";
    for (size_t i = 0; i != N - 1; ++i)
        o << v[i] << ", ";
    o << v[N - 1] << ")";
    return o;
}

template <typename T, int N>
std::istream& operator >> (std::istream& in, MathVector<T, N>& v) {
    for (size_t i = 0; i != N; ++i)
        in >> v[i];
    return in;
}

template <typename T, int N>
double Cos(const MathVector<T, N>& u, const MathVector<T, N>& v) {
    auto uAbs = u.Abs();
    auto vAbs = v.Abs();
    if (uAbs < EPS || vAbs < EPS) {
        throw std::exception();
    } else {
        return u * v / (uAbs * vAbs);
    }
}

int main() {
    MathVector<int, 3> u {1, 2, -3};
    MathVector<int, 3> v;
    std::cin >> v;
    std::cout << "Vector u: " << u << "\n";
    std::cout << "Vector v: " << v << "\n";
    std::cout << "Length of u: " << u.Abs() << "\n";
    std::cout << "Length of v: " << v.Abs() << "\n";
    std::cout << "Scalar product: " << (u * v) << "\n";
    std::cout << "Cosinus of angle: " << Cos(u, v) << "\n";
    return 0;
}
