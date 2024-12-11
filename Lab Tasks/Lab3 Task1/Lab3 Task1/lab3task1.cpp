#include <iostream>
using namespace std;

int main() {
	int age;

	cout << "What is your age? ";
	cin >> age;

	if (age >= 18) {
		cout << "You are eligable to vote";
	}
	else {
		cout << "You are ineligable to vote";
	}


	return 0;
}