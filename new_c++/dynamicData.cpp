
#include<iostream>
using namespace std;
#include<string>
#include<cstring>

class Dynamic{
    private:
        char* name;
        int* age;
        int* marks;
        string* isMale;

    public:
        Dynamic(char name_p[], int age_p, int marks_p[], int size_p, string isMale_p){
            name = new char(strlen(name_p)+1);
            strcpy(name, name_p);

            age = new int(sizeof(int));
            *age = age_p;

            marks = new int(size_p);
            for(int i = 0; i < size_p; i++){
                //marks[i] = marks_p[i];
                *(marks + i) = marks_p[i];
            }

            isMale = new string(isMale_p);
            cout << "constructor of age :" << *age << endl << endl; 
        }

        void display(){
            cout << "Name : " << name << ", Age : " << *age << endl << endl;
            // for(int i=0; i<2; i++){
            //     cout << marks[i] << endl;
            // }
            //cout << "IS Male : " << *isMale << endl;
        }

        ~Dynamic(){
            cout << "destructor                      of age :" << *age << endl << endl;
            delete[] name;
            delete age;
            delete[] marks;
            delete isMale;
            
        }
};

int main(){
    int mark[] = {100, 200};
    int sizee = 2;

// static objects
    // Dynamic ob2("venky", 2, mark, sizee, "yes");
    // Dynamic ob3("venky", 3, mark, sizee, "yes");
    // Dynamic ob1("venky", 1, mark, sizee, "yes");

    // ob3.display();
    // ob2.display();
    // ob1.display();

// dynamic objects
    Dynamic* ob2 = new Dynamic("venky", 2, mark, sizee, "yes");
    Dynamic* ob3 = new Dynamic("venky", 3, mark, sizee, "yes");
    Dynamic* ob1 = new Dynamic("venky", 1, mark, sizee, "yes");

    ob3->display();
    ob2->display();
    ob1->display();

    // delete ob1;
    // delete ob2;
    // delete ob3;

    return 0;
}
