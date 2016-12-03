class Stud {
    private:
        srting Name;
        int Day;
        int Month;
        int Year;
    public:
        Stud() { //constructor by default
            date = 0;
            month = 0;
            year = 0;
        }
        Stud(const string& name, int day, int month, int year) { // other constructor
            Name = name;
            Day = day;
            Month = month;
            Year = year;
        }
}


//using T = double;
template<typename T>
class TVector {
private:
    vector<T> Coeff;
public:
    TVector() {
    }

    TVector(const vector<T>& v) {
        Coeff = v;
    }

    size_t size() const {
        return this->Coeff.size();
    }

    T at(size_t i) const {
         return this->Coeff.at(i);
    }
    T& at(size_t i) {
        return this->Coeff.at(i);
    }
    T operator[] (size_t i) const {
        return Coeff[i]; //return Coeff.operator[](i)
    }
    T operator[] (size_t) {
        return Coeff[i];
    }
    TVector& operator += (const TVector& a) {
        assert(this->size() == a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            Coeff[i] += a.Coeff[i];
        }
    return *this;
    }
};


template<typename T>
TVector operator + (const TVector& a, const TVector& b) {
    TVector res = a;
    res += b;
    return res;
}
template<typename T>
T operator * (const TVector& a, const TVector& b) {
    assert(a.size() == b.size());
    T res =
}


template<typename T, int N>


// std::ostream - type of cout, cin etc

template<typename T, int N>
std::ostream& operator << (
                           std:ostream& out,
                           const Matrix<T, N>& A;
) {
    // printing matrix

}

template <typename>
