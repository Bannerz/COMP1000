#include <iostream>
using namespace std;

string strOne = "string one";
string strTwo = "striuuung two";

string contStr;

int contSize;

int strOneSize, strTwoSize;

int main(){

	contStr = strOne + strTwo;

	contSize = contStr.size();

	strOneSize = strOne.size();
	strTwoSize = strTwo.size();

	if (strOneSize == strTwoSize) {
		cout << "Input strings are the same length" << endl;
	}
	else {
		cout << "Input strings are not the same length" << endl;
	}

	cout << "Concatenated String: " << contStr << endl;
	cout << "Size of concatenated string (including spaces): " << contSize << endl;;


	return 0;
}