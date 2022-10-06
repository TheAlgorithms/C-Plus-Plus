#include<iostream>
using namespace std;
int main()
{
    int a,b;
    int x;
    cout<<"Enter the values of a and b : ";
    cin>>a>>b;
    
    try{
        if(x!=0)
        {
            x=a/(a-b);
            cout<<"The result is : "<<x<<endl;

        }
        else{
            throw(x);
        }
    }
    catch(int y)
    {
        cout<<"x cant be zero ";
    }



    return 0;
}