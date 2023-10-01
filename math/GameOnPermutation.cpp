//Link to the question- https://codeforces.com/problemset/problem/1860/C

#include<iostream>
#include<math.h>
using namespace std;
int main(){
	int t;cin>>t;
    while(t--){
        int noOfElement;cin>>noOfElement;
        int minTotal=noOfElement+1;
        int adjLeft=noOfElement+1;
        int count=0;
        for(int i=0;i<noOfElement;i++){
            int element;
            cin>>element;
            if(!(element<minTotal || element>adjLeft)){
                count++;
                adjLeft=element;
            }           
            minTotal=min(minTotal,element);
        }cout<<count<<endl;
    }
    return 0;
}

Test cases-
4
3
2 1 3
2
2 1
3
1 2 3
4
2 1 4 3
Output- 1 0 1 2
