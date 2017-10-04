//Elliott Dobbs 823004322
//CSCE 420
//Due: October 4, 2017
//hw1pr1.cpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <float.h>
#include <stdlib.h>
using namespace std;

//Point structure
struct Point{
    int x;
    int y;
    bool checked;
};

//Simple distance formula implementation
double pointDist(Point p1, Point p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y));
}

//Algorithm to find the iteration location of the
// closest unckecked point in the point array
int closestPoint(Point p[], int iter){
    
    int i = 0;
    int result = -1;
    double distance = DBL_MAX, tempDis;
    
    //Checks the distance between the given point (via iter)
    // and all other non visited points to return the iteration
    // location of the closest point
    while(p[i].x != -1 && i < 10000){
        if (p[i].checked){
            ++i;
            continue;
        }
        
        tempDis = pointDist(p[i], p[iter]);
        
        if (distance > tempDis){
            distance = tempDis;
            result = i;
        }
        ++i;
    }
    
    return result;
}

int main(){

    //setting up point array
    Point p;
    p.x = -1;
    p.y = -1;
    p.checked = false;
    Point points[10000];
    fill_n(points, 10000, p);
    
    //getting input file into Points array structure
    ifstream myfile;
    myfile.open("hw1pr1_data.txt");
    int i = 0;
    int num;
    while(myfile >> num){
        if (i % 2 == 0)
            points[i/2].x = num;
        else
            points[i/2].y = num;
        i++;
    }
    myfile.close();
    
    //Start with the first point and get the closest point to it,
    // add the distance to the total distance, and keep going
    points[0].checked = true;
    i = 0;
    double totalDist = 0.0;
    
    while (true){
        int closestP = closestPoint(points, i);
        if (closestP == -1)
            break;
        
        points[closestP].checked = true;
        totalDist += pointDist(points[closestP], points[i]);
        i = closestP;
    }
    
    //Once all points are checked, add on the last distance of the last
    //  visited point to the starting points
    totalDist += pointDist(points[0], points[i]);
    
    //Display the result
    cout << "\nThe distance of the greedy best-first search algorithm solution is: " << totalDist << endl << endl;
    
    return 1;
}
