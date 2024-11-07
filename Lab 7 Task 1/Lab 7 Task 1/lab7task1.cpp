//include neccessary libraries
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
using namespace std;

int main() {

	ifstream inputFile("data.csv"); //open the data csv

	string line, value; //declare variables for calculating where the information is

	const string headers[] = { "Name", "Age", "City" }; //sample file does not contain this information so I added it here
	const int numHeaders = sizeof(headers) / sizeof(headers[0]);

	while (getline(inputFile, line)) {
		istringstream ss(line);
		int index = 0;
		while (getline(ss, value, ',')) {
			if (index < numHeaders) {
				cout << headers[index] << ": " << value;
			}
			else {
				cout << "Unnamed: " << value; //if there are extra columns assign this header
			}
			if (ss.peek() != EOF) cout << ", "; //add a comma between each field
			index++;
		}
		cout << endl;
	}

	inputFile.close(); //close the file 

	return 0;
}