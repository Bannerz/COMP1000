#include <iostream>
using namespace std;

int valueInt = 4;
int *valuePtr = &valueInt;


int main() {

	cout << "Value of int: " << valueInt << endl;
	cout << "Address of int: " << valuePtr << endl;

	valuePtr = valuePtr++; //increment pointer value

	cout << "Address of incremented value: " << valuePtr << endl;



	return 0;
}