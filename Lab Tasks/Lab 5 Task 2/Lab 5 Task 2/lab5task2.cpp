#include <iostream>
using namespace std;

void swapNumbers(int a, int b) {

	cout << "Numbers before swap: " << a << " " << b << endl;
	a = a + b;
	b = a - b;
	a = a - b;

	cout << "Numbers after swap: " << a << " " << b << endl;
}

int main() {

	swapNumbers(6, 3);

	return 0;
}