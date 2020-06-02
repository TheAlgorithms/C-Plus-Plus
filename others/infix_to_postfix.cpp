//Program to convert Infix expression to postfix expression
#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;
template<class T>
//creating a stack to store the operands
class stack
{
   private:
      T *t;
      int maxsize;
      int top;
   public:
       stack(int);
       void push(T);
       T pop();
       T peep();
};
template<class T>
stack <T>::stack(int ms)
 {
    t=new T(ms);
    maxsize=ms;
    top=-1;
}
template<class T>
void stack <T>::push(T v)
{
   if(top==maxsize-1)
      {
         cout<<"Stack overflow";
         return;
      }
    top++;
    t[top]=v;
}
template<class T>
T stack <T>::pop()
{
   if(top==-1)
    {
      cout<<"stack overflow:"<<endl;
      return(-1);
    }
  T temp;
  temp=t[top];
  top--;
return(temp);
}
template<class T>
T stack <T>::peep()
{
  if(top==-1)
    {
       cout<<"stack underflow";
       return(-1);
    }
  return(t[top]);
}
int precedence(char c)
{
  if(c=='^')
  return 3;
  else if(c=='*'||c=='/')
  return 2;
  else if(c=='+'||c=='-')
  return 1;
  else
  return -1;
}
void infixtopostfix(string s)
{
  stack<char> st(10);
  st.push('#');
  int l=s.length();
  string ns;
  for(int i=0;i<l;i++)
  {
    if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))
     ns+=s[i];
    else if(s[i]=='(')
    st.push('('); 
    else if(s[i]==')')
   {
      while((st.peep()!='#')&&(st.peep()!='('))
      {
        char c=st.peep();
        st.pop();
        ns+=c;
       }
     
       if(st.peep()=='(')
       {
         char c=st.peep();
         st.pop();
       }
    }

    else
    {
     while((st.peep()!='#')&&(precedence(s[i])<=precedence(st.peep())))
    {
      char c=st.peep();
      st.pop();
      ns+=c;
    }
    st.push(s[i]);
  }
}
while(st.peep()!='#')
{
  char c=st.peep();
  st.pop();
  ns+=c;
}

cout<<"postfix:"<<ns;
}

int main()
{
  string infix="a+b*(c^d-e)^(f+g*h)-i";
  infixtopostfix(infix);
  return 0;
}