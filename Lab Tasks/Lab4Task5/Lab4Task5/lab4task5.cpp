#include <iostream>

int main() {
   
    char* str = new char[20]; //create c style string array

    std::cout << "Enter a string (max 19 characters): ";
    std::cin.getline(str, 20);  //use getline to make sure spaces are counted

    std::cout << "You entered: " << str << std::endl; //print string
    std::cout << "Length of the string: " << strlen(str) << std::endl; //print length of string

    delete[] str; //deallocate memory

    return 0;
}

