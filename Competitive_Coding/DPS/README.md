# Problem Link:

[Link](https://www.codechef.com/problems/DPS)
# Description
A dummy palindromic string (DPS) is a string which can be converted into a palindrome by performing each of the following operations exactly once:
Permute the characters of the string in an arbitrary way.
Choose a valid index i and change the i-th character of the resulting string to a different character (not necessarily present in the original string).

You are given a string S. Find out whether it is a DPS.

**Input**

    The first line of the input contains a single integer T denoting the number of test cases.
    The description of T
    test cases follows.
    The first and only line of each test case contains a single string S

**Output**

For each test case, print a single line containing the string "DPS" if the string is a DPS or "!DPS" if it is not (without quotes).
Constraints

    1≤T≤10^2
    1≤|S|≤10^4

S:contains only lowercase English letters

**Subtasks**

Subtask #1 (30 points): S

contains only the letter 'a'

Subtask #2 (70 points): original constraints

**Example Input**

4

code

xyxyxy

sad

baab


**Example Output**

!DPS

DPS

DPS

!DPS

