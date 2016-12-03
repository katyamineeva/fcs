// #define EPS 0.0000000000057 - some really-really tiny number to compare doubles and zero
#include <iostream>
// here should be: #include <math.h>

template <typename T = double, int N> // we should put some default argument for N
                                      // because in case written "MathVector<something>" then T = something, and N...?
class MathVector {
public:
    // there is general mistake: the field 'coords' isn't private
    // so it would be harder to change type of coords and .. it's just bad
    T coords[N];

    //default constructor must be here:
    //MathVector() {
    //    for (int i = 0; i < N; ++i) {
    //        coords[i] = 0;              //it's better to put some fixed values instead of rubbish
    //    }
    //}


    MathVector(std::initializer_list<T> data) {
        coords = new T[n]; //firstly instead of n should be N
                           //secondly we don't need this line at all, because we have already  allocated memory by writing: "T coords[N];"
        std::copy(coords, data.begin(), data.end()); // arguments of function "copy" in incorrect order
                                                     // we should write std::copy(data.begin(), data.end(), coords);
    }

    const T& operator [] (size_t i) { // here should be: T& operator [] (size_t i) {
                                      // this operator would be used for non-constant MathVectors
                                      // and int << for example we are changing coords
                                      // but this operator returns constant reference to coords[i] so we won't be able to change it
        return coords[i];
    }
    T& operator [] (size_t i) const {  // it would be better to write: const T& operator [] (size_t i) const {
                                       // because is't good to return non-constant reference to object's field in constant operator
        return coords[i];
    }
    friend T& operator * (MathVector u, MathVector v) { // we should write: friend T operator * (MathVector u, MathVector v) {
        T res = 0;
        for (size_t i = 0; i != N; ++i)
            res += u[i] * v[i];
        return res;  // we have local variable "res" and return reference to res
                     // but variable res would disappear as soon as this operator ends working
                     // не уверена, что достаточно грамотно написала это на английском так что поясню на русском
                     // нельзя возвращать ссылку на локальную переменную res т.к. она перестанет существовать после того, как отработает оператор *

    }
    T Abs() const { // we should write: double Abs() const {
                    // even in case all coords are in, the length of vector might be non-int
        T res;    // we should write: T res = 0;
                  // variable res isn't initialized. so value of res is unpredictable
        for (const T& xi : coords)  // it's better to write: for (const T xi : coords)
                                    // i don't really know why here is written "const T& xi".. it gives hte same result, but we don't need reference here
            res += xi * xi;
        return sqrt(res); // we should include "math.h" to use sqrt
    }
};
//template <typename T, int N> must be here
std::ostream& operator << (std::ostream& o, MathVector& v) { // there is no type "MathVector", only MathVector with arguments
                                                             // we should write "MathVector<T, N>" instead of "MathVector".
                                                             // so we need template before this function
    o << "(";
    for (size_t i = 0; i != N; ++i) // here should be:  for (size_t i = 0; i != N - 1; ++i)
        o << v[i] << ", ";
    o << v[N] << ")";   // here should be o << v[N - 1] << ")";
                        // v[N] - is some rubbish; 0, 1, 2, ..., (N - 1) - are indexes of coords
    return o;
}

template <typename T, int N>
std::istream& operator >> (std::istream& i, MathVector<T, N>& v) {// here should be: std::istream& operator >> (std::istream& in, MathVector<T, N>& v) {
                                                                   // the name of input stream is the same as name of counter in for!
                                                                   //let's call input stream "in" and everything would be ok
    for (size_t i = 0; i != N; ++i)
        i >> v[i]; // here we should write in >> v.[i];
                   // and we should also change operator [] for our MathVector to be able to change coords
    return i;      // here we should write return in;
}

template <typename T, int N>
double Cos(const MathVector<T, N>& u, const MathVector<T, N>& v) {
    auto uAbs = u.Abs();
    auto vAbs = v.Abs();
                        // It isn't protected from division by zero. Correct solution is:
                        //    if (uAbs < EPS || vAbs < EPS) {
                        //        throw std::exception();
                        //    } else {
                        //        return u * v / (uAbs * vAbs);
                        //    }
    return u * v / uAbs * vAbs; // the order of calculating is incorrect: u * v / uAbs * vAbs <-> ((u * v) / uAbs) * vAbs
                                // to get cos we should write: return u * v / (uAbs * vAbs);
}

int main() {
    MathVector<int, 3> u {1, 2, -3};
    MathVector<int, 3> v; // we have no default constructor
    std::cin >> v;
    std::cout << "Vector u: " << u << "\n";
    std::cout << "Vector v: " << v << "\n";
    std::cout << "Length of u: " << u.Abs() << "\n";
    std::cout << "Length of v: " << v.Abs() << "\n";
    std::cout << "Scalar product: " << (u * v) << "\n";
    std::cout << "Cosinus of angle: " << Cos(u, v) << "\n";

    //return 0; must be here
}
