#include <iostream>
#include <fstream>
using namespace std;

int main() {
    fstream file("data.txt", ios::in | ios::out | ios::trunc);  // Open for reading and writing

    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    // Write data to the file
    file << "C++ File Handling Example" << endl;
    file << "Using fstream for both read and write operations." << endl;

    // Reset file pointer to the beginning of the file for reading
    file.seekg(0);

    // Read and display the data
    string line;
    cout << "Reading from file:" << endl;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();  // Close the file
    return 0;
}
