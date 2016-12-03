#include<iostream>
#include<vector>


using std::cout;
using std::vector;

void PrintVector(vector<int>& a) {
    for (int ind = 0; ind < a.size(); ++ind) {
        cout << a[ind] << ' ';
    }
    cout << '\n';

}

void PrintStack(vector<int>& a, int stackNum) {
    cout << '[';
    for (int i = a.size() - 1; i >= 0; --i) {
        if (a[i] == stackNum) {
            cout << i + 1 << ' ';
        }
    }
    cout << "]\n";
}

void Print(vector<int>& a) {
    for (int i = 1; i < 4; ++i) {
        PrintStack(a, i);
    }
}

int GetDiskNum(vector<int>& a, int stackNum) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == stackNum) {
            return i;
        }
    }
}

int Hanoi3(int n, int i, int j, int k, bool write, vector<int>& location) {
    if (n > 0) {
        int n1 = Hanoi3(n - 1, i, k, j, write, location);
        int diskNum = GetDiskNum(location, i);
        location[diskNum] = j;


        if (write) {
            cout << '\n';
            Print(location);
        }
        int n2 = Hanoi3(n - 1, k, j, i, write, location);
        return (n1 + n2 + 1);
    } else {
        return 0;
    }
}

int main() {
    vector<int> location = {1, 1, 1};
    Print(location);
    int ans = Hanoi3(3, 1, 2, 3, true, location);
    cout << ans;
    return 0;
}
