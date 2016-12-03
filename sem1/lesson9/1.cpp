#include<vector>
#include<iostream>

const double kCtoF = 5.0 / 9;
const double kFtoC = 9.0 / 5;

double fromCtoF(double tC){
    return tC * kCtoF + 32;
}

double fromFtoC(double tF){
    return (tF - 32) * kFtoC;
}

int sumOfArifProgr(int a0, int d, int n){
    int sum = 0;
    int tmp = a0;
    for (int i = 0; i < n; ++i){
        sum += tmp;
        tmp += d;

    }
    return sum;
}

int sumOfArifPrigr_fast(int a, int d, int n){
    return n * a + d * (n - 1) * n / 2;
}


int sumVect(vector <int> v){
    sum = 0;
    for (int i = 0; i < v.size(); ++i){
        sum += v[i];
    }
    return sum;
}


int main() {
    vector<int> v;
    int n, x;
    std::cin >> n;
    for (int i = 0; i < n; ++i){
        std::cin >> x;
        v.push_back(x);
        std::cout << sumVect(v) << std::endl;
        return 0;
    }


/*    double x = 0;
    char q = 'A';
    std::cin >> x >> q;
    switch(q){
        case 'c':
        case 'C': //in switch you shouldn't write {}
            x = fromCtoF(x);
            break;
        case 'f':
        case 'F':
            x = fromFtoC(x);
            break;
        default:
            std::cout << "error";
            break;
    }
    std::cout << x;

*/
    return 0;

}
