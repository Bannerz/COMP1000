#include <iostream>
using namespace std;

int main() {

	int num = 0;

	while (num >= 0) {
		
		cout << "Input number: ";
		cin >> num;
		if (num > 0) {
			continue;
		}
		else {
			cout << "You enetered a negative number, goodbye";
			break;
		}


	}



	return 0;
}