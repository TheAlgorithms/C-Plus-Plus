#include<iostream>
using namespace std;
#define max 100
class PostfixEvaluation
{
	int a[max];
	int top;
public:
	PostfixEvaluation(){
		top=-1;
	}
	void push(int element){
		if(top==max){
			cout<<"Stack Overflow"<<endl;
		}
		else{
			a[++top]=element;
		}
	}
	int pop(){
		if(top<0){
                cout<<"Stack Underflow";
			return -1;
		}
		else{
			return a[top--];
		}
	}
	int peek(){
		if(top<0){
			cout<<"Stack Underflow";
			return -1;
		}
		else{
			return a[top];
		}
	}
	int evaluation(string st){
	    PostfixEvaluation s;
	    for(int i=0;i<st.length();i++){
            char ch=st[i];
            if(isdigit(ch))
                s.push(ch-'0');
            else{
                int a=s.pop();
                int b=s.pop();

                switch(ch){
                    case '+' : s.push(b+a); break;
                    case '-' : s.push(b-a); break;
                    case '/' : s.push(b/a); break;
                    case '*' : s.push(b*a); break;
                }
            }
	    }
	    return s.pop();
	}
};
int main()
{   PostfixEvaluation ob;
    cout<<"Enter a Postfix Expression"<<endl;
    string exp;cin>>exp;
    cout<<"Evaluation is ";
    cout<<ob.evaluation(exp);
	return 0;
	return 0;
}
