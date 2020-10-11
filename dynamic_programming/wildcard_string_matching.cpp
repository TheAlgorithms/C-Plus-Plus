/*
WildCard Matching - Backtracking

Problem Statement: 
Given an matching string and a pattern, implement wildcard pattern matching with support for '?' and '*'.
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire matching string (not partial).

Task: 
Determine if the pattern matches with the matching string

Solution:  we start comparing the two string from left, if the character at ith position in first
string matches with the jth character of the second string we will just move ahead in both the string,
if they are not same and character at jth position of second string is neither '?' nor '*' then matching
is not possible. If it is '?' then we will convert this symbol to charcter present in the second string and
move ahead. If it is '*' the we have choice either to match zero or multiple characters thus we have two
recursive calls here. If both string are done ans is true, but if the pattern is not finished yet but the
matching string is then the pattern string can only have '*' character so that we can match empty sequence
in return to it.
*/


#include <iostream>
#include <vector> 
#include <string>
#include <cassert>

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

static void test()
{
  // Test 1
  {
   std::vector<std::vector<int>>tempTable(1000, std::vector<int>(1000, -1));
   std::string matching = "acdcb" ;
   std::string pattern = "a*c?b";
   int n = matching.size(), m = pattern.size();
   dpTable = tempTable;
   
   int output = wildcardMatching(matching, pattern, n, m, 0, 0);
   assert(output == 0);
   std::cout << "Input: ";
   std::cout << matching << " " << pattern << std::endl;
   std::cout << "Output: 0" << std::endl;
  }
  
  // Test 2
  {
   std::vector<std::vector<int>>tempTable(1000, std::vector<int>(1000, -1));
   std::string matching = "adceb";
   std::string pattern = "*a*b";
   int n = matching.size(), m = pattern.size();
   dpTable = tempTable;
   
   int output = wildcardMatching(matching, pattern, n, m, 0, 0);
   assert(output == 1);
   std::cout << "Input: ";
   std::cout << matching << " " << pattern << std::endl;
   std::cout << "Output: 1" << std::endl;
  }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
 
int main() 
{
	test();
    return 0;
}
