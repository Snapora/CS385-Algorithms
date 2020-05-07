/*******************************************************************************
 * Name        : maxsumdescent.cpp
 * Author      : Jayson Infante
 * Version     : 1.0
 * Date        : 4/22/20
 * Description : Dynamic programming solution to max sum descent problem.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const char DELIMITER = ' ';

int **values, // This is your 2D array of values, read from the file.
    **sums;   // This is your 2D array of partial sums, used in DP.

int num_rows; // num_rows tells you how many rows the 2D array has.
              // The first row has 1 column, the second row has 2 columns, and
              // so on...

int num_digits(int num) {
    int inc = 0;
    while (num != 0) {
        inc++;
        num = num / 10;
    }
    return inc;
}

/**
 * Displays the 2D array of values read from the file in the format of a table.
 */
void display_table() {
    // TODO
    if (num_rows == 0){
        return;
    }
    int max = values[0][0];
    for (int i = 1; i < num_rows; ++i) {
        for (int j = 0; j <= i; ++j){
            if (values[i][j] > max){
                max = values[i][j];
                // if (num_digits(max) > 2){
                //     goto display;
                // }
            }
        }
    }

// display:
    int max_digits = num_digits(max);
    for (int i = 0; i < num_rows; ++i){
        for (int j = 0; j <= i; ++j){
            if (i == j){
                cout << setw(max_digits) << values[i][j];
            }
            else{
                cout << setw(max_digits) << values[i][j] << " ";
            }
        }
        cout << endl;
    }
}

/**
 * Returns the maximum sum possible in the triangle of values.
 * By starting at the top of the triangle and moving to adjacent numbers on the
 * row below, this function uses dynamic programming to build up another table
 * of partial sums.
 */
int compute_max_sum() {
    // TODO

    // Populate the 2D array of partial sums. It should still work even if
    // num_rows is 0 (i.e. the file was blank).
    if (num_rows == 0){
        return 0;
    }

    if (num_rows == 1){
        return values[0][0];
    }

    sums[0][0] = values[0][0];
    for (int i = 1; i <= num_rows - 1; ++i){
        for (int j = 0; j <= i; ++j){
            if (j != 0 && j != i){
                if (sums[i-1][j-1] > sums[i-1][j]){
                    sums[i][j] = values[i][j] + sums[i-1][j-1];
                }
                else{
                    sums[i][j] = values[i][j] + sums[i-1][j];
                }
            }
            else if (j == 0){
                sums[i][j] = values[i][j] + sums[i-1][j];
            }
            else{
                sums[i][j] = values[i][j] + sums[i-1][j-1];
            }
        }
    }


    // Loop over the last row to find the max sum.
    int max_sum = sums[num_rows - 1][0];

    for (int j = 1; j < num_rows; ++j){
        if (sums[num_rows-1][j] > max_sum){
            max_sum = sums[num_rows-1][j];
        }
    }
    // Return the max sum.
    return max_sum;
}

/**
 * Returns a vector of ints with the values from the top to the bottom of the
 * triangle that comprise the maximum sum.
 */
vector<int> backtrack_solution() {
    vector<int> solution;
    // TODO
    if (num_rows == 0){
        return solution;
    }

    if (num_rows == 1){
        solution.push_back(values[0][0]);
        return solution;
    }

    int max_sum = sums[num_rows - 1][0];
    int max_index = 0;

    for (int j = 1; j < num_rows; ++j){
        if (sums[num_rows-1][j] > max_sum){
            max_sum = sums[num_rows-1][j];
            max_index = j;
        }
    }

    solution.push_back(values[num_rows-1][max_index]);
    for (int i = num_rows - 1; i > 0; --i){
        if (max_index == 0) {
            solution.push_back(values[i-1][max_index]);
        }

        else if (max_index == i){
            solution.push_back(values[i-1][max_index-1]);
            max_index -= 1;
        }
        
        else{
            if (sums[i-1][max_index-1] > sums[i-1][max_index]){
                solution.push_back(values[i-1][max_index-1]);
                max_index = max_index - 1;
            } 
            else{
                solution.push_back(values[i-1][max_index]);
            }
        }
    }

    reverse(solution.begin(),solution.end());
    return solution;
}

/**
 * Reads the contents of the file into the global 2D array 'values'. If
 * successful, the function also allocates memory for the 2D array 'sums'.
 */
bool load_values_from_file(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: Cannot open file '" << filename << "'." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> data;
    try {
        while (getline(input_file, line)) {
            data.push_back(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
    

    // TODO
    num_rows = data.size();
    values = new int*[num_rows];
    for (int i = 0; i < num_rows; ++i){
        values[i] = new int[num_rows];
    }

    int i = 0;
    for(string bar: data){
        // vector<int> temp;
        istringstream iss(bar);
        int n, g=0;
        while (iss >> n){
            values[i][g] = n;
            ++g;
        }
        ++i;
    }

    sums = new int*[num_rows];
    for (int i = 0; i < num_rows; ++i){
        sums[i] = new int[num_rows];
    }

    return true;
}

/**
 * Frees up the memory allocated for the 2D array of values and the 2D array of
 * partial sums.
 */
void cleanup() {
    // TODO
    for(int i = 0; i < num_rows; ++i){
        delete[] values[i];
    }
    delete[] values;

    for(int j = 0; j < num_rows; ++j){
        delete[] sums[j];
    }
    delete[] sums;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }

    // TODO
    display_table();
    cout << "Max sum: " << compute_max_sum() << endl;
    cout << "Values: [";
    vector<int> intvector = backtrack_solution();
    int intvectorsize = intvector.size();
    for (int i = 0; i < intvectorsize; ++i) {
        if (i == intvectorsize - 1){
            cout << intvector[i];
        }
        else{
            cout << intvector[i] << ", ";
        }
    }
    cout << "]" << endl;
    cleanup(); 

    return 0;
}
