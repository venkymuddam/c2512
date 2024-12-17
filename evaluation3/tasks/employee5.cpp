  //1.5 construct array of N programmers. read programmers from keyboard.
        cin >> var; // overload operator>> in employee and programmer 

// code
#include <iostream>
#include <cstring>
#include <utility>
#include <memory>  
#include <vector>  

using namespace std;


class Employee {
private:
    unique_ptr<int> id;
    unique_ptr<int> age;
    unique_ptr<char[]> name;

public:
    
    Employee(int id, int age, const char* name) {
        this->id = make_unique<int>(id);
        this->age = make_unique<int>(age);
        this->name = make_unique<char[]>(strlen(name) + 1);
        strcpy(this->name.get(), name);
    }

    
    Employee() : id(nullptr), age(nullptr), name(nullptr) {}

    
    Employee(Employee&& other) noexcept
        : id(std::move(other.id)), age(std::move(other.age)), name(std::move(other.name)) {}

    
    Employee& operator=(Employee&& other) noexcept {
        if (this != &other) {
            id = std::move(other.id);
            age = std::move(other.age);
            name = std::move(other.name);
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Employee& emp);

    friend istream& operator>>(istream& is, Employee& emp);

    int getId() const { return *id; }
    int getAge() const { return *age; }
    const char* getName() const { return name.get(); }
};

ostream& operator<<(ostream& os, const Employee& emp) {
    os << *emp.id << " " << *emp.age << " " << emp.name.get();
    return os;
}

istream& operator>>(istream& is, Employee& emp) {
    int id, age;
    string name;
    cout << "Enter Employee ID: ";
    is >> id;
    cout << "Enter Employee Age: ";
    is >> age;
    cout << "Enter Employee Name: ";
    is.ignore();  
    getline(is, name);
    
    emp.id = make_unique<int>(id);
    emp.age = make_unique<int>(age);
    emp.name = make_unique<char[]>(name.length() + 1);
    strcpy(emp.name.get(), name.c_str());
    return is;
}

class Programmer : public Employee {
private:
    vector<string> tasks; 

public:
    
    Programmer() : Employee(), tasks() {}


    Programmer(int id, int age, const char* name, int taskCount, const string* tasksArray)
        : Employee(id, age, name) {
        tasks.reserve(taskCount);
        for (int i = 0; i < taskCount; ++i) {
            tasks.push_back(tasksArray[i]);  
        }
    }


    Programmer(Programmer&& other) noexcept
        : Employee(std::move(other)), tasks(std::move(other.tasks)) {}



    Programmer& operator=(Programmer&& other) noexcept {
        if (this != &other) {
            Employee::operator=(std::move(other));
            tasks = std::move(other.tasks);
        }
        return *this;
    }

    
    friend ostream& operator<<(ostream& os, const Programmer& prog);

    
    friend istream& operator>>(istream& is, Programmer& prog);
};

ostream& operator<<(ostream& os, const Programmer& prog) {
    os << static_cast<const Employee&>(prog) << " | Tasks: ";
    
    if (prog.tasks.empty()) {
        os << "No tasks available.";  
    } else {
        for (size_t i = 0; i < prog.tasks.size(); ++i) {
            os << prog.tasks[i] << (i < prog.tasks.size() - 1 ? ", " : "");
        }
    }

    return os;
}

istream& operator>>(istream& is, Programmer& prog) {
    Employee tempEmp;
    is >> tempEmp;  
    
    int taskCount;
    cout << "Enter number of tasks: ";
    is >> taskCount;

    string* tasksArray = new string[taskCount];
    cout << "Enter tasks:" << endl;
    for (int i = 0; i < taskCount; ++i) {
        is >> ws;  
        getline(is, tasksArray[i]);
    }

    prog = Programmer(tempEmp.getId(), tempEmp.getAge(), tempEmp.getName(), taskCount, tasksArray);

    delete[] tasksArray;  
    return is;
}

int main() {
    int N;
    cout << "Enter the number of programmers: ";
    cin >> N;

    vector<Programmer> programmers(N);

    for (int i = 0; i < N; ++i) {
        cout << "Enter details for Programmer " << (i + 1) << endl;
        cin >> programmers[i];  
    }

    cout << "\nProgrammer details:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << programmers[i] << endl;
    }

    return 0;
}
