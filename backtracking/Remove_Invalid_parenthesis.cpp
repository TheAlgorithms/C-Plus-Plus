/**
 * @file
 * @brief Implements [Remove Invalid Parenthesis]
 * (https://www.geeksforgeeks.org/remove-invalid-parentheses/) algorithm
 *
 * @details
 *  An expression will be given which can contain open and close parentheses 
 * and optionally some characters, No other operator will be there in string. 
 * We need to remove minimum number of parentheses to make the input string valid. 
 * If more than one valid output are possible removing same number of parentheses
 *  then print all such output.
 * @author [Kirti Singh](https://github.com/kirtisingh3008)
 * @author [David Leal](https://github.com/Panquesito7)
 */
#include<bits/stdc++.h>// This includes almost all the library function in cpp
using namespace std;
// This is function implementation to check if the string is valid or invalid
bool is_valid(string s)
{
    int cnt_brackets=0;// we maintain a counter for taking count of brackets
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='(')
        {
            cnt_brackets++;
        }
        else if(s[i]==')')
        {
            cnt_brackets--;
        }
        if(cnt_brackets<0)// if at any point the counter becomes less than 0 it would return false;
        {
            return false;
        }
    }
    return (cnt_brackets==0);// return true only if cnt of opening and closing brackets is equal
}
// It is a function implemantion to check if the char is bracket or any other characters or numerals 
bool para(char c)
{
    return (c=='(' || c==')');
}
// Below is the implementation of solve function
void solve(string s)
{
    int n=s.size();
    set<string> st;// we are using set to avoid duplicate valid strings in our answer
    queue<string> q;// Queue to maintain Breadth-First-Search
    string temp;
    st.insert(s);// inserting the given string in set as well as queue
    q.push(s);
    bool level =false;// // If answer is found, it would check valid string of only that level is processed.
    while(q.empty()==false)
    {
        string k=q.front();
        q.pop();
           //taking the first entered string to check
             if(is_valid(k)==true)// if it comes to be valid we will be printing it
             {
                 cout<<k<<endl;
                 level=true;
             }
             if(level==true)// if it is already there then continue
             {
                 continue;
             }
             for(int i=0;i<k.size();i++)
             {
                 if(!para(k[i]))// if a character "no brackets" then proceed
                 {
                     continue;
                 }
                 // Removing parenthesis from str and
                // pushing into queue,if not visited already
                 temp=k.substr(0,i)+k.substr(i+1);
                    if(st.find(temp)==st.end())
                    {
                        st.insert(temp);
                        q.push(temp);
                    }
             }
    }
}
// Below is the implementation of string of main function
// it will be having string input 
// returns 0 on the exit
int main()
{
   string input_string1 = "()())()";
    solve(input_string1);
    string input_string2= "()v)";
    solve(input_string2);
    return 0;
}