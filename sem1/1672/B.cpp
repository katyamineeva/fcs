#include<vector>
#include<string>
#include<iostream>
#include<alorithm>

struct Student {
    string name;
    string surname;
    int day;
    int month;
    int year;
};

int cmpDate(const Student& s1, const Student& s2) {
    if (s1.year < s2.year) {
        return -1;
    }
    if (s1.year > s2.year) {
        return 1;
    }
    if (s1.month < s2.month) {
        return -1;
    }
    if (s1.month > s2.month) {
        return 1;
    }
    if (s1.day < s2.day) {
        return -1;
    }
    if (s1.day > s2.day) {
        return 1;
    }
    return 0;
}

int cmpName(const Student& s1, const Student& s2) {
    int a = s1.surname.compare(s2.surname);
    if (a) {
        return a;
    }
    return s1.name.compare(s2.name);
}


bool cmpNameDate(const Student& s1, const Student& s2) {
    int tmpName = cmpName(s1, s2);
    int tmpDate = cmpDate(s1, s2);
    if (tmpName < 0 || (tmpName = 0 && tmpDate <= 0)) {
        return true;
    }
    return false;
}


bool cmpDateName(const Student& s1, const Student& s2) {
    int tmpName = cmpName(s1, s2);
    int tmpDate = cmpDate(s1, s2);
    if (tmpName < 0 || (tmpName = 0 && tmpDate <= 0)) {
        return true;
    }
    return false;
}

int main() {
    sort(v.begin(), v.end(), cmpDateName);
    return 0;
}
