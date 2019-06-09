# Problem Link:
[Link](https://www.codechef.com/NUVO2019/problems/CANDC)
# Description
Tis’ the holiday season, and the Chef is inviting the best coders to his annual summer beach party. He invites n

people, and they all enter one after the other. The Chef has arranged a chess competition in his party, and needs to divide all his friends into pairs to play the game. Note : if any invitee is left unpaired, that person will play against the Chef, otherwise the chef will not participate.

The chef decides the number of ways the invitees can be paired at any instant to be called the magic number of the party M
. For example, if there are 3 people invited, the magic number at the 1st instance is 1, because the 1st person to arrive at the party is paired with the chef. When the 2nd person arrives, he is paired with the 1st invitee, and the chef doesn’t play. Thus the magic number is 1. When the 3rd guest arrives, he has 3 people to play with (Counting the chef because one person will be left unpaired), Then the remaining 2 people will play against each other. Thus the magic number is 3

The chef wants to find out the magic number when all the guests have entered the party. Help him find this number out.
###Input:

    First line will contain T, number of testcases. Then the testcases follow.
    Each testcase contains of a single integer n, the number of guests invited to his party

### Output:

For each test case print M
. Since the outputs may be large, print it modulo 10<sup>9</sup>+7

Constraints

    1≤T≤10^6

    1≤n≤10^7

Subtask 1

    1≤T≤40

    1≤n≤40

Subtask 2

    Original Constraints

### Sample Input:

 4
 
 1
 
 2
 
 3
 
 4

### Sample Output:

 1
 
 1
 
 3
 
 3

EXPLANATION:

1) If only 1 friend is joining the party, then he will be paired with chef. The number of ways to form a pair is 1.

2) If two friends join the party one by one then when first friend joins the party chef will be paired with him so there is only 1 way and when the second friend joins the party he will be paired with the friend who joined first (chef will not play in this case) so the number of ways is 1.

3) If three friends join the party, then chef will play chess and the number of ways after all of them joins the party (that is, the final magic number) is 3.

4) If four friends join the party then chef will not play and the number of ways to form the pair will be 3. 
