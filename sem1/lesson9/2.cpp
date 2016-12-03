#include<iostream>
int main(){
    int a = 7;
    int *pa = &a;

    a++;
    // std::cout << *pa << " " << &a << " " << a << " " << pa;
    std::cout << sizeof(char*) << " " << sizeof(int**);
    return 0;
}
