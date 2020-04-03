#include<iostream>
#include<stdlib.h>
#include<math.h>


using namespace std;

class problem_12
{
    private:
        long long tNum;
        int divs;
        long long count;
        long long triNum(long long a)
        {
            long long result = (0.5)*a*(a+1);
            return result;
        }
        int sqrt;
    public:
        problem_12()
        {
            tNum = 0;
            divs = 0;
            count= 1;
            sqrt = 0;
        }
        
        void setNum(long long a)
        {   
            tNum = triNum(a);
        }
        void start()
        {
            while(divs<500)
            {
                divs = 0;
                setNum(count);                
                sqrt = pow(tNum, 0.5);
                for(int i=1;i<sqrt;i++)
                {
                    if(tNum%i == 0)
                        divs += 2;
                    if(sqrt*sqrt == tNum)
                        divs = divs - 1;
                }
                count++;
                    
            }
            cout<<tNum;
        }
};

int main()
{
    problem_12 first;
    first.start();
    return 0;
}
