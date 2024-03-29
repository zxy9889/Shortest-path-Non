#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int rows = 5, cols = 6;
int minRow, minLength;
string path[rows][cols];

void calculateCosts() {
   static int weight[rows][cols] = {{3,4,1,2,8,6},
                                    {6,1,8,2,7,4},
                                    {5,9,3,9,9,5},
                                    {8,4,1,3,2,6},
                                    {3,7,2,8,6,4}};
   static int cost[rows][cols] = {};
   
   for (int i = 0; i < rows; ++i) {
      cost[i][0] = weight[i][0];
      path[i][0] = to_string(i); 
  }
   for (int j = 1; j < cols; ++j)               
      for (int i = 0; i < rows; ++i) {          
         int up = cost[(i+rows-1)%rows][j-1];    
         int left = cost[i%rows][j-1];
         int down = cost[(i+1)%rows][j-1];
         int minCost = min(min(up, left), down);
         if (minCost == up)                      
            path[i][j] = path[(i+rows-1)%rows][j-1] + to_string(i);
         else if (minCost == left) 
            path[i][j] = path[i][j-1] + to_string(i);
         else
            path[i][j] = path[(i+1)%rows][j-1] + to_string(i);
         cost[i][j] = minCost + weight[i][j];    
      }
   minRow = 0, minLength = cost[0][cols-1];     
   for (int i = 1; i < rows; ++i)
      if (cost[i][cols-1] < minLength)
         minRow = i, minLength = cost[i][cols-1];
}
int main() {
   calculateCosts();
   cout << "The length of the shortest path is " << minLength;
   cout << ".\nThe rows of the path from left to right are " << path[minRow][cols-1] << ".";
   return 0;
}
