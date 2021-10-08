#include<bits/stdc++.h>
using namespace std;
class Stack
{
    int Size;
    queue<int> q1;
    queue<int> q2;

public:
    Stack()
    {
        Size = 0;
    }
    void push(int value)
    {
        q2.push(value);
        Size++;
        while (!q1.empty())
        {
            q2.push(q1.front());
            q1.pop();
        }
        queue<int> temp = q1;
        q1 = q2;
        q2 = temp;
    }
    void pop()
    {
        q1.pop();
        Size--;
    }
    bool empty()
    {
        if (q1.empty())
        {
            return true;
        }
        return false;
    }
    int top()
    {
        if (!empty())
        {
            return q1.front();
        }
        return -1;
    }
    int size()
    {
        return Size;
    }
};

int main()
{
    Stack st;
    st.push(4);
    st.push(3);
    st.push(2);
    st.push(1);
    cout<<"Top Element : " << st.top() << endl;
    cout <<"Size : "<< st.size() << endl;
    cout<<"-----After 1st Pop-----"<<endl;
    st.pop();
    cout<<"Top Element : " << st.top() << endl;
    cout <<"Size : "<< st.size() << endl;
    cout<<"-----After 2nd Pop-----"<<endl;
    st.pop();
    cout<<"Top Element : " << st.top() << endl;
    cout <<"Size : "<< st.size() << endl;
    cout<<"-----After 3rd Pop-----"<<endl;
    st.pop();
    cout<<"Top Element : " << st.top() << endl;
    cout <<"Size : "<< st.size() << endl;
    cout<<"-----After 4th Pop-----"<<endl;
    st.pop();
    cout<<"Top Element : " << st.top() << endl;
    cout <<"Size : "<< st.size() << endl;
}