#include<iostream>
#include<cmath>


using std::cin;
using std::cout;
using std::endl;
using std::fixed;

int main() {
    int a = 0;
    int b = 0;
    cin >> a >> b;
    double c = sqrt(a * a + b * b);
    cout << fixed << c;
    return 0;
}
