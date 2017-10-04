//Elliott Dobbs 823004322
//CSCE 420
//Due: October 2, 2017
//hw1pr2.cpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <float.h>
#include <vector>
#include <algorithm>
using namespace std;

//Distances matrix
vector<vector<vector <double> > > distances;
vector<vector<vector <double> > > sortedDistances;
double greedyPathTotal;
double partialTotal;
double minTotalFound;

struct Point{
    int x;
    int y;
    bool checked;
};

//Point vector
vector<Point> points;

////////////////////////////Greedy path function

//Algorithm to find the iteration location of the
// closest unckecked point in the point array
int closestPoint(vector<Point> p, int iter){
    
    int result = -1;
    
    for (int i = 1; i < sortedDistances[iter].size(); ++i){
        if (p[sortedDistances[iter][i][1]].checked){
            continue;
        }
        else
            return sortedDistances[iter][i][1];
    }
    
    return result;
}
////////////////////////////

double pointDist(Point p1, Point p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y));
}

vector<int> fourClosestPoints(vector<Point> p, int iter){
    
    vector<int> result;
    int counter = 0;

    //Start at one since the 0 location contains the distance to itself (0)
    for (int i = 1; i < sortedDistances[iter].size(); ++i){

        if (p[sortedDistances[iter][i][1]].checked)
            continue;

        else{
            result.push_back(sortedDistances[iter][i][1]);

            if(result.size() == 4)
                break;
        }
    }

    return result;
}

//Redo this. check iterative deepening
double findBestPath(int pointIter, vector<Point> p){
    
    vector<int> closestPoints = fourClosestPoints(p, pointIter);
    double dist1 = DBL_MAX, dist2 = DBL_MAX, dist3 = DBL_MAX, dist4 = DBL_MAX;
    
    //base case: only 1 point left to check
    if (closestPoints.size() == 1){
        
        if ((partialTotal + distances[pointIter][closestPoints[0]][0] +
        distances[closestPoints[0]][0][0]) < minTotalFound)
            minTotalFound = partialTotal + distances[pointIter][closestPoints[0]][0] + distances[closestPoints[0]][0][0];
        
        return distances[pointIter][closestPoints[0]][0] +
               distances[closestPoints[0]][0][0];
    }
    
    //First point
    p[closestPoints[0]].checked = true;
    partialTotal += distances[pointIter][closestPoints[0]][0];
    
    //checking the partial total before going on
    if (partialTotal > greedyPathTotal){
        partialTotal -= distances[pointIter][closestPoints[0]][0];
    }
    else{
        dist1 = distances[pointIter][closestPoints[0]][0] +
                   findBestPath(closestPoints[0], p);
        partialTotal -= distances[pointIter][closestPoints[0]][0];
    }
    p[closestPoints[0]].checked = false;
    
    //Second point
    p[closestPoints[1]].checked = true;
    partialTotal += distances[pointIter][closestPoints[1]][0];
    
    if (partialTotal > greedyPathTotal){
        partialTotal -= distances[pointIter][closestPoints[1]][0];
    }
    else{
        dist2 = distances[pointIter][closestPoints[1]][0] +
        findBestPath(closestPoints[1], p);
        partialTotal -= distances[pointIter][closestPoints[1]][0];
    }
    p[closestPoints[1]].checked = false;
    
    //if there is a 3rd point
    if (closestPoints.size() >= 3){
        p[closestPoints[2]].checked = true;
        partialTotal += distances[pointIter][closestPoints[2]][0];
        
        if (partialTotal > greedyPathTotal){
            partialTotal -= distances[pointIter][closestPoints[2]][0];
        }
        else{
            dist3 = distances[pointIter][closestPoints[2]][0] +
            findBestPath(closestPoints[1], p);
            partialTotal -= distances[pointIter][closestPoints[2]][0];
        }
        p[closestPoints[2]].checked = false;
    }
    
    //if their is a fourth point
    if (closestPoints.size() >= 4){
        p[closestPoints[3]].checked = true;
        partialTotal += distances[pointIter][closestPoints[3]][0];
        
        if (partialTotal > greedyPathTotal){
            partialTotal -= distances[pointIter][closestPoints[3]][0];
        }
        else{
            dist4 = distances[pointIter][closestPoints[3]][0] +
            findBestPath(closestPoints[1], p);
            partialTotal -= distances[pointIter][closestPoints[3]][0];
        }
        p[closestPoints[3]].checked = false;
    }
    
    if (dist1 <= dist2){
        if (dist3 <= dist4){
            if (dist1 < dist3)
                return dist1;
            else
                return dist3;
        }
        else if (dist1 <= dist4)
            return dist1;
        else
            return dist4;
    }
    else{
        if (dist3 <= dist4){
            if (dist2 < dist3)
                return dist2;
            else
                return dist3;
        }
        else if (dist2 <= dist4)
            return dist2;
        else
            return dist4;
    }
}

int main(){
    
    partialTotal = 0;
    minTotalFound = DBL_MAX;
    
    //FOR GENERATING RANDOM POINTS
    ofstream myfile1;
    myfile1.open("hw1pr2_data.txt");
    for (int r = 0; r < 18; r++){
        myfile1 << rand() % 1000 << " " << rand() % 1000 << '\n';
    }
    myfile1.close();
    
    //getting input file into Points vector
    ifstream myfile;
    myfile.open ("hw1pr2_data.txt");
    int i = 0;
    int num;
    Point p;
    p.checked = false;
    while(myfile >> num){
        if (i % 2 == 0)
            p.x = num;
        else{
            p.y = num;
            points.push_back(p);
        }
        i++;
    }
    myfile.close();
    
    //Make a distance matrix (vector of vectors) and calc
    // each distance for each point
    vector<double> emptyList;
    vector<vector <double> > emptyMat;
    for (int i = 0; i < points.size(); ++i){
        
        distances.push_back(emptyMat);
        for (int j = 0; j < points.size(); ++j){
            
            distances[i].push_back(emptyList);
            distances[i][j].push_back(pointDist(points[i], points[j]));
            distances[i][j].push_back(double(j));
        }
    }
    
    sortedDistances = distances;
    
    for (int i = 0; i < distances.size(); i++){
        sort(sortedDistances[i].begin(), sortedDistances[i].end());
    }
    
    cout << "\nMatrix created. \n";
    
//    for (int i = 0; i < distances.size(); i++){
//        for (int j = 0; j < distances[i].size(); j++){
//            cout << distances[i][j][0] << "/" << distances[i][j][1] << " : ";
//        }
//        cout << endl << endl;
//    }
    
    points[0].checked = true;
    vector<Point> temp = points;
    greedyPathTotal = 0.0;
    i = 0;
    
    //getting the greedy path total
    while (true){
        int closestP = closestPoint(temp, i);
        if (closestP == -1)
            break;
        
        temp[closestP].checked = true;
        greedyPathTotal += distances[closestP][i][0];
        i = closestP;
    }
    greedyPathTotal += distances[0][i][0];
    
    //Call the recursive function on the first point
    double totalDist = findBestPath(0, points);

    //Display the result
    cout << "\nThe distance of the 4 best-first search algorithm solution is: " << totalDist << endl;
    cout << "The distance of the greedy search algorithm solution is: " << greedyPathTotal << endl << endl;
    
    return 1;
}

