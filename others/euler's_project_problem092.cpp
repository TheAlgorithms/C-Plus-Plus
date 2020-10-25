#include <iostream>

int getDigSqSum(int num){
    int res = 0;
    int a;
    while (num > 0){
        a = (num%10);
        res = res + (a*a);
        num = num - a;
        num = num/10;
    }
        
    return (res);
}

int main(){
    
    int trgNum ;

    std::cout<<"enter target number \n";
    std::cin >> trgNum;
    
    int firstSum=0;
    
    firstSum = getDigSqSum(trgNum);
    
    std::cout<<firstSum<<"\n";
    
    int n = firstSum;
    
    int lastSum=0;
    
    while (lastSum != firstSum){
            
        lastSum = 0;
        
        lastSum = getDigSqSum(n);
            
        std::cout<<lastSum<<"\n";  
        n = lastSum;
    }
    
return(0);
}

//foxtrot12
        
