#include <cstring>
#include <iostream>
#include <stack>
using namespace std;

int precedance(char ch) {
    if (ch == '^')
        return 3;
    else if (ch == '/' || ch == '*')
        return 2;
    else if (ch == '+' || ch == '-')
        return 1;
    else
        return -1;
}  // for precedence of operators

string infixToPostfix(string s) {
    stack<char> st;
    string result = "";

    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];
        // If the current character is an operand, add it to our answer string.
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9'))
            result += ch;

        // If the current character of string is an '(', push it to the stack.
        else if (ch == '(')
            st.push('(');

        // If the current character of string is an ')', append the top
        // character of stack in our answer string and pop that top character
        // from the stack until an '(' is encountered.
        else if (ch == ')') {
            while (st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop();
        }

        else {
            while (!st.empty() && precedance(s[i]) <= precedance(st.top())) {
                result += st.top();
                st.pop();
            }
            st.push(ch);  // Push the current character of string in stack
        }
    }

    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    return result;
}  // Poping all the remaining elements from the stack

int main() {
    string s;
    cout << "Enter the expression to be converted: ";
    cin >> s;
    cout << infixToPostfix(s);
    return 0;
}