#include<iostream>

using std::cin;
using std::cout;

int main () {
     int sumDigit = 0;
     char curDigit = 0;
     cin >> curDigit;
     sumDigit += curDigit;

     while (cin) {
         cin >> curDigit;
         sumDigit += curDigit;
     }
     cout << sumDigit;

     return 0;
}
