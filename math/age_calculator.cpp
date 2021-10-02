#include <iostream>
#include <time.h>
using namespace std;

int main()
{
    time_t s, val = 1;
    struct tm* current_time;
    
    s = time(NULL);
    
    current_time = localtime(&s);
    
    int n,Age;
    cout<<"\n"<<"Calculate your Age !!!"<<"\n";
    cout<<"\n"<<"Enter Your Birth Year"<<"\n";
    cin>>n;
    
    Age = ((current_time->tm_year + 1900)-n);
    cout<<"\n"<<"Your age is "<<Age<<"\n";
 return 0;   
}    