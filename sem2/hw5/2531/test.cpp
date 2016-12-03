#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <map>

using std::cout;
using std::vector;
using std::ifstream;
using std::min;
using std::queue;
using std::map;




int main() {
    map<int, int> m;
    //m[57];
    m[57] += 10;
    m[15] -= 1;
    for (auto elem : m) {
        cout << elem.first << ' ' << elem.second << '\n';
    }
    return 0;
}

