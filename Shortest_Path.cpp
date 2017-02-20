/**
* Jason Navi
* 4/7/16
* Program finds and prints both the length of the shortest path and 
* the row path of a 2D Grid from left to right 
*/
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// Represent the rows and columns of the 2D matrices for the path, weight, and cost matrices
const int rows = 5, cols = 6;

// Path matrix will be used for printing 
// Path[i][j] is a string of the row numbers of the shortest path that leads to that square
string path[rows][cols];

// Returns the cost of the shortest path from the left to the square in row i, column j
int calculateCost(int i, int j) {
    // Declare the weight matrix 
    static int weight[rows][cols] = {{3, 4, 1, 2, 8, 6},
                                     {6, 1, 8, 2, 7, 4},
                                     {5, 9, 3, 9, 9, 5},
                                     {8, 4, 1, 3, 2, 6},
                                     {3, 7, 2, 8, 6, 4}};

    // Declare the cost matrix
    static int cost[rows][cols] = {
            {3, 0, 0, 0, 0, 0},
            {6, 0, 0, 0, 0, 0},
            {5, 0, 0, 0, 0, 0},
            {8, 0, 0, 0, 0, 0},
            {3, 0, 0, 0, 0, 0}};

    // If the cost has already been calculated, return it
    if (j == 0) {
        path[i][j] = to_string(i);
        return cost[i][0];
    }

    // Check for the base case: 
    // If you are in the leftmost column, the square's cost is the same as its weight
    if (cost[i][j] != 0)
        return cost[i][j];

    // Calculate the costs of the 3 adjacent squares by calling the function recursively
    // Note that the grid is cylincdrical
    int up = weight[i][j] + calculateCost((i + 4) % 5, j - 1);
    int left = weight[i][j] + calculateCost(i, j - 1);
    int down = weight[i][j] + calculateCost((i + 1) % 5, j - 1);

    // Find the minimum of the 3 costs
    // Update the path matrix and concatenate the minimum of the 3 paths with the current row number
    int smallest = down;
    path[i][j] = path[(i + 1) % 5][j - 1] + to_string(i);
    if (up < smallest) {
        smallest = up;
        path[i][j] = path[(i + 4) % 5][j - 1] + to_string(i);
    }
    if (left < smallest) {
        smallest = left;
        path[i][j] = path[i][j - 1] + to_string(i);
    }

    // Calculate the cost of the current square, store the minimum cost for the next move in the cost matrix, and return the cost
    return cost[i][j] = smallest;
}

int main() {
    // Call the calculateCost function once for each square in the rightmost column of the grid
    // Check which one has the lowest cost
    int r = 0;
    int minLength = calculateCost(0, cols - 1);
    for (int i = 1; i < rows; i++)
        if (calculateCost(i, cols - 1) < minLength) {
            minLength = calculateCost(i, cols - 1);
            r = i;
        }

    // Print out the length(weight) of the shortest path and the row path  
    cout << "The length of the shortest path is " << minLength;
    cout << ".\nThe rows of the path from left to right are " << path[r][cols - 1] << ".";

    return 0;
}
