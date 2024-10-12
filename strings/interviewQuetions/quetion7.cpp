//to check repeating character

#include<bits/stdc++.h>
using namespace std;

int main(){
    string result = "Abhiraj"; 
    sort(result.begin(),result.end()); 
    
    for(int i=0;i<result.size()-1;i++){
        if(result[i]==result[i+1]){
           cout<<"this character is repeating:"<<" "<<result[i]<<endl;
        }
    } 

    return 0;
}