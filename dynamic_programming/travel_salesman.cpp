/**
 * @file
 * @brief Implementation of [Travel Salesman Problem]
 * with dynamic approach
 * @details
 * Travelling Salesman Problem (TSP) : Given a set of cities and distances between every pair of cities, 
 * the problem is to find the shortest possible route that visits every city exactly once and returns to 
 * the starting point.
 * Time Complexity : O(n^2 * 2^n)
 * @author [Anshul Sharma](https://github.com/anshul-sharma-2002)
 */

#include<iostream>
using namespace std;

#define MAX 9999

int n=4; // Number of the places want to visit

//Next distan array will give Minimum distance through all the position
int distan[10][10] = {                
                    {0, 10, 15, 20},
                    {10, 0, 35, 25},
                    {15, 35, 0, 30},
                    {20, 25, 30, 0}
};
int completed_visit = (1<<n) -1;

int DP[16][4];


int travel_salesman(int mark,int position){

    if(mark==completed_visit){      // Initially checking whether all the places are visited or not
        return distan[position][0];
    }
    if(DP[mark][position]!=-1){
        return DP[mark][position];
    }

    //Here we will try to go to every other places to take the minimum
    // answer
    int answer = MAX;

    //Visit rest of the unvisited cities and mark the . Later find the 
    //minimum shortest path
    for(int city=0;city<n;city++){
        if((mark&(1<<city))==0){
            int newAnswer = distan[position][city] + travel_salesman( mark|(1<<city),city);
            answer = min(answer, newAnswer);
        }
    }

    return DP[mark][position] = answer;
}

int main(){

    /* initialize the DP array */
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            DP[i][j] = -1;
        }
    }
    cout<<"Minimum Distance Travelled : "<< travel_salesman(1,0) << endl;

    return 0;
}

