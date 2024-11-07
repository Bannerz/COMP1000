#include <iostream>
using namespace std;

//global var

int globalVar = 23;
static int staticVar = 40;

void incrementVar() {

	//local var
	int localVar = 10;
	static int localStaticVar = 4;
	localVar++;
	globalVar++;
	staticVar++;
	localStaticVar++;
	//output variables
	cout << "Global Variable: " << globalVar << endl;
	cout << "Static Variable: " << staticVar << endl;
	cout << "Local Variable: " << localVar << endl;
	cout << "Static Local Variable: " << localStaticVar << endl;
	

}


int main() {
	//call function 3 times
	incrementVar();
	incrementVar();
	incrementVar();

	return 0;
}