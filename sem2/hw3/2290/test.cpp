#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

int main() {
    map<int, set<pair<int, int>>> tooHard;
    set<pair<int, int>> st;
    pair<int, int> Moscow(1, 2);
    pair<int, int> NY(10, 20);
    st.insert(Moscow);
    st.insert(NY);
    tooHard[1] = st;
    for (auto it = tooHard[1].begin(); it != tooHard[1].end(); ++it) {
        cout << it->first << it->second << '\n';
    }
    return 0;
}
