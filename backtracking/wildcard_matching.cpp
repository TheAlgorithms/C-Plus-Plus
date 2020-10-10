/*
WildCard Matching - Backtracking
Problem Statement: 
Given an matching string and a pattern, implement wildcard pattern matching with support for '?' and '*'.
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire matching string (not partial).
Task: 
Determine if the pattern matches with the matching string
*/


#include <iostream>
#include <vector> 
#include <string>

std::vector<std::vector<int>>dpTable(1000, std::vector<int>(1000, -1));
int wildcardMatching(std::string s, std::string p, int n, int m, int pos1, int pos2)
{
	    // matching is successfull if both strings are done
        if(pos1 == n && pos2 == m)
		    {
            return 1;
		    }

		// matching is unsuccessfull if pattern is not finished but matching string is
        if(pos1 != n && pos2 == m)
		    {
            return 0;
		    }

		// all the remaining characters of patterns must be * inorder to match with finished string
        if(pos1 == n && pos2 != m)
        {
            while(pos2 < m && p[pos2] == '*')
			      {
                pos2++;
			      }

            return pos2 == m;
        }

		// if already calculted for these positions
        if(dpTable[pos1][pos2] != -1)
		    {
            return dpTable[pos1][pos2];
		    }

		// if the characters are same just go ahead in both the string
        if(s[pos1] == p[pos2])
		    {
            return dpTable[pos1][pos2] = wildcardMatching(s, p, n, m, pos1 + 1, pos2 + 1);
		    }

        else
        {
		// can only single character
            if(p[pos2] == '?')
			      {
                return dpTable[pos1][pos2] = wildcardMatching(s, p, n, m, pos1 + 1, pos2 + 1);
			      }
			// have choice either to match one or more charcters
            else if(p[pos2] == '*')
			      {
                return dpTable[pos1][pos2] = wildcardMatching(s, p, n, m, pos1, pos2 + 1) || wildcardMatching(s, p, n, m, pos1 + 1, pos2);
			      }
			// not possible to match
            else
			      {
                return dpTable[pos1][pos2] = 0;
			      }
        }
}

int main() 
{
	  std::string matching = "", pattern = "";

    std::cout <<"Enter the matching string: ";
    std::cin >> matching;

    std::cout <<"Enter the pattern string ";
	  std::cin >> pattern;

    int matching_length = matching.length(), pattern_length = pattern.length();

    std::cout << wildcardMatching(matching, pattern, matching_length, pattern_length, 0, 0);
    return 0;
}
