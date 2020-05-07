/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Jayson Infante, Bharddwaj Vemulapalli
 * Date        : 3/13/20
 * Description : Solving the Waterjug Puzzle using BFS.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

State pouring(State s, int step, const int capacities[]){
    /*  Algorithm
    1) Pour from C to A
    2) Pour from B to A
    3) Pour from C to B
    4) Pour from A to B
    5) Pour from B to C
    6) Pour from A to C
    */
    if(step == 1){
        //Pour from C to A
        int tempA = s.a;
        s.a += s.c;
        if(s.a > capacities[0]) {
            //if you cannot pour everything in c
            //into a, then fill up a to capacity
            //subtract that capacity from c
            s.a = capacities[0];
            //s.c -= capacities[0];
            s.c -= capacities[0] - tempA;
            if(capacities[0] - tempA == 1){
                s.directions += "Pour " + to_string(capacities[0] - tempA) + " gallon from C to A. " + s.to_string()+ '\n';
            }
            else{
                s.directions += "Pour " + to_string(capacities[0] - tempA) + " gallons from C to A. " + s.to_string()+ '\n';
            }
        }
        else{
            // if s.a + s.c <= its capacity
            //then that means that all of c was poured
            int tempC = s.c;
            s.c = 0;
            if(tempC == 1){
                 s.directions += "Pour " + to_string(tempC) + " gallon from C to A. " + s.to_string() + '\n';
            }
            else{
                s.directions += "Pour " + to_string(tempC) + " gallons from C to A. " + s.to_string() + '\n';
            }
            
        }
        
    }

    else if(step == 2){
        //Pour from B to A
        int tempA = s.a;
        s.a += s.b;
        if(s.a > capacities[0]){
            s.a = capacities[0];
            s.b -= capacities[0] - tempA;
            
            if(capacities[0] - tempA == 1){
                s.directions += "Pour " + to_string(capacities[0] - tempA) + " gallon from B to A. " + s.to_string()+ '\n';
            }
            else{
                s.directions += "Pour " + to_string(capacities[0] - tempA) + " gallons from B to A. " + s.to_string()+ '\n';
            }
        }
        else{
            int tempB = s.b;
            s.b = 0;
             
            if(tempB == 1){
                 s.directions += "Pour " + to_string(tempB) + " gallon from B to A. " + s.to_string()+ '\n';
            }
            else{
                s.directions += "Pour " + to_string(tempB) + " gallons from B to A. " + s.to_string()+ '\n';
            }
        }
    }

    else if(step == 3){
        //Pour from C to B
        int tempB = s.b;
        s.b += s.c;
        if(s.b > capacities[1]) {
            s.b = capacities[1];
            s.c -= capacities[1] - tempB;
            
            if(capacities[1] - tempB == 1){
                s.directions += "Pour " + to_string(capacities[1] - tempB) + " gallon from C to B. " + s.to_string()+ '\n';
            }
            else{
                s.directions += "Pour " + to_string(capacities[1] - tempB) + " gallons from C to B. " + s.to_string()+ '\n';
            }
        }
        else{
            int tempC = s.c;
            s.c = 0;
            if(tempC == 1){
                s.directions += "Pour " + to_string(tempC) + " gallon from C to B. " + s.to_string()+ '\n';
            }
            else{
                s.directions += "Pour " + to_string(tempC) + " gallons from C to B. " + s.to_string()+ '\n';
            }

        }
    }

    else if(step == 4){
        //Pour from A to B
        int tempB = s.b;
        s.b += s.a;
        if(s.b > capacities[1]) {
            s.b = capacities[1];
            // s.a -= capacities[1];
            s.a -= capacities[1] - tempB;
           
            if(capacities[1] - tempB == 1){
                s.directions += "Pour " + to_string(capacities[1] - tempB) + " gallon from A to B. " + s.to_string()+ '\n';
            }
            else{
                s.directions += "Pour " + to_string(capacities[1] - tempB) + " gallons from A to B. " + s.to_string()+ '\n';
            }
        }
        else{
            int tempA = s.a;
            s.a = 0;

            if(tempA == 1){
                 s.directions += "Pour " + to_string(tempA) + " gallon from A to B. " + s.to_string() + '\n';
            }
            else{
                s.directions += "Pour " + to_string(tempA) + " gallons from A to B. " + s.to_string() + '\n';
            }
        }
    }

    else if(step == 5){
        // Pour from B to C
        int tempC = s.c;
        s.c += s.b;
        if(s.c > capacities[2]) {
            s.c = capacities[2];
            // s.b -= capacities[2];
            s.b -= capacities[2] - tempC;
            if(capacities[2] - tempC == 1){
                s.directions += "Pour " + to_string(capacities[2] - tempC) + " gallon from B to C. " + s.to_string()+ '\n';
            }
            else{
                s.directions += "Pour " + to_string(capacities[2] - tempC) + " gallons from B to C. " + s.to_string()+ '\n';
            }
        }
        else{
            int tempB = s.b;
            s.b = 0;
 
            if(tempB == 1){
                 s.directions += "Pour " + to_string(tempB) + " gallon from B to C. " + s.to_string() + '\n';
            }
            else{
                s.directions += "Pour " + to_string(tempB) + " gallons from B to C. " + s.to_string() + '\n';
            }
        }
    }

    else{
        // step == 6
        // Pour from A to C
        int tempC = s.c;
        s.c += s.a;
        if(s.c > capacities[2]) {
            s.c = capacities[2];
            // s.a -= capacities[2];
            s.a -= capacities[2] - tempC;

            if(capacities[2] - tempC == 1){
                s.directions += "Pour " + to_string(capacities[2] - tempC) + " gallon from A to C. " + s.to_string()+ '\n';
            }
            else{
                s.directions += "Pour " + to_string(capacities[2] - tempC) + " gallons from A to C. " + s.to_string()+ '\n';
            }
        }
        else{
            int tempA = s.a;
            s.a = 0;
            if(tempA == 1){
                s.directions += "Pour " + to_string(tempA) + " gallon from A to C. " + s.to_string() + '\n';
            }
            else{
                s.directions += "Pour " + to_string(tempA) + " gallons from A to C. " + s.to_string() + '\n';
            }
        }
    }
    return s;
}

void waterJug(State &s, int step, const int capacities[], const int goals[]){
    // pouring(s,step,capacities);

    //Use a queue instead to use BFS
    //Use a for loop, inclusive of 1 and 6, in order to test all current edges of a node (BFS)
    //Within the for loop, initiailize a new state tahts a neighbor of the current state, we need to pouring function to update the direction attribute, which is the
    //same as the previous, plus the new set of directions based of the new pouring state
    //
    //We need a base case,
    // if(s.a == goals[0] && s.b == goals[1] && s.c == goals[2]){
    //     return s;
    // }
    // else{
    //     if(step + 1 > 6){
    //         return waterJug(s,1,capacities,goals);
    //     }
    //     //else (step + 1 < 6)
    //     return waterJug(s, step+1, capacities, goals);
    // }
    unordered_map<string, bool> seen; //couldn't store the State as a key
    queue<State> paths;
    bool solvable = false;

    paths.push(s);
    // for (int i = 1; i <= 6; i++){
    //     pouring(s,i,capacities);
    //     paths.push(s);
    // }
    
    unordered_map<string,bool>::iterator it;
    while(!paths.empty()){
        State current = paths.front();
        paths.pop();

        it = seen.find(current.to_string());
        if (it != seen.end()){
            //found
            if (seen[current.to_string()] == true){
                continue;
            }
    
        }
        
        if(current.a == goals[0] && current.b == goals[1] && current.c == goals[2]){
            solvable = true;
            cout << current.directions;
            break;
        }
        
        seen[current.to_string()] = true;
        
        for (int i = 1; i <= 6; i++){
            paths.push(pouring(current,i,capacities));
        }
    }

    
    if (!solvable){
        cout << "No solution.";
    }
    
}
int main(int argc, char * const argv[]){
    int capA, capB, capC, goalA, goalB, goalC;

    istringstream iss;
    ostringstream oss;
    //Error Checking
    if (argc != 7)
    {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
        return 1;
    }

    iss.str(argv[1]);
    oss << argv[1];
    if(!(iss >> capA) || capA <= 0){
        cerr << "Error: Invalid capacity "  << "'" <<  oss.str() << "'" << " for jug A." << endl;
        return 1;
    }
    iss.clear();
    oss.str(""); //this is how you clear the oss

    iss.str(argv[2]);
    oss << argv[2];
    if(!(iss >> capB) || capB <= 0){
        cerr << "Error: Invalid capacity " << "'" << oss.str() << "'"  << " for jug B." << endl;
        return 1;
    }
    iss.clear();
    oss.str("");

    iss.str(argv[3]);
    oss << argv[3];
    if(!(iss >> capC) || capC <= 0){
        cerr << "Error: Invalid capacity '" << oss.str() << "' for jug C." << endl;
        return 1;
    }
    iss.clear();
    oss.str("");

    iss.str(argv[4]);
    oss << argv[4];
    if(!(iss >> goalA) || goalA < 0 ){
        cerr << "Error: Invalid goal '" << oss.str() <<"' for jug A." << endl;
        return 1;
    }
    iss.clear();
    oss.str("");

    iss.str(argv[5]);
    oss << argv[5];
    if(!(iss >> goalB) || goalB < 0){
        cerr << "Error: Invalid goal '" << oss.str() <<"' for jug B." << endl;
        return 1;
    }
    oss.str("");
    iss.clear();

    iss.str(argv[6]);
    oss << argv[6];
    if(!(iss >> goalC) || goalC < 0){
        cerr << "Error: Invalid goal '" << oss.str() <<"' for jug C." << endl;
        return 1;
    }
    oss.str("");
    iss.clear();



    if (goalA > capA){
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }

    if (goalB > capB){
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    
    if (goalC > capC){
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }

    if((goalA + goalB + goalC) != capC){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }


    // if((goalA + goalB + goalC) != (capA + capB + capC)){
    //     //ask Dr. B for this extra test case.
    //     cerr << "Error: Total gallons in goal state must be equal to the capacity" << endl;
    //     return 1;
    // }
    // //All the water starts at C
    // if ( (capA + capB) > capC ){
    //     //ask Dr.B for this extra test case.
    //     cerr << "Error: C cannot have the capacity to hold all the gallons " << endl;
    //     return 1;
    // }

    int capacities [3] = {capA, capB, capC};
    int goals [3] = {goalA, goalB, goalC};
    //Use stringstream to put string in + the integer + string
    string directions = "Initial state. (0, 0, " + to_string(capC) + ")\n";
    State initial(0,0,capC,directions);

    // cout << (waterJug(initial, 1, capacities, goals)).directions;
    waterJug(initial, 1, capacities, goals);
    // cout << sinitial.direction;
    // cout << pouring(initial,1,capacities).to_string() << endl;
    return 0;
}
