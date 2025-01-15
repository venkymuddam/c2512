#include <iostream>
using namespace std;

int add(int num1, int num2);
float add(float num1, float num2);

int main(){
    add(2,3);
    add(3.0f, 5.0f);

    return 0;
}

int add(int num1, int num2){
    return (num1 + num2);
}

float add(float num1, float num2){
    return (num1 + num2);
}
