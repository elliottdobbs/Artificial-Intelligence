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
using namespace std;

struct Point{
    int x;
    int y;
    bool checked;
};

double pointDist(Point p1, Point p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y));
}

int* fourClosestPoints(Point p[], int iter){
    
    int i = 0;
    int *result = new int[4];
    result[0] = -1; result[1] = -1; result[2] = -1; result[3] = -1;
    double tempDis;
    
    //Checks the distance between the given point (via iter)
    // and all other non visited points to return the iteration
    // location of the closest point
    while(p[i].x != -1){
        if (p[i].checked){
            ++i;
            continue;
        }
        
        tempDis = pointDist(p[i], p[iter]);
        
        //Check if there is nothing in the spot
        if (result[0] == -1){
            result[0] = i;
            p[i].checked = true;
        }
        //if there is something, check if its shorter than the found one
        else if (tempDis < pointDist(p[result[0]], p[iter]){
            
            //if we have a new shortest distance, shift the
            // rest of the shortest points to make room
            result[3] = result[2];
            result[2] = result[1];
            result[1] = result[0];
            result[0] = i;
        }
        //repeat with the other locations in result
        else if (result[1] == -1){
            result[1] = i;
            p[i].checked = true;
        }
                 //keep replacing the sqrt with enw function
        else if (tempDis < sqrt((p[result[1]].x - p[iter].x)*
                                (p[result[1]].x - p[iter].x) +
                                (p[result[1]].y - p[iter].y)*
                                (p[result[1]].y - p[iter].y))){
            result[3] = result[2];
            result[2] = result[1];
            result[1] = i;
        }
        else if (result[2] == -1){
            result[2] = i;
            p[i].checked = true;
        }
        else if (tempDis < sqrt((p[result[2]].x - p[iter].x)*
                                (p[result[2]].x - p[iter].x) +
                                (p[result[2]].y - p[iter].y)*
                                (p[result[2]].y - p[iter].y))){
            result[3] = result[2];
            result[2] = i;
        }
        else if (result[3] == -1){
            result[3] = i;
            p[i].checked = true;
        }
        else if (tempDis < sqrt((p[result[3]].x - p[iter].x)*
                                (p[result[3]].x - p[iter].x) +
                                (p[result[3]].y - p[iter].y)*
                                (p[result[3]].y - p[iter].y))){
            result[3] = i;
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
    myfile.open ("hw1pr1_data.txt");
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
    
    //Start with the first point and get the closest point to it
    // Then add the distance to the total distance, and keep going
    points[0].checked = true;
    i = 0;
    double totalDist = 0.0;
    
    //maybe recursive function here instead of loop
    /*
     so here we have
         closestPoints : the 4 closest points of the start point
         points[] : with all the points and only first point marked as checked
     
     
     -a recursion will have base cases, closestPoints size 1
         -this means we are at a last point
         -so we need send the distance from this node to the start node,
         -(and the dist from the prev to this node?)
     -we return the distance of
     */
    while (true){
        int *closestPoints = fourClosestPoints(points, i);
        
        if (closestPoints[0] == -1)
            break;

        points[closestP].checked = true;
        totalDist += sqrt((points[closestP].x - points[i].x)*
                          (points[closestP].x - points[i].x) +
                          (points[closestP].y - points[i].y)*
                          (points[closestP].y - points[i].y));
        i = closestP;
    }

    //Once all points are checked, add on the last distance of the last
    //  visited point to the starting points
    totalDist += sqrt((points[0].x - points[i].x)*
                      (points[0].x - points[i].x) +
                      (points[0].y - points[i].y)*
                      (points[0].y - points[i].y));

    //Display the result
    cout << "\nThe distance of the greedy best-first search algorithm solution is: " << totalDist << endl << endl;
    
    return 1;
}

