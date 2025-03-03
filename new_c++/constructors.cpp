
#include<iostream>
using namespace std;

class Example{
    private:
        int age;
        string name;

    public:
        // parametarised constructor
        Example(int age_p, string name_p) : age(age_p), name(name_p){cout << endl;}
        
        // no parameterised constructor 
        Example():Example(0, ""){
            cout << "This is empty constructor" << endl;
            cout << endl;
        }
        
        // copy constuctor 
        Example(const Example& other){
            age = other.age;
            name = other.name;
            cout << endl;
        }
        Example& operator=(Example& other){
            
            this->age = other.age;
            this->name = other.name;
            return *this;
            cout << endl;
        }

        // move constructor
        Example(Example&& other){
            age=other.age;
            name=other.name;
            
            other.age = 0;
            other.name = "";
            cout << endl;
            
        }
        Example& operator=(Example&& other) {
            age=other.age;
            name=other.name;
            
            other.age = 0;
            other.name = "";
            
            return *this;
            cout << endl;
        }

        void display(){
            cout << "name : " << name << endl << "age : " << age << endl;
            cout << endl;
        }
};

int main(){

// creating
    // no parametarised
    Example ob1;
    // parametarised
    Example ob2(1, "aaaaa");
    Example ob3(2, "bbbbb");
    Example ob4(3, "ccccc");
    // copy(it is deep copying)
    Example ob5(ob2); //1
    Example ob6=ob3; //2
    // move 
    Example ob7(move(ob2)); //1
    Example ob8=move(ob3); //2


// displaying
    // parametarised
    ob2.display();
    // copy
    ob5.display(); //1
    ob6.display(); //2
    // move
    ob7.display(); //1
    ob8.display(); //2
    
    return 0;
}
