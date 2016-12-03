#include<fstream>
#include<iostream>
#include<string>
#include<vector>

using std::cout;
using std::vector;
using std::string;
using std::ifstream;

void rotatePoint(int& x, int& y, int n) {
    int tmp = x;
    x = y;
    y = n - 1 - tmp;
}


void getPattern(vector<vector<char> >& pattern, string& word) {
    ifstream fin("input.txt");
    int n = 0;
    fin >> n;

    vector<char> emptyVect;
    emptyVect.assign(n, ' ');
    pattern.assign(n, emptyVect);

    string s;
    getline(fin, s);
    int x = 0;
    int y = 0;

    for (int i = 0; i < n; ++i) {
        getline(fin, s);
        for (int j = 0; j < n; ++j) {
            if (s[j] != '*') {
                x = i;
                y = j;
                pattern[x][y] = '0';
                rotatePoint(x, y, n);
                pattern[x][y] = '1';
                rotatePoint(x, y, n);
                pattern[x][y] = '2';
                rotatePoint(x, y, n);
                pattern[x][y] = '3';
            }
        }
    }
    getline(fin, word);

    fin.close();
}


void printCode(vector<vector<char> >& pattern, const string word) {
    int ind[4] = {0, 0, 0, 0};
    char tmp = ' ';
    int shift = word.length() / 4;
    for (int i = 0; i < pattern.size(); ++i) {
        for (int j = 0; j < pattern[i].size(); ++j) {
            if (pattern[i][j] != ' ') {
                tmp = pattern[i][j] - '0';
                pattern[i][j] = word[shift * tmp + ind[tmp]];
                ++ind[tmp];
            }
            cout << pattern[i][j];
        }
    }
}

int main() {
    vector< vector<char> > pattern;
    string word;
    getPattern(pattern, word);
    if (word.length() > 0) {
        printCode(pattern, word);
    }
    return 0;
}
