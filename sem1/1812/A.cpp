#include<vector>

while (true) {
    cin >> s;
    v.push_back(s);
    if (!cin) {
        break;
    }
}

sort(v.beging(), v,end());
char prevSymb = 0;
string prevStr;
// for (const string& s: v)
// for (auto i = v,begin(); i != v.end(); ++i)
for (vector<string>::const_iterator = v.begin(); i = v.begin(); i != v.end(); ++i) {
    const string prevStr = *i;
    if (prevStr[0] != prevSymb) {
        cout << prevStr[0] << " :" << endl;
        cout << prevStr << endl;
        prevSymb = prevStr[0];
    }
}

//----------------------------------------------------

while (true) {
    cin >> s;
    st.insert(s);
    if (!cin) {
        break;
    }
}


char prevSymb = 0;
string curStr;

for (const string& s: st) {
    if (s[0] != curStr) {
        cout << s[0] << ':' << endl;
    }
    cout << s << endl;
}


//-----------------------------------------------------

while (true) {
    cin >> s;
    mp[s[0]].insert(s);;
    if (!cin) {
        break;
    }
}


char prevSymb = 0;
string curStr;

for (const auto& i: mp) {
    cout << i.first << ':'<< endl;
    for (const string& s; i.second) {
        cout << s << endl;
    }
}
 //--------------------------------------------

a = (b + (c * d)) << 2) & 8 // OK
++++a-- // NOT
a & 077 |= 3 // NOT
sizeof(**p) // OK
(a == b) || ((a == c) && (c < 5)) // OK
// ^
// |
// first

a == (b | a) == ((c & c) < 5) // OK
