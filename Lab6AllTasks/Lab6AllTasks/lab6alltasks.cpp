#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void q1() {

	cout << "Question 1: " << endl;

	ofstream question1File("q1file.txt"); //create txt file called q1file.txt

	float thisIsAFloat = 12.5; //define a float

	if (question1File.is_open()) { //check file has opened properly

		question1File << "This is writing a string" << endl; //write a string

		question1File << 176 << endl; //write an int

		question1File << thisIsAFloat << endl; //write the float
	}
	else {
		cout << "something went wrong";
	}

	

	question1File.close(); //close the file

	cout << endl;

}

void q2() {

	cout << "Question 2: " << endl;

	string fileText; //declare the variable to store the data

	ifstream existingFile("q1file.txt"); //open the file
	if (existingFile.is_open()) {
		while (getline(existingFile, fileText)) {
			cout << fileText << endl;
		}
	}
	else {
		cout << "failed to open file";
	}
	

	existingFile.close();

	cout << endl;
}

void q3() {

	cout << "Question 3: " << endl;

	ifstream inputFile("source.txt"); //source file

	ofstream outputFile("destination.txt"); //destination file to copy to

	char ch; //variable for storing contents of file

	if (inputFile.is_open() && outputFile.is_open()) { //if both files are open
		while (inputFile.get(ch)) { //while there are characters to read, get them and store in ch variable
			outputFile.put(ch); //write ch to the destination file
		}
		inputFile.close(); //close files
		outputFile.close();//close files
	}

	cout << endl;
}

void q4() {

	cout << "Question 4: " << endl;
	ifstream question4File("q4file.txt"); //open txt file called q4file.txt

	int value; //declare value variable

	while (true) {
		question4File >> value; //store contents of q4file.txt in value variable

		if (question4File.eof()) { //if reached end of file print this
			cout << "End of file reached" << endl;
			break;
		}

		if (question4File.fail()) { //if invalid data is detected print this and clear the stream
			cerr << "Error: invalid data" << endl;
			question4File.clear();
			question4File.ignore(100, '\n'); //ignore the error and start a new line to continue the program
		}
		else {
			cout << "Value: " << value << endl; //if all is good print the contents of value variable
		}
	}
	question4File.close(); //close the file
	
	cout << endl;
}

int main() {

	q1(); //run q1
	q2(); //run q2
	q3(); //run q3
	q4(); //run q4

	return 0;
}