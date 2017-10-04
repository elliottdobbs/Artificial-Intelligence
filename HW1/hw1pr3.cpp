//Elliott Dobbs 823004322
//CSCE 420
//Due: October 4, 2017
//hw1pr3.cpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

//Move functions for a given puzzle state, and a blank location
vector<int> moveUp(vector<int> vec, int blank){
    vec[blank] = vec[blank - 4];
    vec[blank - 4] = 0;
    return vec;
}

vector<int> moveRight(vector<int> vec, int blank){
    vec[blank] = vec[blank + 1];
    vec[blank + 1] = 0;
    return vec;
}

vector<int> moveDown(vector<int> vec, int blank){
    vec[blank] = vec[blank + 4];
    vec[blank + 4] = 0;
    return vec;
}

vector<int> moveLeft(vector<int> vec, int blank){
    vec[blank] = vec[blank - 1];
    vec[blank - 1] = 0;
    return vec;
}

//Base 5 to base 10 conversion
int b5tob10(vector<int> vec){
    
    int total = 0;
    
    for (int i = 0; i < vec.size(); i++)
        total += vec[i] * pow(5, (vec.size() - 1 - i));
    
    return total;
}

//Base 10 to base 5 conversion
vector<int> b10tob5(int num){
    
    int i = 0;
    vector<int> result;
    double howdy;
    
    if (num < 1){
        cerr << "ERROR in base10 to base 5" << endl;
        return result;
    }

    while (num >= pow(5, i)){
        result.insert(result.begin(), int((num / (pow(5, i)))) % 5);
        ++i;
    }
    
    return result;
}

//Finding the iteration location of the blank
int blankSpot(vector<int> state){
    
    int result = 0;
    while (state[result] != 0){
        ++result;
        if (result == 16){
            cout << "Error: No Blank found" << endl;
            return -1;
        }
    }
    return result;
}

//Checks if a given vector contains any 0s
bool checkZeros(vector<int> vec){
    
    for (int i = 0; i < vec.size(); i++){
        if (vec[i] == 0)
            return true;
    }
    
    return false;
}

/*This algorithm takes in the input state, ending state, and an integer sol.
     -the sol integer is a normal base 10 number that represents a sequence of moves
     -This number is converted to base 5 and stored by digit in a vector
     -each digit (1, 2, 3, 4) represents up, right, down, and left respectivly
     -the sol integer is checked in the main function to make sure there are no 0s
         in the base 5 version of the number since 0 does not represent any move
 */
vector<int> BFS(vector<int> inState, vector<int> endState, int sol){

    vector<int> tempState = inState;
    vector<int> check = b10tob5(sol);
    int blank = blankSpot(tempState);
    vector<int> result;
    
    //Get the game state according to the sequence of moves
    // represented by integer sol
    for (int i = 0; i < check.size(); i++){
        
        //Up
        if (check[i] == 1){
            
            //Make sure the blank is not at the top of the puzzle
            if (blank >= 4){
                tempState = moveUp(tempState, blank);
                blank = blankSpot(tempState);
            }
            else{
                blank = -1;
                break;
            }
        }
        
        //Right
        else if (check[i] == 2){
            
            //Make sure the blank is not at the right side of the puzzle
            if (blank % 4 != 3){
                tempState = moveRight(tempState, blank);
                blank = blankSpot(tempState);
            }
            else{
                blank = -1;
                break;
            }
        }
        
        //Down
        else if (check[i] == 3){
            
            //Make sure the blank is not at the bottom of the puzzle
            if (blank <= 11){
                tempState = moveDown(tempState, blank);
                blank = blankSpot(tempState);
            }
            else{
                blank = -1;
                break;
            }
        }
        
        //Left
        else if (check[i] == 4){
            
            //Make sure the blank is not at the left side of the puzzle
            if (blank % 4 != 0){
                tempState = moveLeft(tempState, blank);
                blank = blankSpot(tempState);
            }
            else{
                blank = -1;
                break;
            }
        }
    }
    
    //Checking if the derived state is the end state, and if the move is valid
    // valid: it does not move the blank off the puzzle
    if (tempState == endState && blank != -1){
        
        //If we are at the end, return sol in location 0,
        // and '1' in location 1 to represent that the
        // number in location 0 represents the solution move sequence
        result.push_back(sol);
        result.push_back(1);
        return result;
    }
    else{
        
        //If we are NOT at the end, return sol in location 0,
        // and 0 in location 1 to represent that the
        // number in location 0 is not the solution to the puzzle
        result.push_back(sol);
        result.push_back(0);
        return result;
    }
}

int main(){
    
    //Getting the input state
    string input;
    vector<int> inputState, endingState;
    cout << "Enter 15-puzzle starting state by rows, separated by commas (0 for blank):" << endl;
    cin >> input;
    stringstream in(input);

    int i;
    while (in >> i){
        inputState.push_back(i);
        if (in.peek() == ',')
            in.ignore();
    }
    if(inputState.size() != 16){
        cout << "Invalid state entered.  Exiting" << endl;
        return 0;
    }

    //Getting the ending state
    cout << "Enter ending state by rows, separated by commas (0 for blank):" << endl;
    cin >> input;
    stringstream end(input);

    while (end >> i){
        endingState.push_back(i);
        if (end.peek() == ',')
            end.ignore();
    }
    if(endingState.size() != 16){
        cout << "Invalid state entered.  Exiting" << endl;
        return 0;
    }

    if (inputState == endingState){
        cout << "Input and ending state are the same. exiting" << endl;
        return 1;
    }
    
    //Findin the solution
    int sol = 1, numberOfStates = 1;
    vector<int> solution = BFS(inputState, endingState, sol);
    vector<int> check;

    //BFS maps the given integer 'sol' to a sqeuence of moves
    // by changing the number to base 5, and checking for 0s in
    // the digits
    while (solution[1] != 1){
        
        ++sol;
        check = b10tob5(sol);
        
        //This checks the next sequence of moves for 0s,
        // if there are 0s in the base 5 number, we have to try the next number
        // since 0 doesn't represent any valid move for this implementation
        while(checkZeros(check)){
            ++sol;
            check = b10tob5(sol);
        }
        
        ++numberOfStates;
        solution = BFS(inputState, endingState, sol);
    }
    
    //Display the start state
    cout << "\nStart:\n";
    cout << "\t" << setw(3) << inputState[0] << setw(3) << inputState[1] << setw(3) << inputState[2] << setw(3) << inputState[3] << endl;
    cout << "\t" << setw(3) << inputState[4] << setw(3) << inputState[5] << setw(3) << inputState[6] << setw(3) << inputState[7] << endl;
    cout << "\t" << setw(3) << inputState[8] << setw(3) << inputState[9] << setw(3) << inputState[10] << setw(3) << inputState[11] << endl;
    cout << "\t" << setw(3) << inputState[12] << setw(3) << inputState[13] << setw(3) << inputState[14] << setw(3) << inputState[15] << endl << endl;
    cout << "--------------------\n";
    cout << "To solve, swipe the blank:\n";
    
    //Print out the solution sequence of moves by applying the moves
    // to the input state
    vector<int> solVec = b10tob5(solution[0]);
    int blank = blankSpot(inputState);
    for (int i = 0; i < solVec.size(); i++){
        if (solVec[i] == 1){
            cout << "\nUp:\n";
            inputState = moveUp(inputState, blank);
            cout << "\t" << setw(3) << inputState[0] << setw(3) << inputState[1] << setw(3) << inputState[2] << setw(3) << inputState[3] << endl;
            cout << "\t" << setw(3) << inputState[4] << setw(3) << inputState[5] << setw(3) << inputState[6] << setw(3) << inputState[7] << endl;
            cout << "\t" << setw(3) << inputState[8] << setw(3) << inputState[9] << setw(3) << inputState[10] << setw(3) << inputState[11] << endl;
            cout << "\t" << setw(3) << inputState[12] << setw(3) << inputState[13] << setw(3) << inputState[14] << setw(3) << inputState[15] << endl;
        }
        else if (solVec[i] == 2){
            cout << "\nRight:\n";
            inputState = moveRight(inputState, blank);
            cout << "\t" << setw(3) << inputState[0] << setw(3) << inputState[1] << setw(3) << inputState[2] << setw(3) << inputState[3] << endl;
            cout << "\t" << setw(3) << inputState[4] << setw(3) << inputState[5] << setw(3) << inputState[6] << setw(3) << inputState[7] << endl;
            cout << "\t" << setw(3) << inputState[8] << setw(3) << inputState[9] << setw(3) << inputState[10] << setw(3) << inputState[11] << endl;
            cout << "\t" << setw(3) << inputState[12] << setw(3) << inputState[13] << setw(3) << inputState[14] << setw(3) << inputState[15] << endl;
        }
        else if (solVec[i] == 3){
            cout << "\nDown:\n";
            inputState = moveDown(inputState, blank);
            cout << "\t" << setw(3) << inputState[0] << setw(3) << inputState[1] << setw(3) << inputState[2] << setw(3) << inputState[3] << endl;
            cout << "\t" << setw(3) << inputState[4] << setw(3) << inputState[5] << setw(3) << inputState[6] << setw(3) << inputState[7] << endl;
            cout << "\t" << setw(3) << inputState[8] << setw(3) << inputState[9] << setw(3) << inputState[10] << setw(3) << inputState[11] << endl;
            cout << "\t" << setw(3) << inputState[12] << setw(3) << inputState[13] << setw(3) << inputState[14] << setw(3) << inputState[15] << endl;
        }
        else if (solVec[i] == 4){
            cout << "\nLeft:\n";
            inputState = moveLeft(inputState, blank);
            cout << "\t" << setw(3) << inputState[0] << setw(3) << inputState[1] << setw(3) << inputState[2] << setw(3) << inputState[3] << endl;
            cout << "\t" << setw(3) << inputState[4] << setw(3) << inputState[5] << setw(3) << inputState[6] << setw(3) << inputState[7] << endl;
            cout << "\t" << setw(3) << inputState[8] << setw(3) << inputState[9] << setw(3) << inputState[10] << setw(3) << inputState[11] << endl;
            cout << "\t" << setw(3) << inputState[12] << setw(3) << inputState[13] << setw(3) << inputState[14] << setw(3) << inputState[15] << endl;
        }
        blank = blankSpot(inputState);
    }
    cout << '\n' << "Generated " << numberOfStates << " states." << endl << endl;
    
    return 1;
}











