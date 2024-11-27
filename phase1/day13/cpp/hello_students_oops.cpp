#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

struct Student {
	int id;
	char name[255];
};

void student_read(Student& student);
void student_print(Student& student);

int main() {

	int N;
	cout << "Number of Students:"; cin >> N;


	Student students[N] {};

	for(int I = 0; I < N; I++) {
		cout << "Enter " << (I+1) << " th student details." << endl;  student_read(students[I]);
	}
	
	for(int I = 0; I < N; I++) {
		student_print(students[I]); 
	}

	return EXIT_SUCCESS;
}

void student_read(Student& student) {
	cout << "Enter id:";
	cin >> student.id;
	cout << "Enter name:";
	cin >> student.name;
}

void student_print(Student& student) {
	cout << "Hello " << student.name << " of id " << student.id << "!!!" << endl;
}
