#include<iostream>

#define LEAPYEAR 366
#define NOTLEAPYEAR 365

const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

using std::cin;
using std::cout;

struct Date{
    int day;
    int month;
    int year;
};

bool isLeapYear(int theYear) {
    if (theYear % 4 != 0 || (theYear % 100 == 0 && theYear % 400 != 0)) {
        return false;
    }
    return true;
}

int cntDaysFrom1600(Date& theDate) {
    int ans = 0;
    for (int i = 1600; i < theDate.year; ++i) {
        ans += isLeapYear(i) ? LEAPYEAR : NOTLEAPYEAR;
    }

    for (int i = 0; i < theDate.month - 1; ++i) {
        ans += daysInMonth[i];
    }
    if (theDate.month > 2 && isLeapYear(theDate.year)) {
        ++ans;
    }
    ans += theDate.day;
    return ans;
}

int main() {
    Date start, finish;
    cin >> start.day >> start.month >> start.year;
    cin >> finish.day >> finish.month >> finish.year;

    cout << cntDaysFrom1600(finish) - cntDaysFrom1600(start);

    return 0;
}
