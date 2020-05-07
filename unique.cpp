/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Jayson Infante
 * Date        : 2/18/20
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System - jinfante
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    int length = s.length();
    for (int i = 0; i < length; i++){
        if (!(islower(s[i]))){
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    int length = s.length();
    unsigned int bitset = 0;
    for (int i = 0; i < length; i++){
        unsigned int char_setter = 1 << (s[i] - 'a');
        if (char_setter & bitset){
            return false;
        }
        bitset |= char_setter;
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    string input_word;
    istringstream iss;

    if (argc != 2)
    {
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    iss.str(argv[1]);
    if (!(iss >> input_word))
    {
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    if(!(is_all_lowercase(input_word)))
    {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if(all_unique_letters(input_word))
    {
        cout << "All letters are unique." << endl;
    }

    else
    {
        cout << "Duplicate letters found." << endl;
    }
    return 0;
}
