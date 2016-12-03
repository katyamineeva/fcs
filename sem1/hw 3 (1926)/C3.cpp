#include<vector>
#include<iostream>

using std::cout;
using std::ostream;
using std::vector;

class FixedString {
private:
    vector<char> symbols;
public:
    FixedString() {
    }

    FixedString(const char* s) {
        while (*s != '\0'){
            symbols.push_back(*s);
            ++s;
        }
    }

    size_t size() {
        return symbols.size();
    }

    bool empty() {
        return (symbols.size() == 0);
    }

    vector<char>::const_iterator begin() const {
        return symbols.begin();
    }

    vector<char>::const_iterator end() const {
        return symbols.end();
    }

    const char operator [](const int ind) const {
        return symbols[ind];
    }

    void push_back(char c) {
        symbols.push_back(c);
    }

    FixedString substr(int first, size_t length) {
        FixedString res;
        for (size_t i = first; i < first + length; ++i) {
            res.push_back(*(symbols.begin() + i));
        }
        return res;
    }
};


ostream& operator << (ostream& out, const FixedString& s) {
    for (vector<char>::const_iterator it = s.begin(); it != s.end(); ++it) {
        out << *it;
    }
    return out;
}

int main() {
    char* a = "i love 57";
    FixedString s(a);
    cout << s[2] << ' ' << s[3] << '\n';
    cout << s.size() << '\n';
    cout << s.substr(3, 3);
    return 0;
}
