#include <iostream>
using namespace std;

int main() {
	//initial varibales

	int a = 5;
	int b = 3;
	int c = 2;
	int d = 4;
	int e = 1;

	//standard integer arithmatic 
	int sum = a + b * c / d - e;

	//to avoid compiler performing integer division i used static_cast<float> to convert int to float to display proper result
	//PEMDAS arithmatic with floating point division
	//another way to do this would be to change the 2 to 2.0 to force float division
	float sum2 = (a + b) * (static_cast<float>(c) / (d - e));

	

	//outputs
	cout << "Result without brackets: " << sum << endl;
	cout << "Result with brackets: " << sum2 << endl;

	return 0;
}