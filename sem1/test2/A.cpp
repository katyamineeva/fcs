#include<iostream>
#include<set>
#include<algorithm>
#include<string>

using std::cin;
using std::cout;
using std::set;
using std::string;

void setIntersection(set<char>& s1, set<char>& s2) {
    for (set<char>::const_iterator i = s1.begin();
                                    i != s1.end();
                                               ++i) {
        if (s2.find(*i) == s2.end()) {
            s1.erase(i);
        }
    }

}

void wordsIntersection() {
    int n = 0;
    cin >> n;
    string word;
    cin >> word;
    set<char> st;
    for (int i = 0; i < word.length(); ++i) {
        st.insert(word[i]);
    }
    set<char> stTmp;
    for (int i = 0; i < n - 1; ++i) {
        cin >> word;
        for (int j = 0; j < word.length(); ++j) {
            stTmp.insert(word[j]);
        }
        setIntersection(st, stTmp);
        stTmp.clear();
    }
    for (set<char>::const_iterator i = st.begin();
                                    i != st.end();
                                              ++i) {
        cout << *i << ' ';
    }
}

int main() {
    wordsIntersection();
    return 0;
}
