#include <iostream>
#include<bits/stdc++.h>
using namespace std;

 vector<char>  a;

class Stack{
  public:

  void push(char n);
  bool isEmpty();
  bool top(char &top);
  bool pop();
  void paraCheck(string s);
};


void Stack :: push(char n){
 a.push_back(n);
}

bool Stack :: isEmpty(){
    if(a.size()==0){
        return true;
    }else{
        return false;
    }
}

bool Stack :: top(char &top){
 if(isEmpty()==true){
    return false;
 }else{
   top = a[a.size()-1];
   return true;
 }
}

bool Stack :: pop(){
    if(isEmpty()==true){
        return false;
    }else{
        a.pop_back();
        return true;
    }
}




int main()
{ cout<<"Instructions: \n";
    cout<<"Type add to push onto stack"<<endl;
    cout<<"Type del to pop from stack"<<endl;
    cout<<"Type top to check the top element in stack"<<endl;
    cout<<"Type PC for parenthesis checker "<<endl;
    cout<<"Type exit to stop using the stack"<<endl;

    Stack S;
    char top;
    while(1){
        string instruction;
        cout<<"Instruction: ";
        cin>>instruction;
        if(instruction=="exit"){
            break;
        }else if(instruction=="add"){
            cout<<"Enter the element top be pushed"<<endl;
            char push; //element to be pushed
            cin>>push;
            S.push(push);
                cout<<"Element successfully pushed"<<endl;
                if(S.top(top)==true){
                    cout<<"Top Element is:"<<top<<endl;
                }

        }else if(instruction=="del"){
            if(S.pop()==true){
                cout<<"Element was successfully popped"<<endl;
                if(S.top(top)==true){
                    cout<<"Top Element is:"<<top<<endl;
                }else{
                    cout<<"Stack is now Empty!"<<endl;
                }
            }else{
                cout<<"ERROR : Stack is empty!"<<endl;
            }
        }else if(instruction=="top"){
                if(S.top(top)==true){
                        char x;
                        x* = S.top(top);
                cout<<"x "<<x<<endl;
                    cout<<"Top Element is:"<<top<<endl;
                }else{
                    cout<<"ERROR : Stack is empty!"<<endl;
                }
        }
        else{
            cout<<"ERROR : Unknown operation! Please try again"<<endl;
        }
    }
}
