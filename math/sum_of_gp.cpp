#include <iostream>
#include <math.h>

float sum_of_gp(int first_term_of_gp, float common_ratio, int no_of_terms)
{
    if(common_ratio==1)
    {
        return no_of_terms*first_term_of_gp;
    }
    else
    {
        float t1,t2,ans;
        t1=1-pow(common_ratio,no_of_terms);
        t2=1-common_ratio;
        ans=first_term_of_gp*t1/t2;
        return ans;
    }
}


int main() {
    
    std::cout <<"the output of your GP is "<<sum_of_gp(5,0.2,10);

    return 0;
}

