/* same idea take an temporary array which have dimension depends on number of variable
changes in recursive call  */
#include<iostream>
using namespace std;
// time complexity O(m*n)
// space complexity O(m+1+n+1)
int memozation_LCS(string s1,string s2,int m,int n){
    int memozation[m+1][n+1]; // two dimension array due to m,n parameter changing in recursion
    for(int i=0;i<m+1;i++){
        for(int j=0;j<n+1;j++){
            memozation[i][j]=-1;
        }
    }
    if(memozation[m][n]!=-1){
        return memozation[m][n];
    }
    else{
    if(m==0||n==0){
         return memozation[m][n]=0;
    }
    else{
        if(s1[m-1]==s2[n-1]){
            return 1+memozation_LCS(s1,s2,m-1,n-1);
        }
        else{
            return max(memozation_LCS(s1,s2,m-1,n),memozation_LCS(s1,s2,m,n-1));
        }
    }
    }
    return memozation[m][n];
    

}
int main()
{
    string s1="AXYZ";
   string s2="BAZ";
   cout<<memozation_LCS(s1,s2,4,3);
 return 0 ;
}