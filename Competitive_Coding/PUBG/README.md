# Problem Link:

[Link](https://www.codechef.com/NUVO2019/problems/PUBG)
# Description

Playerunknown's Battlegrounds Mobile, popularly known as PUBG is the favourite mobile game of millions. Such is its popularity, that it had to be banned in several regions to account for its addiction. This reduced the number of real players on some servers and increased the number of bots.

On one of the PUBG servers, real players can team up as “squad” of four members, “duo” of two members or play alone as “solo”. The server must contain exactly p players for the match to start and so, bots are added to fill up the player count to p in cases when there are not enough "real" players on the server.

On a particular server, there are a number of squads, b number of duos, c number of solo players and d number of bots. Given the number of bots, d on the server when the match starts, find the total number of distinct values of triplets (a, b, c) possible on the server.

**Input:**

    The first line of the input contains a single integer T
    denoting the number of test cases.
    The description of T test cases follows.
    The first and only line of each test case contains two space separated integers p
    and d

**Output:**

    For each test case, print a single line containing one integer — the total number of distinct values of triplets (a, b, c) posible on the server. 

### Constraints

    1≤T≤3⋅10^5
    100≤p≤10^5
    0≤d≤p−4
    0≤a,b,c

### Subtasks
Subtask #1 (10 points):

    1≤T≤3⋅10^3
    100≤p≤1000

Subtask #2 (30 points):

    1≤T≤3⋅10^4
    100≤p≤10000

Subtask #3 (60 points):

    Original Constraints 

### Sample Input:
1

100 94

### Sample Output:
6
