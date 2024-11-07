#include <iostream>
using namespace std;

int main() {
	//initial varibales

	int num1;
	int num2;

	int addSum;
	int subSum;
	int multSum;
	float divSum;
	int modSum;

	cout << "Type the first number: ";
	cin >> num1;
	cout << "Type the second number: ";
	cin >> num2;

	addSum = num1 + num2;
	subSum = num1 - num2;
	multSum = num1 * num2;
	divSum = num1 / num2;
	modSum = num1 % num2;

	cout << "Addition: " << addSum << endl;
	cout << "Subtraction: " << subSum << endl;
	cout << "Multiplication: " << multSum << endl;
	cout << "Division: " << divSum << endl;
	cout << "Modulus: " << modSum << endl;



	return 0;
}