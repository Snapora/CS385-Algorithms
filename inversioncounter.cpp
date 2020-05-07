/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Jayson Infante
 * Version     : 1.0
 * Date        : 3/24/20
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long inversioncounter = 0;
    for (int i = 0; i < length - 1; i++){
        for (int j = i + 1; j < length; j++){
            if (array[i] > array[j]){
                inversioncounter++;
            }
        }
    }
    return inversioncounter;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int *scratcharray = new int[length];
    long inversioncounter = mergesort(array, scratcharray, 0, length-1);
    delete [] scratcharray;
    return inversioncounter;
}

// Canvas Pseudocode for mergesort adjusted to count the number of inversions.
static long mergesort(int array[], int scratch[], int low, int high) {
    if (low < high){
        long inversioncounter = 0;
        int mid = low + (high - low) / 2;
        inversioncounter = inversioncounter + mergesort(array, scratch, low, mid);
        inversioncounter = inversioncounter + mergesort(array, scratch, mid+1, high);
        int L = low;
        int H = mid + 1;
        for (int k = low; k <= high; k++){
            if (L <= mid && (H > high || array[L] <= array[H])){
                scratch[k] = array[L];
                L = L + 1;
            }
            else {
                scratch[k] = array[H];
                H = H + 1;
                inversioncounter = inversioncounter + (mid + 1 - L);
            }
        }
        for (int k = low; k <= high; k++){
            array[k] = scratch[k];
        }
        return inversioncounter;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if (argc == 1){
        goto evaluatevector;
    }

    if (argc == 2){
        ostringstream oss;
        oss << argv[1];
        if (oss.str() != "slow"){
            cerr << "Error: Unrecognized option '" << oss.str() << "'." << endl;
            return 1;
        }
    }

    if (argc > 2){
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return 1;        
    }

evaluatevector:
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if (values.size() == 0){
        cerr << "Error: Sequence of integers not received.";
        return 1;
    }
    // TODO: produce output
    ostringstream speed;
    speed << argv[1];

    if (speed.str() == ""){
        int values_size = values.size();
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values_size) << endl;
    }

    else {
        int values_size = values.size();
        cout << "Number of inversions: " << count_inversions_slow(&values[0], values_size) << endl;
    }
    
    return 0;
}
