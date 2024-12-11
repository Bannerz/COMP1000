#include <iostream>
using namespace std;

int main() {

	int usrIn;

	cout << "Please Select an Option: " << endl;
	cout << "1: Start Game" << endl;
	cout << "2: Load Game" << endl;
	cout << "3: Quit" << endl;
	cout << "Choice: ";

	cin >> usrIn;

	switch (usrIn) {
	case 1:
		cout << "New game starting..." << endl;
		break;

	case 2:
		cout << "Loading game..." << endl;
		break;

	case 3:
		cout << "Quitting game..." << endl;
		break;
	default:
		cout << "Invalid input" << endl;
	}

	

	return 0;
}