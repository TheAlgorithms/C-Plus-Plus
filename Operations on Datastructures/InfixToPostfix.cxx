#include<iostream>
using namespace std;
#define max 100
class InfixToPostfix
{
	char a[max];
	int top;
public:
	InfixToPostfix(){
		top=-1;
	}
	void push(char element){
		if(top==max){
			cout<<"Stack Overflow"<<endl;
		}
		else{
			a[++top]=element;
		}
	}
	char pop(){
		if(top<0){
                cout<<"Stack Underflow";
			return '0';
		}
		else{
			return a[top--];
		}
	}
	char peek(){
		if(top<0){
			cout<<"Stack Underflow";
			return '0';
		}
		else{
			return a[top];
		}
	}
    int precedence(char ch){
        switch(ch){
            case '^' :
                return 3;
            case '*' :
            case '/' :
                return 2;
            case '+' :
            case '-' :
                return 1;
            default : return -1;
        }
    }
    bool character(char ch){
        return ((ch>='a')&&(ch<='z'))||((ch>='A')&&(ch<='Z'));
    }
    string convert(string s){
        InfixToPostfix st;
        int l=s.length();
        string ns="";
        st.push('N');
        for(int i=0;i<l;i++){
            if(character(s[i]))
                ns=ns+s[i];
            else if(s[i]=='(')
                st.push('(');
            else if(s[i]==')'){
                while(st.peek()!='N'&&st.pop()!='('){
                        char c=st.peek();
                        st.pop();
                        ns+=c;
                      }
                if(st.peek()=='('){
                    char c=st.peek();
                        st.pop();
                }
            }
            else{

            while( (st.peek()!='N') && (precedence(s[i])<=precedence( st.peek() ) )){
                    char c=st.peek();
                        st.pop();
                        ns+=c;
                }

                st.push(s[i]);
            }
        }
        while(st.peek()!='N'){
            char c=st.peek();
            st.pop();
            ns+=c;
        }
        return ns;
    }
};
int main()
{   InfixToPostfix ob;
    cout<<"Enter a Infix Expression"<<endl;
    string exp;cin>>exp;
    cout<<"Postfix Expression is \t";
    cout<<ob.convert(exp);
	return 0;
}
