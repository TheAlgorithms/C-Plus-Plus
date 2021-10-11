#include <bits/stdc++.h>
using namespace std;

struct Stack
{
    queue<int> main_q, auxiliary_q;
    int current_size = 0;

    int top()
    {
        return main_q.front();
    }
    void push(int val)
    {
        auxiliary_q.push(val);
        while(!main_q.empty())
        {
            auxiliary_q.push(main_q.front());
            main_q.pop();
        }
        swap(main_q, auxiliary_q);
        // queue<int> q = main_q;
        // main_q=auxiliary_q;
        // auxiliary_q=q;
        current_size++;
    }
    void pop()
    {
        if(main_q.empty())
            return ;
        main_q.pop();
        current_size--;
    }
    int size()
    {
        return current_size;
    }
};


int main()
{

    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
  
    cout << "current size: " << s.size() << endl;
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.push(5);
    cout<<s.top()<<endl;
    s.pop();
    cout<<s.top()<<endl;
  
    cout << "current size: " << s.size() << endl;

    return 0;

}