# Problem Link:

[Link](https://www.codechef.com/problems/H1)
# Description
ohnny has some difficulty memorizing the small prime numbers. So, his computer science teacher has asked him to play with the following puzzle game frequently.

The puzzle is a 3x3 board consisting of numbers from 1 to 9. The objective of the puzzle is to swap the tiles until the following final state is reached:

    1 2 3
    4 5 6
    7 8 9

At each step, Johnny may swap two adjacent tiles if their sum is a prime number. Two tiles are considered adjacent if they have a common edge.

Help Johnny to find the shortest number of steps needed to reach the goal state.
Input

The first line contains t, the number of test cases (about 50). Then t test cases follow. Each test case consists of a 3x3 table describing a puzzle which Johnny would like to solve.

The input data for successive test cases is separated by a blank line.
Output

For each test case print a single line containing the shortest number of steps needed to solve the corresponding puzzle. If there is no way to reach the final state, print the number -1.
Example

### Input:
    2

    7 3 2 
    4 1 5 
    6 8 9 

    9 8 5 
    2 4 1 
    3 7 6  

### Output:
    6
    -1

