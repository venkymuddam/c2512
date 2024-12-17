
#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    int id;
    int age;       
    string name;   

public:
    Employee(int empId, int empAge, const string& empName) 
        : id(empId), age(empAge), name(empName) {}

    Employee(Employee&& other) noexcept
        : id(other.id), age(other.age), name(std::move(other.name)) {
        other.id = 0;
        other.age = 0;
    }

    Employee& operator=(Employee&& other) noexcept {
        if (this != &other) {
            id = other.id;
            age = other.age;
            name = std::move(other.name);
            
            other.id = 0;
            other.age = 0;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Employee& emp) {
        os << emp.id << " " << emp.age << " " << emp.name;
        return os;
    }

    void swap(Employee& other) {
        Employee temp = std::move(*this);  
        
        *this = std::move(other);
        
        other = std::move(temp);
    }
};

int main() {
    Employee e1(101, 22, "Athira");
    Employee e2(102, 23, "Bhagya");

    cout << "Before swapping:" << endl;
    cout << e1 << endl; 
    cout << e2 << endl; 

    e1.swap(e2);

    cout << "swapped : " << endl;
    cout << e1 << endl; 
    cout << e2 << endl; 

    return 0;
}
