//capitalize first and last letter 
#include<bits/stdc++.h>
using namespace std;

int main(){
    string result = "abhiraj";
    for(int i=0;i<result.size();i++){
        if (i == 0 || i == result.size() - 1) {
            if (islower(result[i])) {
            result[i] = toupper(result[i]);
            } else if (isupper(result[i])) {
            result[i] = tolower(result[i]);
            }
        }
    } 
    cout<<result;
    return 0;
}