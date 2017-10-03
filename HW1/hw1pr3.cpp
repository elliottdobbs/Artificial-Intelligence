//Elliott Dobbs 823004322
//CSCE 420
//Due: October 2, 2017
//hw1pr3.cpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <unistd.h>
using namespace std;

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
    
    cout << 'A' << endl << num << endl;
    
    cout << 'B' << endl;
    int i = 0;
    vector<int> result;
    double howdy;
    
    if (num < 1){
        cerr << "ERROR in base10 to base 5" << endl;
        return result;
    }
    cout << 'B' << endl;

    while (num >= pow(5, i)){
        result.insert(result.begin(), int((num / (pow(5, i)))) % 5);
        ++i;
    }
    
    return result;
}

//Finding the iteration of the blank
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

int BFS(vector<int> inState, vector<int> endState, int sol){
    cout << "\n1 *";
    vector<int> tempState = inState;
    cout << "\n2 * " << sol << endl;
    vector<int> check = b10tob5(sol);
    cout << "\n3 *";
    int blank = blankSpot(tempState);
    cout << "\n4 *";
    
    cout << "\n\nsol: " << sol << endl;
    for (int i = 0; i < check.size(); ++i){
        cout << check[i] << " : ";
    }
    
    //Get the current game state
    for (int i = 0; i < check.size(); i++){
        
        if (check[i] == 1){
            if (blank >= 4){
                tempState = moveUp(tempState, blank);
                blank = blankSpot(tempState);
            }
            else{
                blank = -1;
                break;
            }
        }
        else if (check[i] == 2){
            if (blank % 4 != 3){
                tempState = moveRight(tempState, blank);
                blank = blankSpot(tempState);
            }
            else{
                blank = -1;
                break;
            }
        }
        else if (check[i] == 3){
            if (blank <= 11){
                tempState = moveDown(tempState, blank);
                blank = blankSpot(tempState);
            }
            else{
                blank = -1;
                break;
            }
        }
        else if (check[i] == 4){
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
    
    //Checking if input is the end state (base case)
    if (tempState == endState && blank != -1)
        return b5tob10(check);
    
    //if not, iterate to next valid solution sequence (a sequence with no 0s)
    ++sol;
    check = b10tob5(sol);
    while(checkZeros(check)){
            ++sol;
            check = b10tob5(sol);
    }
    
    //Once we have the next sequence of moves in the BFS,
    // return the next one checked
    return BFS(inState, endState, sol);
}

int main(){
    
    //Getting the input state
    string input;
    vector<int> inputState, endingState;
//    cout << "Enter 15-puzzle starting state by rows, separated by commas (0 for blank):" << endl;
//    cin >> input;
//    stringstream in(input);
//
//    int i;
//    while (in >> i){
//        inputState.push_back(i);
//        if (in.peek() == ',')
//            in.ignore();
//    }
//    if(inputState.size() != 16){
//        cout << "Invalid state entered.  Exiting" << endl;
//        return 0;
//    }
//
//    //Getting the ending state
//    cout << "Enter ending state by rows, separated by commas (0 for blank):" << endl;
//    cin >> input;
//    stringstream end(input);
//
//    while (end >> i){
//        endingState.push_back(i);
//        if (end.peek() == ',')
//            end.ignore();
//    }
//    if(endingState.size() != 16){
//        cout << "Invalid state entered.  Exiting" << endl;
//        return 0;
//    }
//
//    if (inputState == endingState){
//        cout << "Input and ending state are the same. exiting" << endl;
//        return 1;
//    }
    inputState.push_back(1);inputState.push_back(2);inputState.push_back(3);inputState.push_back(4);
    inputState.push_back(0);inputState.push_back(6);inputState.push_back(11);inputState.push_back(7);
    inputState.push_back(5);inputState.push_back(9);inputState.push_back(10);inputState.push_back(8);
    inputState.push_back(13);inputState.push_back(14);inputState.push_back(15);inputState.push_back(12);
   
    endingState.push_back(1);endingState.push_back(2);endingState.push_back(3);endingState.push_back(4);
    endingState.push_back(5);endingState.push_back(6);endingState.push_back(7);endingState.push_back(8);
    endingState.push_back(9);endingState.push_back(10);endingState.push_back(11);endingState.push_back(12);
    endingState.push_back(13);endingState.push_back(14);endingState.push_back(15);endingState.push_back(0);
    
    int solution = 1;
    solution = BFS(inputState, endingState, solution);
    
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
    vector<int> solVec = b10tob5(solution);
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
    cout << '\n';
    
    return 1;
}











