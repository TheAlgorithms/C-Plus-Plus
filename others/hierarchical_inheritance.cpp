//heirarchial inheritance
#include<iostream>
using namespace std;
class a{
    protected:
    int i;
};
class b:public a{
    protected:
    int j;
    public:
    void input(){
        cout<<"Enter j: ";
        cin>>j;
    }
    void output(){
        cout<<"j is "<<j<<endl;
    }
};
class c: public a{
    protected:
    int k;
    public:
    void get(){
        cout<<"Enter i  k: ";
        cin>>i>>k;
    }
    void show(){
        cout<<"i = "<<i<<" k = "<<k;
    }
};
int main(){
    c c1;
    b b1;
    b1.input();
    b1.output();
    c1.get();
    c1.show();
    return 0;
}