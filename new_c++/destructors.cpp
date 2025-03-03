
#include<iostream>
using namespace std;

class Example{
    private:
        int age;
        string name;

    public:
        // parametarised constructor
        Example(int age_p, string name_p) : age(age_p), name(name_p){
            cout << "constructor details,            name : " << name << ", age : " << age << endl << endl; 
        }
        
        // no parametarised constructor 
        // Example():Example(0, ""){
        //     cout << "This is empty constructor" << endl;
        //     cout << endl;
        // }

        ~Example(){
            cout << "destructor details, name : " << name << ", age : " << age << endl << endl; 
        }
        
        void display(){
            cout << "name : " << name << endl << "age : " << age << endl;
            cout << endl;
        }
};

int main(){
// static objects
    // creating
    Example ob1(1, "aaaaa");
    Example ob2(2, "bbbbb");
    Example ob3(3, "ccccc");
    

    // displaying
    cout << "started " << endl << endl;
    ob1.display();
    ob2.display();
    ob3.display();
    cout << "ended " << endl << endl;


// // dynamic objects
//     // creating
//     Example* ob2 = new Example(2, "bbbbb");
//     Example* ob3 = new Example(3, "ccccc");
//     Example* ob1 = new Example(1, "aaaaa");

//     // displaying
//     ob1->display();
//     ob2->display();
//     ob3->display();

//     delete ob1;
//     delete ob3;
//     delete ob2;

    return 0;
    
}
