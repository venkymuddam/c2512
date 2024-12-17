    //1.2 "id, age, name" as dynamic memory using new and delete 



// code
#include <iostream>
#include <cstring>
#include <utility>

using namespace std;

class Employee {
private:
    int* id;
    int* age;     
    char* name;

public:
    Employee(int id, int age, const char* name) {
        this->id = new int(id);                  
        this->age = new int(age);   
        this->name = new char[strlen(name) + 1]; 
        strcpy(this->name, name);
    }

    ~Employee() {
        delete id;   
        delete age;  
        delete[] name; 
    }

    Employee(Employee&& other) noexcept 
        : id(other.id), age(other.age), name(other.name) {
        other.id = nullptr;
        other.age = nullptr;
        other.name = nullptr; 
    }

    Employee& operator=(Employee&& other) noexcept {
        if (this != &other) {
            delete id;
            delete age;
            delete[] name;

            id = other.id;
            age = other.age;
            name = other.name;

            other.id = nullptr;
            other.age = nullptr;
            other.name = nullptr;
        }
        return *this;
    }

    void swap(Employee& other) {
        Employee temp(std::move(other)); 
        other = std::move(*this);       
        *this = std::move(temp);        
    }

    friend ostream& operator<<(ostream& os, const Employee& emp);
};

ostream& operator<<(ostream& os, const Employee& emp) {
    os << *emp.id << " " << *emp.age << " " << emp.name;
    return os;
}

int main() {
    Employee e1(101, 22, "Athira"), e2(102, 23, "Bhagya");

    cout << e1 << endl; 
    cout << e2 << endl; 

    e1.swap(e2);

    cout << e1 << endl; 
    cout << e2 << endl; 

    return 0;
}
