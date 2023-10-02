#include<iostream>
#include<iomanip>
#include<limits>
#include<math.h>
using namespace std;
double solve(double x){
    double res = x*sin(x) - 1;
    return res;
}
int main(){
    double i=0, x0, x1, k, n=12;
    while(true){
        if(solve(i)>=0 && solve(i+1)<0){
            x0 = i;
            x1 = i+1;
            k = 1;
            break;
        }
        else if(solve(i)<0 && solve(i+1)>=0){
            x0 = i;
            x1 = i+1;
            k = 2;
            break;
        }
        i++;
    }
    double low = x0, pres = INT_MIN;
    double high = x1;
    for(int i=0; i<n; i++){
        double mid = (low+high)/2;
        double next = solve(mid);
        cout<<"x1="<<low<<" x2="<<high<<" mid="<<mid<<" f("<<mid<<")="<<next<<endl;
        if(next==pres){
            break;
        }
        else{
            pres = next;
        }
        
        if(k==1){ // from + to -
            if(next<0){
                high = mid;
            }
            else if(next>0){
                low = mid;
            }
        }
        else if(k==2){ //from - to +
            if(next<0){
                low = mid;
            }
            else if(next>0){
                high = mid;
            }
        }
    }
}
