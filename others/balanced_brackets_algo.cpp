/*
    This will cover the algorithm for checking if brackets are balanced
    using a stack
    Ex: {{}}} is not closed
        {{}{}}{} is closed
    Constraits: let the input string only consist of '{' or '}'
*/

#include <stack>
#include <iostream>
#include <string>

using namespace std;

// returns true if balanced, false if not
bool balanceBrackets(string s)
{
    // use stack to track the left brackets
    // pop off the stack when there's a right bracket
    stack<char> brackets;
    bool balanced = true;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '{')
        {
            brackets.push('{');
        }    
        else
        {
            if (brackets.empty())
            {
                balanced = false;
                break;
            }
            else
            {
                brackets.pop();
            }
        }
    }

    
    if (brackets.empty() == false)
    {
        balanced = false;
    }

    return balanced;
}


void test()
{
    string testOne = "{{{}}}}";
    string testTwo = "{{{}}}{}";
    string testThree = "{}{{";

    cout << balanceBrackets(testOne) << endl;
    cout << balanceBrackets(testTwo) << endl;
    cout << balanceBrackets(testThree) << endl;
}

int main()
{
    string in;

    cout << "Enter a string of brackets consiting of { and }" << endl;
    cin >> in;

    bool b = balanceBrackets(in);

    if (b == true)
        cout << "Balanced!!!" << endl;
    else
        cout << "Not balanced..." << endl;
    
    return 0;
}