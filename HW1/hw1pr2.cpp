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

Point* copyPointArray(Point p[]){
    
    Point *result = new Point[10000];
    
    for (int i = 0; i < 10000; i++){
        result[i].x = p[i].x;
        result[i].y = p[i].y;
        result[i].checked = p[i].checked;
    }
    
    return result;
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
        //cout << i << " : " << p[i].checked << endl;
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
        else if (tempDis < pointDist(p[result[0]], p[iter])){
            
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
        else if (tempDis < pointDist(p[result[1]], p[iter])){
            result[3] = result[2];
            result[2] = result[1];
            result[1] = i;
        }
        else if (result[2] == -1){
            result[2] = i;
            p[i].checked = true;
        }
        else if (tempDis < pointDist(p[result[2]], p[iter])){
            result[3] = result[2];
            result[2] = i;
        }
        else if (result[3] == -1){
            result[3] = i;
            p[i].checked = true;
        }
        else if (tempDis < pointDist(p[result[3]], p[iter])){
            result[3] = i;
        }
        
        ++i;
    }
    
    return result;
}

double findBestPath(int pointIter, Point p[]){
    
    Point* tempPointArray = copyPointArray(p);
    int *closestPoints = fourClosestPoints(tempPointArray, pointIter);
    
    //base case: only 1 point left to check
    if (closestPoints[1] == -1){
        return pointDist(p[pointIter], p[closestPoints[0]]) +
               pointDist(p[closestPoints[0]], p[0]);
    }
    
    //first point
    p[closestPoints[0]].checked = true;
    double dist1 = pointDist(p[pointIter], p[closestPoints[0]]) +
                   findBestPath(closestPoints[0], p);
    p[closestPoints[0]].checked = false;
    
    //second point
    p[closestPoints[1]].checked = true;
    double dist2 = pointDist(p[pointIter], p[closestPoints[1]]) +
                   findBestPath(closestPoints[1], p);
    p[closestPoints[1]].checked = false;
    
    double dist3 = DBL_MAX;
    double dist4 = DBL_MAX;
    
    //if there is a 3rd point
    if (closestPoints[2] != -1){
        p[closestPoints[2]].checked = true;
        dist3 = pointDist(p[pointIter], p[closestPoints[2]]) +
                findBestPath(closestPoints[2], p);
        p[closestPoints[2]].checked = false;
    }
    
    //if their is a fourth point
    if (closestPoints[3] != -1){
        p[closestPoints[3]].checked = true;
        dist4 = pointDist(p[pointIter], p[closestPoints[3]]) +
                findBestPath(closestPoints[3], p);
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
        
    //setting up point array
    Point p;
    p.x = -1;
    p.y = -1;
    p.checked = false;
    Point points[10000];
    fill_n(points, 10000, p);
    
    //getting input file into Points array structure
    ifstream myfile;
    myfile.open ("hw1pr2_data.txt");
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
    
    //Call the recursive function on the first point
    points[0].checked = true;
    double totalDist = findBestPath(0, points);

    //Display the result
    cout << "\nThe distance of the 4 best-first search algorithm solution is: " << totalDist << endl << endl;
    
    return 1;
}

