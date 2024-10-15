//remove brackets from the string 
#include<bits/stdc++.h>
using namespace std;

int main(){
    string result = "(Abhiraj)";
    for(int i=0;i<result.size();i++){
        if(result[i] == '(' || result[i] == ')'){
            result.erase(i,1);
        }
        else{
            i++;
        }
    } 
    cout<< result << endl;
    return 0;
}