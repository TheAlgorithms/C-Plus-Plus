# Problem Link:

[Link](https://www.codechef.com/NOV18B/problems/CHHAPPY)
# Description

Chef is happy only if three conditions hold:

    Chef finished cooking a delicious meal
    Chef got AC for a programming problem with an almost correct code
    Chef got a new problem with a sequence of integers

Today, all three conditions are satisfied. Chef would like you to feel his happiness and provide him with a solution for this new problem with a sequence of integers. The problem is as follows.

You are given a sequence A1,A2,…,AN
. You need to determine if it is possible to choose two indices i and j such that Ai≠Aj, but AAi = AAj.(If it was possible, Chef would be truly happy.)
### Input

    The first line of the input contains a single integer T denoting the number of test cases.
    The description of T test cases follows.
    The first line of each test case contains a single integer N.
    The second line contains N
    space-separated integers A1,A2,…,AN


### Output

For each test case, print a single line containing the string "Truly Happy" if it is possible to choose required indices or "Poor Chef" otherwise.
Constraints

    1≤T≤1,000
    1≤N≤10^5
    1≤Ai≤N
for each valid i the sum of N over all test cases does not exceed 2⋅10<sup>5</sup>

Subtasks

Subtask #1 (27 points): 1≤N≤1,000

Subtask #2 (73 points): original constraints
### Example Input

4

4

1 1 2 3

4

2 1 3 3

5

5 4 4 3 1

5

3 2 1 1 4

### Example Output

Truly Happy

Poor Chef

Poor Chef

Truly Happy
