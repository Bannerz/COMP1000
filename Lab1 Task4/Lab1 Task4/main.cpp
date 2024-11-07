#include <iostream>
using namespace std;

int main() {
    //initialise variables
    int num1;
    int num2;

    int implicitResult;

    //make sure explicit result will be float
    float explicitResult;

    //inputs
    cout << "Type first number here: ";
    cin >> num1;
    cout << "Type second number here: ";
    cin >> num2;

    //implicit divide
    implicitResult = num1 / num2;

    //cast num1 and num2 variables to float for a decimal result
    explicitResult = (float)num1 / (float)num2;

    //print results
    cout << "Result without type casting (integer division): " << implicitResult << endl;

    cout << "Result with type casting (float division): " << explicitResult << endl;


    //the results are different because one is calculating with integers which cannot perform floating point
    //the other is using float division that allows for calculation of real numbers with decimal places
    return 0;
}