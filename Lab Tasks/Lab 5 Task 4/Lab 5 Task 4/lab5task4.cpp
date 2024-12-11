#include <iostream>
using namespace std;

int counter = 0;

void incrementCounter() {
	counter = counter++;
}

void displayCounter() {
	cout << counter << endl;
}

int main() {

	cout << "Increment not called yet: " << counter << endl;
	incrementCounter(); // call increment
	cout << "Displaying counter from main: " << counter << endl;

	cout << "Displaying counter from displayCounter(): ";
	displayCounter();
	return 0;
}