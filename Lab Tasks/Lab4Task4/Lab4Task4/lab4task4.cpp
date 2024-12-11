#include <iostream>
using namespace std;

int main() {
	int myArray[5] = { 4,2,5,7,4 };

    int outPut;
    
	int* ptr = &myArray[0];

    for (int i = 0; i < 5; i++) {
        cout << "Value of " << i << " myArray[" << i << "] is "
            << *(ptr + i) << endl;
        cout << "Address of " << *(ptr + i) << " is  "
            << ptr + i << endl
            << endl;
    }

    for (int x = 0; x < 5; x++) {
        outPut = *(ptr + x) + 2;

        cout << "Item " << x << ":" << outPut << endl;
    }

	return 0;
}