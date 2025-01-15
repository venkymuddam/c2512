#include <iostream>
using namespace std;

template <typename T>
T add(T num1, T num2);

int main(){
    cout << add(2,3) << endl;
    cout << add(3.5f, 5.0f);

    return 0;
}


template <typename T>
T add(T num1, T num2){
    return (num1 + num2);
}
