#include <iostream>
using namespace std;

int main() {

	int marks;

	cout << "Please input marks attained: ";

	cin >> marks;

	if (marks >= 90) {
		cout << "You got an A!" << endl;

	}
	else if (marks >= 80) {
		cout << "You got a B!" << endl;
	}
	else if (marks >= 70) {
		cout << "You got a C." << endl;
	}
	else if (marks >= 60) {
		cout << "You got a D..." << endl;
	}
	else {
		cout << "You got an F." << endl;
	}

	return 0;
}