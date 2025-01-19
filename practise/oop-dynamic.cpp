#include <iostream>
#include <cstring>
using namespace std;

class DynamicClass {
private:
    int* size;        // Dynamic size field
    int* arr;         // Pointer to dynamically allocated array
    string* name;       // Pointer to a dynamically allocated string

public:
    // Constructor
    DynamicClass(int size_p, int arr_p[], string name_p) {
        size = new int(size_p);            // Dynamically allocate size
        arr = new int[*size];             // Dynamically allocate array
        name = new string(name_p); // Dynamically allocate string
        //strcpy(name, name_p);             // Copy the string into the dynamically allocated memory

        // Initialize the array
        for (int i = 0; i < *size; i++) {
            arr[i] = arr_p[i];
        }
    }

    // Member function to display the data
    void display() const {
        cout << "Name: " << *name << endl;
        cout << "Size: " << *size << endl;
        cout << "Array Contents: ";
        for (int i = 0; i < *size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Destructor
    ~DynamicClass() {
        delete size;   // Free dynamically allocated size
        delete[] arr;  // Free dynamically allocated array
        delete name; // Free dynamically allocated string
    }
};

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    string stringName;
    cout << "Enter the string: ";
    cin >> stringName;

    // Create an array for testing
    int* vec = new int[n];
    cout << "Enter " << n << " elements for the array: ";
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }

    // Create an object of the class
    DynamicClass obj(n, vec, stringName);

    // Display the data
    obj.display();

    // Clean up dynamically allocated memory
    delete[] vec;

    return 0;
}
