#include <iostream>
using namespace std;

void trackFunctionCalls() {
	static int trackCounter = 0;

	trackCounter++;

	cout << trackCounter << endl;
}

int main() {

	trackFunctionCalls();

	trackFunctionCalls();

	trackFunctionCalls();

	return 0;
}