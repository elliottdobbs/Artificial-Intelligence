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

int closestPoint(Point p[], int iter){
    
    int i = 0;
    int result = -1;
    double distance = DBL_MAX, tempDis;
    
    //Checks the distance between the given point (via iter)
    // and all other non visited points to return the iteration
    // location of the closest point
    while(p[i].x != -1){
        if (p[i].checked){
            ++i;
            continue;
        }
        
        tempDis = sqrt((p[i].x - p[iter].x)*(p[i].x - p[iter].x) +
                       (p[i].y - p[iter].y)*(p[i].y - p[iter].y));
        
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
    
    while (true){
        int closestP = closestPoint(points, i);
        if (closestP == -1)
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

