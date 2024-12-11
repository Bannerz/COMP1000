#include <iostream>
using namespace std;

int main() {

	int temp;

	cout << "Input temperature: ";
	cin >> temp;

	if (temp <= 0) {
		cout << "It's freezing" << endl;
	}
	else if (temp <= 15) {
		cout << "It's cold" << endl;
	}
	else if (temp < 30) {
		cout << "It's warm" << endl;
	}
	else {
		cout << "It's hot" << endl;
	}

	return 0;
}