//Elliott Dobbs 823004322
//CSCE 420
//Due: October 30, 2017
//hw2pr3.cpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

//Symbol structure, value not used for this program
struct Symbol{
    string name;
    int value;
};

//Function that returns a list of symbols from a given PROLOG input string
vector<Symbol> getSymbols(string input){
    
    vector<Symbol> result;
    string tempString = "";
    char tempChar;
    int iter = 0, prevIter = 0;
    tempChar = input[iter];
    
    while (tempChar != '.'){
        
        prevIter = iter;
        
        //Iterate to the next invalid Symbol character
        while (tempChar != ':' && tempChar != ',' && tempChar != '.' && tempChar != '-'){
            ++iter;
            tempChar = input[iter];
        }
        
        //If prevIter and iter are the same, that means the next character was
        //  also invalid and we need to loop again going to next character.
        //  If they are not the same, the string inside input between location
        //  prevIter and iter is a symbol name and we can add it to the result vector
        if (prevIter != iter){
            tempString = input.substr(prevIter, iter-prevIter);
            Symbol s;
            s.name = tempString;
            s.value = -1;
            result.push_back(s);
        }
        else{
            ++iter;
            tempChar = input[iter];
        }
    }
    
    return result;
    
}

//Function to get all possible deductions with the given clauses
vector<int> deduceSymbols(vector<Symbol> symbols,
                          vector<Symbol> queue,
                          vector< vector<int> > clauses,
                          vector<int> count){
    
    //Go through each Symbol in the queue, decrementing the symbol count for a clause
    //  if the symbol is found in the clause
    Symbol tempSymbol;
    int tempSymbolLocation;
    vector<int> result;
    
    while (queue.size() > 0){
        tempSymbol = queue[0];
        queue.erase(queue.begin());
        
        //getting the symbol location in the symbol vector
        for (int i = 0; i < symbols.size(); ++i){
            if (symbols[i].name == tempSymbol.name){
                tempSymbolLocation = i;
                break;
            }
        }
        
        //Check each clause for the symbol obtained from the queue
        for (int i = 0; i < clauses.size(); ++i){
            
            if (clauses[i].size() == 1)
                continue;
            else{
                for (int j = 1; j < clauses[i].size(); ++j){
                    if (clauses[i][j] == tempSymbolLocation){
                        --count[i];
                        
                        //If we decrement a clause to 0, we can deduce the first symbol
                        //  in the clause as true, and add it to the queue
                        if (count[i] == 0){
                            queue.push_back(symbols[clauses[i][0]]);
                            
                            bool alreadyDeducted = false;
                            for (int k = 0; k < result.size(); ++k){
                                if (result[k] == clauses[i][0]){
                                    alreadyDeducted = true;
                                    break;
                                }
                            }
                            if (!alreadyDeducted)
                                result.push_back(clauses[i][0]);
                        }
                    }
                }
            }
        }
    }
    
    return result;
}

int main(){
    
    vector<Symbol> symbols;
    vector< vector<int> > clauses; /*Formatted as follows:
                                        -One vector for each clause
                                        -The first element in each clause vector is either
                                            -a given true element if vector size is 1
                                            -a element we can try to prove is true by deduction
                                        -the rest of the elements are symbols we need to be true
                                            in order to prove the first element is true
                                        -Lastly, the elements are integers representing the
                                            location of the symbol in the symbol vector.
                                            (Serving as a kind of pointer)*/
    vector<int> count;
    vector<Symbol> queue;
    
    //Getting input file
    ifstream myfile;
    myfile.open("hw2pr3_data.txt");
    string input;
    vector<Symbol> tempSymbols;
    bool foundFlag;
    
    //Each line of the file processed
    while(myfile >> input){
        
        //Get list of symbols from this input line
        tempSymbols = getSymbols(input);
        foundFlag = false;
        vector<int> tempVec;
        
        //Add the symbols to the symbol vector
        //If there are no symbols, simple add the whole first list of symbols
        //  to the symbols vector
        if (symbols.size() == 0){
            for (int i = 0; i < tempSymbols.size(); ++i){
                symbols.push_back(tempSymbols[i]);
                tempVec.push_back(i);
            }
            
            //Setting clauses vector
            clauses.push_back(tempVec);
        }
        
        //If there are already symbols, check for new symbols to add to the symbol list
        else{
            for (int i = 0; i < tempSymbols.size(); ++i){
                for (int j = 0; j < symbols.size(); ++j){
                    
                    if (tempSymbols[i].name == symbols[j].name){
                        foundFlag = true;
                        tempVec.push_back(j);
                    }
                }
                if (!foundFlag){
                    symbols.push_back(tempSymbols[i]);
                    tempVec.push_back(symbols.size() - 1);
                }
                else
                    foundFlag = false;
            }
            
            //Setting clauses vector
            clauses.push_back(tempVec);
        }
        
        //Add the symbol to queue if its the only one is the clause
        if (tempSymbols.size() == 1)
            queue.push_back(tempSymbols[0]);
        
        //Add the number of symbols in right side of clause to the count vector
        count.push_back(tempSymbols.size() - 1);
        
    }
    myfile.close();
    
    //Call the deduce function to deduce all symbols we can
    vector<int> deductedTrueSymbols = deduceSymbols(symbols, queue, clauses, count);
    
    //Print the output
    cout << endl;
    cout << "Deducted Symbols:" << endl << ": ";
    for (int i = 0; i < deductedTrueSymbols.size(); ++i){
        cout << symbols[deductedTrueSymbols[i]].name << " : ";
    }
    cout << endl << endl;
    
    return 1;
}











