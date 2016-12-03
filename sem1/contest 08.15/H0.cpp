#include <iostream>
#include <string>
#include <vector>


using namespace std;
string s;
vector<int> z;
int n;

int zfunc()
 {
    int l = 0;
    int r = 1;
    int tmp = 0;
    int val = 0;

    for (int i = 1; i < n; i++)
        {
        if (i >= r)
        {
            tmp = 0;
            while (i + tmp < n && s[tmp] == s[i + tmp])
            {
                tmp++;
            }
            z.push_back(tmp);
            l = i;
            r = i + tmp;
        }
        else
        {
            if (i + z[i - l] < r)
            {
                z.push_back(z[i - l]);
            }
            else
            {
                val = r - i;
                tmp = 0;
                while (r + tmp < n && s[r + tmp] == s[r - l + tmp])
                {
                    tmp++;
                    val++;
                }
                z.push_back(val);
                l = i;
                r = r + tmp;
            }

        }
        if (z[i] == n - i && n % i == 0)
        {
            return n / i;
        }
    }
    return 1;
}

int main() {
    cin >> s;
    n = s.length();

    z.push_back(n);

    int res = zfunc();
    cout << res;

    return 0;
}
