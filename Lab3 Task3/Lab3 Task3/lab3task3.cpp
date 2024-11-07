#include <iostream>
using namespace std;

int main() {
	int num1;
	int num2;
	float result;

	int operation;

	cout << "Input 1: ";
	cin >> num1;

	cout << "Input 2: ";
	cin >> num2;

	cout << "Operator (1=+, 2=-, 3=*, 4=/: ";
	cin >> operation;

	switch (operation) {
		case 1: 
			result = num1 + num2;
			cout << result << endl;
			break;
			

		case 2: 
			result = num1 - num2;
			cout << result << endl;
			break;
		
		
		case 3: 
			result = num1 * num2;
			cout << result << endl;
			break;
		

		case 4: 
			result = static_cast<float>(num1) / static_cast<float>(num2);
			cout << result << endl;
			break;
		

		default:
			cout << "Invalid input";
	}

	

	return 0;
}