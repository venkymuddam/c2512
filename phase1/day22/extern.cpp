#include <iostream>
#include <string>
using namespace std;

void display_username();


string username = "Sooraj";
int main() {
    int id = 100;
    display_username();
    return 0;
}


void display_username() {
    cout << "Username: " << username << endl;
}
