#include<iostream>
#include<queue>
using namespace std;

void pop(queue<int>&q1,queue<int>&q2)
{
    int n=q1.size();
    for(int i=1;i<n;++i)
    {
        q2.push(q1.front());
        q1.pop();
    }

    cout<<q1.front()<<" has been popped\n";
    q1.pop();
    swap(q2,q1);
}

void push(queue<int>&q1,int num)
{
    q1.push(num);
}

void display(queue<int>q1,queue<int>q2)
{
    int n=q1.size();
    for(int i=0;i<n;++i)
    {
        for(int j=i+1;j<n;++j)
        {
            q2.push(q1.front());
            q1.pop();
        }
        cout<<q1.front()<<" ";
        q1.pop();
        swap(q1,q2);
    }
    cout<<"\n";
}

int main()
{
    queue<int> q1,q2;
    push(q1,1);
    push(q1,2);
    push(q1,3);
    push(q1,4);
    display(q1,q2);
    pop(q1,q2);
    display(q1,q2);
    pop(q1,q2);
    display(q1,q2);
    return 0;
}
