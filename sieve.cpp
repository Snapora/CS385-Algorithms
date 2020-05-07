/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Jayson Infante
 * Date        : 2/3/2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

//This is a constructor
PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_),
             primes_per_row = 80 / (max_prime_width + 1);

    cout << endl;
    cout << "Number of primes found: " << count_num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
    int counter = 0;
    int lastcounter = 0;

    if (count_num_primes() < primes_per_row){
        for (int i=0; i <= limit_; i++){
            if(is_prime_[i] == true){
                if (counter == count_num_primes()-1){
                    cout << i;
                }
                else{
                    cout << i << " ";
                    counter++;
                }
            }
        }
    }
    else{
        for (int i = 0; i <= limit_; i++){
            if (is_prime_[i] == true){
                counter++;
                lastcounter++;
                if (lastcounter == count_num_primes()){
                    cout << setw(max_prime_width) << i;
                }
                else if (counter == primes_per_row){
                    cout << setw(max_prime_width) << i << endl;
                    counter = 0;
                }
                else{
                    cout << setw(max_prime_width) << i;
                    cout << " ";
                }

            }
        }
    }

}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    return num_primes_;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    is_prime_[0] = false;
    is_prime_[1] = false;
    for (int i = 2; i <= limit_; i++){
        is_prime_[i] = true;
    }
    
    for (int i = 2; i <= sqrt(limit_); i++){
        if (is_prime_[i] == true){
            for (int j = i*i; j<=limit_; j+=i){
                is_prime_[j] = false;
            }
        }  
    }

    num_primes_ = 0;
    for (int i = 0; i <= limit_; i++){
        if (is_prime_[i] == true){
            num_primes_++;
        }
    }

    max_prime_ = limit_;
    for (int i = limit_ ; i > 0; i--){
        if (is_prime_[i] == true){
            max_prime_ = i;
            break;
        }
    }

}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int inc = 0;
    while (num != 0) {
        inc++;
        num = num / 10;
    }
    return inc;
}

// bool is_prime(int num){
//     bool isPrime = true;

//     for (int i = 2; i <= num / 2; i++){
//         if (num % i == 0) {
//             isPrime = false;
//             break;
//         }
//     }
//     return isPrime;
// }

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve x(limit);
    x.display_primes();

    return 0;
}
