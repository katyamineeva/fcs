#include<iostream>
#include<cmath>

using std::cin;
using std::cout;
using std::endl;

int main() {
    int command = 0;
    double a = 0;
    double b = 0;
    cin >> command >> a >> b;

    switch(command) {
        case 0:
            cout << (a + b) << endl;
            break;
        case 1:
            cout << (a - b) << endl;
            break;
        case 2:
            cout << (a * b) << endl;
            break;
        case 3:
            cout << (a / b) << endl;
            break;
        case 4:
            cout << pow(a, b) << endl;
            break;
        case 5:
            cout << pow(b, 1 / a) << endl;
            break;
        default:
            cout << "-1" << endl;
    }
    return 0;
}
