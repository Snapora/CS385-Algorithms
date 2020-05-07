/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Jayson Infante
 * Date        : 2/25/20
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> ways;
    vector<int> empty;
    if (num_stairs <= 0){
        ways.push_back(empty);
    }
    else{
        for (int i = 1; i < 4; i++){
            if (num_stairs >= i){
                vector<vector<int>> result = get_ways(num_stairs - i);
                int resultlength = result.size();
                for (int j = 0; j < resultlength; j++){
                    result[j].insert(result[j].begin(), i);
                    ways.push_back(result[j]);
                }
            }
        }
    }
    return ways;
}

int num_digits(int num) {
    int inc = 0;
    while (num != 0) {
        inc++;
        num = num / 10;
    }
    return inc;
}

void display_ways(const vector<vector<int>> &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int counter = 1;
    int ways_size = ways.size();
    // auto& way: ways
    for(int i = 0; i < ways_size; i++){
        vector<int> way = ways[i];
        int way_size = ways[i].size();
        cout << setw(num_digits(ways_size)) << counter;
        cout << ". [";
        for (int j = 0; j < way_size; j++){
            if (j == way_size - 1){
                cout << way[j];
            }
            else{
                cout << way[j] << ", ";
            }
        }
        cout << "]" << endl;
        counter += 1;
    }
}


int main(int argc, char * const argv[]) {
    istringstream iss;
    int input_num;


    if (argc != 2)
    {
        cerr << "Usage: ./stairclimber <number of stairs>";
        return 1;
    }

    iss.str(argv[1]);
    if (!(iss >> input_num))
    {
        cerr << "Error: Number of stairs must be a positive integer.";
        return 1;
    }
    if (input_num < 1) {
        cerr << "Error: Number of stairs must be a positive integer.";
        return 1;
    }

    int ways = (get_ways(input_num)).size();
    if (ways == 1){
        cout << ways << " way to climb " << input_num << " stair." << endl;
    }
    else{
        cout << ways << " ways to climb " << input_num << " stairs." << endl;
    }
    display_ways(get_ways(input_num));
    return 0;
}
