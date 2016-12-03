#include<iostream>
#include<list>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;


void printData(list<int>& lst) {
    cout << lst.size();
    for (list<int>::const_iterator i = lst.begin(); i != lst.end(); ++i) {
        cout << ' ' << *i;
    }
    cout << endl;
}

void interactive() {
    list<int> lst;
    int m = 0;
    cin >> m;
    string command;
    int value = 0;
    for (int i = 0; i < m; ++i) {
        cin >> command;
        switch(command[0]) {
            case 'b':
                cin >> value;
                lst.push_front(value);
                break;
            case 'e':
                cin >> value;
                lst.push_back(value);
                break;
            case 'p':
                printData(lst);
                break;
            default:
                cout << "error";
        }
    }
}

int main() {
    interactive();
    return 0;
}
