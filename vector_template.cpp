#include<iostream>
using namespace std;
template <class t>
class MyVector
{
    t *v;
    int s;
    int capacity;
public:
    MyVector()
    {
        capacity = 2;
        v = new t[capacity];
        s= 0;
    }

    MyVector(t n)
    {
        capacity = n;
        v = new t[capacity];
        s = 0;
    }

    int Size()
    {
        return(s);
    }

    void push_back(t n)
    {
        if(s+1 > capacity)
        {
            allocNew();
        }
        v[s] = n;
        s++;
    }

    int Capacity()
    {
        return capacity;
    }

    t at(t n)
    {
        if(n < s)
        {
            return v[n];
        }
        // Throw an exception if n is greater than vector size
        throw 10;
    }

    void allocNew()
    {
        capacity = s * 2;
        t* temp = new t[capacity];
        for(int i = 0; i < s ; i++)
        {
            temp[i] = v[i];
        }
        delete v;
        v = temp;
    }

    void Clear()
    {
        delete []v;
        s = 0;
        capacity = 2;
        v = new t [capacity];
    }

    t pop_front()
    {
        if(s>0)
        {
            t n = v[0];
            t*temp = new t[s];
            for(int i=0;i<s-1;i++)
            {
                temp[i] = v[i+1];
            }
            v = temp;
            s--;
            capacity-=2;
            return n;

        }
        else
            throw  ;
    }
};

int main()
{
    MyVector<int> vect(5);
    vect.push_back(12);
    vect.push_back(1);
    vect.push_back(8);
    vect.push_back(95);
    vect.push_back(47);
    vect.push_back(28);

    cout<<"\nThe Size:- "<<vect.Size();
    cout<<"\nThe Capacity:- "<<vect.Capacity();

    cout<<"\n\t"<<vect.pop_front();

    cout<<"\nNew Size:- "<<vect.Size();
    cout<<"\nNew Capacity:- "<<vect.Capacity();

    cout<<"\n\t"<<vect.pop_front();
    cout<<"\n\t"<<vect.pop_front();

    cout<<"\nElement at 3rd pos is:- "<<vect.at(2);

    return 0 ;
}
