#include <iostream>
using namespace std;

// Base class
class Animal {
public:
    // Virtual function (This allows runtime polymorphism)
    virtual void sound() {
        cout << "Animal makes a sound" << endl;
    }
    virtual ~Animal(){
        cout << "animal destructor     " << endl;
    }
};

// Derived class 1
class Dog : public Animal {
public:
    // Overriding the base class function
    void sound() override {
        cout << "Dog barks" << endl;
    }
    
    ~Dog(){
        cout << "dog destructor     " << endl;
    }
};

// Derived class 2
class Cat : public Animal {
public:
    // Overriding the base class function
    void sound() override {
        cout << "Cat meows" << endl;
    }
    
    ~Cat(){
        cout << "cat destructor     " << endl;
    }
};

// Function to demonstrate dynamic polymorphism
void makeSound(Animal* animal) {
    // The function call will be determined at runtime based on the actual object type (Dog or Cat)
    animal->sound();
}

int main() {
    //Create objects of derived classes
    // Dog dog;
    // Cat cat;
    

    // // Demonstrating dynamic polymorphism using base class pointer
    // Animal* animal1 = &dog;
    // Animal* animal2 = &cat;

    // // Function call that resolves to the appropriate method at runtime
    // cout << "Animal 1: ";
    // makeSound(animal1);  // Output: Dog barks

    // cout << "Animal 2: ";
    // makeSound(animal2);  // Output: Cat meows
    
    
    // cout << endl << endl;
    
    // dynamic objects
    
    
    Animal* ob1 = new Animal();
    
    cout << "Animal: ";
    makeSound(ob1);  // Output: Cat meows
    
    Animal* ob2 = new Dog();
    
    //Function call that resolves to the appropriate method at runtime
    cout << "Animal 1: ";
    makeSound(ob2);  // Output: Dog barks
    
    Animal* ob3 = new Cat();
    
    cout << "Animal 2: ";
    makeSound(ob3);  // Output: Cat meows
    
    
    delete ob3;
    delete ob2;
    delete ob1;
    
    

    return 0;
}
