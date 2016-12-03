#include<iostream>

using std::cin;
using std::cout;

int main() {
    float a = 0.1;
    int b = 2;
    int c = 3;
    int d = 4;
    cout << (a == b || a == c && c < 5);
    return 0;
}
