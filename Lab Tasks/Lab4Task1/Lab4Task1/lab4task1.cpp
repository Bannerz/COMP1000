#include <iostream>
using namespace std;

const int arrSize = 10;
int numArray[arrSize]{};
int sum;
float average;


int main(){
	

	for (int i = 1; i <= 10; i++) {
		numArray[i] = i;
		cout << numArray[i] << " ";
	}
	cout << endl;
	for (int x = 0; x < arrSize; x++) {
		sum = sum + numArray[x];
	}

	for (int y = 0; y < arrSize; y++) {
		average = average + numArray[y] / static_cast<float>(arrSize);
	}

	cout << "The sum of the array is: " << sum << endl;
	cout << "The average of the array is: " << average << endl;
	return 0;
}