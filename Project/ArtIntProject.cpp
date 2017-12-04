//Elliott Dobbs
//CSCE 420
//29 Nov. 2017
//ArtIntProject.cpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <bitset>
#include <math.h>
using namespace std;

vector<double> sigmoid;
vector<double> hyperbolicTan;
double alpha = 0.05;

struct Link{
    int sendingLink;
    int recievingLink;
    double weight;
};

struct Node{
    vector<Link> inputLinks;
    vector<Link> outputLinks;
    int someVaribaleForFunctionSelection;
    double outputActivation;
    double delta;
};

struct NeuroNetwork{
    vector< vector<Node> > layers;
};

void generateSigmoid(){
    double x, sig;
    
    for (int i = 0; i < 10000; ++i){
        x = -5.0 + ((double)i/1000.0);
        sig = 1.0/(1.0+exp(-x));
        sigmoid.push_back(sig);
    }
}

void generateHyperbolicTangent(){
    double x, hyp;
    
    for (int i = 0; i < 10000; ++i){
        x = -5.0 + ((double)i/1000.0);
        hyp = (exp(x) - exp(-x))/(exp(x) + exp(-x));
        hyperbolicTan.push_back(hyp);
    }
}

NeuroNetwork createNetwork(){
    
    NeuroNetwork net;
    Node n;
    n.outputActivation = 0.0;
    n.delta = 0.0;
    int inputLayerNodes = 240;
    int outputLayerNodes = 29;
    vector<int> hiddenLayerNodes;
    hiddenLayerNodes.push_back(120);
    hiddenLayerNodes.push_back(60);
    
    vector<Node> tempLayer;
    
    //creating the input layer
    for (int i = 0; i < inputLayerNodes; ++i){
        tempLayer.push_back(n);
    }
    net.layers.push_back(tempLayer);
    tempLayer.clear();
    
    //creating the hidden layers
    for(int j = 0; j < hiddenLayerNodes.size(); ++j){
        for (int i = 0; i < hiddenLayerNodes[j]; ++i){
            tempLayer.push_back(n);
        }
        net.layers.push_back(tempLayer);
        tempLayer.clear();
    }
    
    //creating the output layer
    for (int i = 0; i < outputLayerNodes; ++i){
        tempLayer.push_back(n);
    }
    net.layers.push_back(tempLayer);
    tempLayer.clear();
    
    /////////Creating the links vectors for each node
    Link tempLink;
    tempLink.weight = 0.0;
    vector<Link> tempLinkVector;
    
    //making the outputLinks vector for the input layer
    for (int i = 0; i < net.layers[1].size(); ++i){
        tempLink.recievingLink = i;
        tempLinkVector.push_back(tempLink);
    }
    //setting outputLinks vector
    for (int i = 0; i < inputLayerNodes; ++i){
        for (int j = 0; j < tempLinkVector.size(); ++j){
            tempLinkVector[j].sendingLink = i;
        }
        net.layers[0][i].outputLinks = tempLinkVector;
    }
    
    //making the Links vectors for the hidden layers
    for (int layer = 1; layer < net.layers.size() - 1; ++layer){
        
        tempLinkVector.clear();
        
        //creating the inputLinks vector
        for (int i = 0; i < net.layers[layer-1].size(); ++i){
            tempLink.sendingLink = i;
            tempLinkVector.push_back(tempLink);
        }
        //setting the inputLinks
        for (int i = 0; i < net.layers[layer].size(); ++i){
            for (int j = 0; j < tempLinkVector.size(); ++j){
                tempLinkVector[j].recievingLink = i;
            }
            net.layers[layer][i].inputLinks = tempLinkVector;
        }
        tempLinkVector.clear();
        
        //creating the outputLinks vector
        for (int i = 0; i < net.layers[layer + 1].size(); ++i){
            tempLink.recievingLink = i;
            tempLinkVector.push_back(tempLink);
        }
        //setting outputLinks vector
        for (int i = 0; i < net.layers[layer].size(); ++i){
            for (int j = 0; j < tempLinkVector.size(); ++j){
                tempLinkVector[j].sendingLink = i;
            }
            net.layers[layer][i].outputLinks = tempLinkVector;
        }
    }
    
    //creating inputLinks for outputLayer
    tempLinkVector.clear();
    
    //creating the inputLinks vector
    for (int i = 0; i < net.layers[net.layers.size() - 2].size(); ++i){
        tempLink.sendingLink = i;
        tempLinkVector.push_back(tempLink);
    }
    //setting the inputLinks
    for (int i = 0; i < net.layers[net.layers.size() - 1].size(); ++i){
        for (int j = 0; j < tempLinkVector.size(); ++j){
            tempLinkVector[j].recievingLink = i;
        }
        net.layers[net.layers.size() - 1][i].inputLinks = tempLinkVector;
    }
    
    return net;
}

vector<double> getInputVector(uint64_t input){
    
    vector<double> result;
    bitset<64> x(input);
    string howdy = x.to_string();
    int missingNumber[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    for (int i = 1; i < 16; ++i){
        
        string test = howdy.substr(i*4, 4);
        
        if(test == "0000"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            
            missingNumber[0] = 1;
        }
        else if(test == "0001"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            
            missingNumber[1] = 1;
        }
        else if(test == "0010"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[2] = 1;
        }
        else if(test == "0011"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[3] = 1;
        }
        else if(test == "0100"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[4] = 1;
        }
        else if(test == "0101"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[5] = 1;
        }
        else if(test == "0110"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[6] = 1;
        }
        else if(test == "0111"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[7] = 1;
        }
        else if(test == "1000"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[8] = 1;
        }
        else if(test == "1001"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[9] = 1;
        }
        else if(test == "1010"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[10] = 1;
        }
        else if(test == "1011"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[11] = 1;
        }
        else if(test == "1100"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[12] = 1;
        }
        else if(test == "1101"){
            result.push_back(0);
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[13] = 1;
        }
        else if(test == "1110"){
            result.push_back(0);
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[14] = 1;
        }
        else if(test == "1111"){
            result.push_back(1);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            result.push_back(0);
            
            missingNumber[15] = 1;
        }
        
    }
    
    return result;
}

vector<double> getOutputVector(int input){
    
    vector<double> result;
    
    for (int i = 0; i < 29; ++i){
        if (input == i)
            result.push_back(1.0);
        else
            result.push_back(0.0);
    }
    
    return result;
}

NeuroNetwork makeWeights(NeuroNetwork net){
    
    double random;
    
    for (int layer = 0; layer < net.layers.size(); ++layer){
        
        //set output weights
        if (layer != net.layers.size() - 1){
            for (int node = 0; node < net.layers[layer].size(); ++node){
                for (int nodeLink = 0;
                     nodeLink < net.layers[layer][node].outputLinks.size();
                     ++nodeLink){
                    
                    random = (double)(rand() % 2000 - 1000)/1000;
                    net.layers[layer][node].outputLinks[nodeLink].weight = random;
                }
            }
        }
        
        //set input weights based on the output link from the previous layer
        if (layer != 0){
            for (int node = 0; node < net.layers[layer].size(); ++node){
                for (int nodeLink = 0;
                     nodeLink < net.layers[layer][node].inputLinks.size();
                     ++nodeLink){
                    
                    net.layers[layer][node].inputLinks[nodeLink].weight = net.layers[layer - 1][net.layers[layer][node].inputLinks[nodeLink].sendingLink].outputLinks[node].weight;
                }
            }
        }
    }
    
    return net;
}

NeuroNetwork backPropLearning(vector< vector<double> > inputActivations,
                              vector< vector<double> > outputActivations,
                              NeuroNetwork network){
    
    network = makeWeights(network);
    
    //for each example...
    for (int example = 0; example < inputActivations.size(); ++example){
        
        //Set input activations
        for (int inputLayerNode = 0;
             inputLayerNode < network.layers[0].size();
             ++inputLayerNode){
            
            network.layers[0][inputLayerNode].outputActivation = inputActivations[example][inputLayerNode];
        }
        //Propigate input forward to output
        for (int layer = 1; layer < network.layers.size(); ++layer){
            for (int node = 0; node < network.layers[layer].size(); ++node){
                
                //Get weighted sum
                double weightedSum = 0.0;
                for (int inputLink = 0;
                     inputLink < network.layers[layer][node].inputLinks.size();
                     ++inputLink){
                    
                    weightedSum +=  network.layers[layer][node].inputLinks[inputLink].weight *
                    network.layers[layer - 1][network.layers[layer][node].inputLinks[inputLink].sendingLink].outputActivation;
                }
                
                //Putting weighted sum into Sigmoid function
                int sum = (int)((weightedSum + 5) * 1000);
                if (layer == network.layers.size() - 1){
                    if (sum < 0)
                        network.layers[layer][node].outputActivation = 0.0;
                    else if (sum >= 10000)
                        network.layers[layer][node].outputActivation = sigmoid[9999];
                    else
                        network.layers[layer][node].outputActivation = sigmoid[sum];
                }
                else{
                    if (sum < 0)
                        network.layers[layer][node].outputActivation = -1;
                    else if (sum >= 10000)
                        network.layers[layer][node].outputActivation = hyperbolicTan[9999];
                    else
                        network.layers[layer][node].outputActivation = hyperbolicTan[sum];
                }
                
            }
        }
        
        //Propigate deltas backwards
        for (int node = 0;
             node < network.layers[network.layers.size() - 1].size();
             ++node){
            
            double y_error = outputActivations[example][node] - network.layers[network.layers.size() - 1][node].outputActivation;
            if (y_error > 0)
                y_error *= 2;
            
            network.layers[network.layers.size() - 1][node].delta = (network.layers[network.layers.size() - 1][node].outputActivation) * (1 - network.layers[network.layers.size() - 1][node].outputActivation) * y_error;
        }
        double summedWeightedJs;
        for (int layer = (network.layers.size() - 2); layer >= 0; --layer){
            for (int node = 0; node < network.layers[layer].size(); ++node){
                
                summedWeightedJs = 0.0;
                for (int deltaJs = 0; deltaJs < network.layers[layer + 1].size(); ++ deltaJs){
                    summedWeightedJs += network.layers[layer][node].outputLinks[deltaJs].weight * network.layers[layer + 1][deltaJs].delta;
                }
                
                network.layers[layer][node].delta = (1 - (network.layers[layer][node].outputActivation * network.layers[layer][node].outputActivation)) * summedWeightedJs;
            }
        }
        
        //Update weights
        for (int layer = 0; layer < network.layers.size(); ++layer){
            
            //Update output weights
            if (layer != network.layers.size() - 1){
                for (int node = 0; node < network.layers[layer].size(); ++node){
                    for (int nodeLink = 0;
                         nodeLink < network.layers[layer][node].outputLinks.size();
                         ++nodeLink){
                        
                        network.layers[layer][node].outputLinks[nodeLink].weight += alpha * network.layers[layer][node].outputActivation * network.layers[layer + 1][network.layers[layer][node].outputLinks[nodeLink].recievingLink].delta;
                    }
                }
            }
            
            //set input weights based on the output link from the previous layer
            if (layer != 0){
                for (int node = 0; node < network.layers[layer].size(); ++node){
                    for (int nodeLink = 0;
                         nodeLink < network.layers[layer][node].inputLinks.size();
                         ++nodeLink){
                        
                        network.layers[layer][node].inputLinks[nodeLink].weight = network.layers[layer - 1][network.layers[layer][node].inputLinks[nodeLink].sendingLink].outputLinks[node].weight;
                    }
                }
            }
        }
    }
    
    return network;
}

NeuroNetwork progigate(vector<double> inputActivations, NeuroNetwork network){
    
    //Set input activations
    for (int inputLayerNode = 0;
         inputLayerNode < network.layers[0].size();
         ++inputLayerNode){
        
        network.layers[0][inputLayerNode].outputActivation = inputActivations[inputLayerNode];
    }
    //Propigate input forward to output
    for (int layer = 1; layer < network.layers.size(); ++layer){
        for (int node = 0; node < network.layers[layer].size(); ++node){
            
            //Get weighted sum
            double weightedSum = 0.0;
            for (int inputLink = 0;
                 inputLink < network.layers[layer][node].inputLinks.size();
                 ++inputLink){
                
                weightedSum +=  network.layers[layer][node].inputLinks[inputLink].weight *
                network.layers[layer - 1][network.layers[layer][node].inputLinks[inputLink].sendingLink].outputActivation;
            }
            
            //Putting weighted sum into Sigmoid function
            int sum = (int)((weightedSum + 5) * 1000);
            if (layer == network.layers.size() - 1){
                if (sum < 0)
                    network.layers[layer][node].outputActivation = 0.0;
                else if (sum >= 10000)
                    network.layers[layer][node].outputActivation = sigmoid[9999];
                else
                    network.layers[layer][node].outputActivation = sigmoid[sum];
            }
            else{
                if (sum < 0)
                    network.layers[layer][node].outputActivation = -1;
                else if (sum >= 10000)
                    network.layers[layer][node].outputActivation = hyperbolicTan[9999];
                else
                    network.layers[layer][node].outputActivation = hyperbolicTan[sum];
            }
            
        }
    }
    
    return network;
}

int main(){
    
    //Getting input file
    ifstream myfile[29];
    uint64_t howdy;
    vector< vector<double> > exampleInputActivations;
    vector< vector<double> > exampleOutputActivations;
    int randomChance, randomState;
    
    int testNumber, maxTestStateNumber, learningCycles;
    cout << "Enter an amount of test files to get: ";
    cin >> testNumber;
    cout << "Enter the max state number to train on: ";
    cin >> maxTestStateNumber;
    
    for (int i = 0; i < 29; ++i){
        string fileName = "/pub/faculty_share/daugher/datafiles/data/" + to_string(i) + "states.bin";
        //string fileName = "Data/" + to_string(i) + "states.bin";
        cout << fileName << endl;
        myfile[i].open(fileName, ios::binary);
    }
    
    cout << "Getting input data..." << endl;
    int inputStateIter = 0;
    for (int i = 1; i < testNumber; ++i){
        
        bool found = false;
        while (found == false){
            
            while (myfile[inputStateIter].read(reinterpret_cast<char *>(&howdy), sizeof(howdy))){
                
                randomChance = rand() % 100;
                
                if (randomChance == 1 || inputStateIter == 0){
                    //Parsing input
                    vector<double> inputActivation = getInputVector(howdy);
                    exampleInputActivations.push_back(inputActivation);
                    
                    //Getting output activations
                    vector<double> outputActivation = getOutputVector(inputStateIter);
                    exampleOutputActivations.push_back(outputActivation);
                    
                    found = true;
                    break;
                }
            }
            
            myfile[inputStateIter].clear();
            myfile[inputStateIter].seekg(0, myfile[inputStateIter].beg);
        }
        
        ++inputStateIter;
        if (inputStateIter > maxTestStateNumber)
            inputStateIter = 0;
    }
    
    for (int i = 0; i < 29; ++i){
        myfile[i].close();
    }
    
    cout << "Input Obtained" << endl;
    
    //generate the sigmoid table
    generateSigmoid();
    cout << "Generated Sigmoid Values..." << endl;
    
    //generate the hyperbolic tangent table
    generateHyperbolicTangent();
    cout << "Generated Hyperbolic Tangent Values..." << endl;
    
    //Creating the base network
    NeuroNetwork network = createNetwork();
    cout << "Created Neural Network..." << endl;
    
    //Performing the back-Propigation
    cout << "Training network..." << endl;
    NeuroNetwork resultingNetwork = backPropLearning(exampleInputActivations,
                                                     exampleOutputActivations,
                                                     network);
    cout << "Neural Network Trained..." << endl << endl;
    
    //User choosing input states
    int continueInput = 1, stateChosen;
    vector<double> userInputActivation;
    while (continueInput == 1) {
        cout << "Input an integer (0-28) for which state pool you want\nto choose from: ";
        cin >> stateChosen;
        
        while (userInputActivation.size() == 0){
            
            string fileName = "/pub/faculty_share/daugher/datafiles/data/" + to_string(stateChosen) + "states.bin";
            //string fileName = "Data/" + to_string(stateChosen) + "states.bin";
            myfile[0].open(fileName, ios::binary);
            
            while (myfile[0].read(reinterpret_cast<char *>(&howdy), sizeof(howdy))){
                
                randomChance = rand() % 1000^(stateChosen+1);
                
                if (randomChance == 1){
                    //Parsing input
                    userInputActivation = getInputVector(howdy);
                    
                    break;
                }
            }
            myfile[0].close();
        }
        
        resultingNetwork = progigate(userInputActivation, resultingNetwork);
        
        cout << endl << endl << "Here are your results!" << endl;
        double max = -10.0;
        int maxIter;
        for (int i = 0; i < 29; ++i){
            if (resultingNetwork.layers[resultingNetwork.layers.size() - 1][i].outputActivation > max){
                max = resultingNetwork.layers[resultingNetwork.layers.size() - 1][i].outputActivation;
                maxIter = i;
            }
            cout << i << " : " << resultingNetwork.layers[resultingNetwork.layers.size() - 1][i].outputActivation << endl;
        }
        cout << endl << "Max number was : " << max << "\nAt: " << maxIter << endl;
        cout << endl << endl;
        cout << "continue? (1/0) : ";
        cin >> continueInput;
        userInputActivation.clear();
    }
    
    return 1;
}













