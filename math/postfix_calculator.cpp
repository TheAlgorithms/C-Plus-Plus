/*
 *
 * Copyright 2020 @author RameshwarPawar
 *
 * @file
 * program to calculate prosfix expression
 *
 */
#include<iostream>
#include<stack>
#include<cstring>

void infix_to_postfix(char *in, char *post);
bool is_operand(char ch);
int priority(char opr);
int postfix_evaluation(char *post);
int calculate(int op1, int op2, char opr);

void infix_to_postfix(char *in, char *post) {
int j=0;
std::stack<int> s;

for(int i = 0 ; in[i] != '\0' ; i++ ) {
if( is_operand(in[i]) ) {
post[j++] = in[i];
}else if( in[i] == '(') {
s.push(in[i]);
}else if( in[i] == ')') {
while( s.top() != '(' ) {
post[j++] = s.top();
s.pop();
}
s.pop();
}else {
while( !s.empty() && priority(s.top()) >= priority(in[i])) {
post[j++] = s.top();
s.pop();
}
s.push(in[i]);
}
}
while( !s.empty()) {
post[j++] = s.top();
s.pop();
}
post[j] = '\0';
}

int postfix_evaluation(char *post) {
int result;
std::stack<int> s;
for( int i = 0 ; post[i] != '\0' ; i++ ) {
if( is_operand(post[i])) {
s.push(post[i] - '0');
}else{
int op2 = s.top(); s.pop();
int op1 = s.top(); s.pop();
result = calculate(op1, op2, post[i]);
s.push(result);
}
}
result = s.top(); s.pop();
return result;
}

bool is_operand(char ch) {
return ( (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57) );
}

int calculate(int op1, int op2, char opr) {
switch(opr) {
case '+': return ( op1 + op2 );
case '-': return ( op1 - op2 );
case '*': return ( op1 * op2 );
case '/': return ( op1 / op2 );
case '%': return ( op1 % op2 );
}
return 0;
}
int priority(char opr) {
switch(opr) {
case '(': return 0;
case '+':
case '-': return 1;
case '*':
case '/':
case '%': return 2;
}
return 0;
}

int main(void) {
     char infix[64];
     std::cout << "Enter Infix Expression :";
     std::cin >> infix;
     char postfix[64] = "";
     std::cout << std::endl;
     std::cout << "Infix Expression : " << infix << std::endl;
     infix_to_postfix(infix, postfix);
     std::cout << "Postfix Expression : " << postfix << std::endl;
     std::cout << "Postfix Evaluation Result = " << postfix_evaluation(postfix) << std::endl;
return 0;
}

