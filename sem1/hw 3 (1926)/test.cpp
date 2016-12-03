#include<iostream>
#include<math.h>

using std::cout;
using std::ostream;

class myPair {
private:
    int f = 0;
    int s = 0;
public:
    myPair() {
    }

    const int& getF() const {
        return f;
    }
};

int main() {
    int a = 5;
    cout << sqrt(a);
    return 0;
}
