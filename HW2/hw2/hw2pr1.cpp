//Elliott Dobbs 823004322
//CSCE 420
//Due: October 30, 2017
//hw2pr1.cpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <climits>
using namespace std;

struct Node{
    int value;
    Node * parent;
    vector<Node> subtrees;
};

//Function to remove whitespace from input
string removeWhite(string input){
    int i = 0;
    while (i < input.size()){
        if (input.substr(i, 1) == " ")
            input.erase(i, 1);
        else
            ++i;
    }
    return input;
}

//Function for creating a tree with a given space-less input tree
void createTree(string input, Node* current){
    
    //if the input is the last close parenthesis, we are at the root node
    //  with nothing left to do so we can exit
    if (input == ")")
        return;
    
    //Get the next character
    string symbol = input.substr(0, 1);
    input.erase(input.begin());

    //Actions based on what character is next
    // If this, create a new subtree and go to it (first location in subtrees)
    if (symbol == "("){
        
        Node howdy;
        howdy.parent = current;
        howdy.value = (int)NULL;
        current->subtrees.push_back(howdy);
        createTree(input, &current->subtrees[0]);
    }
    //If this, create a subtree and go to it (last location in subtrees)
    else if (symbol == ","){
        
        Node howdy;
        howdy.parent = current;
        howdy.value = (int)NULL;
        current->subtrees.push_back(howdy);
        createTree(input, &current->subtrees.back());
    }
    //If this, go back to the parent node
    else if (symbol == ")"){
        
        createTree(input, current->parent);
    }
    //If this, get full number, make the node have that value,
    //  and then go to parent
    else{
        
        //Get the full number
        string test = input.substr(0, 1);
        while (test != "(" &&
               test != "," &&
               test != ")"){
            symbol.push_back(input[0]);
            input.erase(input.begin());
            test = input.substr(0, 1);
        }
        int leaf = stoi(symbol);
        current->value = leaf;
        
        createTree(input, current->parent);
    }
}

//Forward declaration for use in maxValue
void minValue(Node* n);

//Recursive call to get the maximum subtree value for the given node
void maxValue(Node* n){
    
    //If the number is -1, we need to get the value for it by
    //  calling minValue() for each subtree
    if (n->value == (int)NULL){
        
        int max = INT_MIN;
        for (int i = 0; i < n->subtrees.size(); ++i){
            
            minValue(&n->subtrees[i]);
            if (n->subtrees[i].value > max)
                max = n->subtrees[i].value;
        }
        
        n->value = max;
    }
}

//Recursive call to get the minimum subtree value for the given node
void minValue(Node* n){
    
    //If the number is -1, we need to get the value for it by
    //  calling maxValue() for each subtree
    if (n->value == (int)NULL){
        
        int min = INT_MAX;
        for (int i = 0; i < n->subtrees.size(); ++i){
            
            maxValue(&n->subtrees[i]);
            if (n->subtrees[i].value < min)
                min = n->subtrees[i].value;
        }
        
        n->value = min;
    }
}

int main(){
    
    string input;
    cout << "Enter a Tree:";
    cin >> input;
    input = removeWhite(input);
    
    Node root;
    root.parent = NULL;
    root.value = (int)NULL;
    
    createTree(input, &root);
    maxValue(&root);

    cout << endl << endl;
    cout << "The value of the root node is: " << root.value << endl << endl;
    
    return 1;
    
}











