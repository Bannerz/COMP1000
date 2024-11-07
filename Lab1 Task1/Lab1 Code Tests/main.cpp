#include <iostream>
using namespace std;

int main() {
	//initial varibales
	int age = 20;
	string name = "Alice";
	float height = 1.65;
	char grade = 'B';

	//print first lot
	cout << "Name: " << name << endl;
	cout << "Age: " << age << endl;
	cout << "Height: " << height << endl;
	cout << "Grade: " << grade << endl;

	//update variables
	age = 22;
	name = "Bob";
	height = 1.75;
	grade = 'A';

	//print second lot
	cout << "Name: " << name << endl;
	cout << "Age: " << age << endl;
	cout << "Height: " << height << endl;
	cout << "Grade: " << grade << endl;



	return 0;
}