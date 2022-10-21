#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
//Extended Bottom Up approach, with internal Print. 
int Memoized_rodCut(int price[], int n) {
    int r[n + 1];   // `r[i]` stores the maximum profit achieved from a rod of length `i`
    int s[n + 1];  //For, storing the index values. 
    // Initializing maximum profit to 0
    for (int i = 0; i <= n; i++) {
        r[i] = 0;
        s[i]=0;
    }
    // Considering a rod of length `i`
    for (int i = 1; i <= n; i++) {
        // Dividing the rod of length `i` into two rods of length `j` and `i-j` each and take maximum
        for (int j = 1; j <= i; j++) {
            //T[i] = max(T[i], price[j - 1] + T[i - j]);
            if(r[i]<price[j - 1] + r[i - j]){
                r[i]=price[j - 1] + r[i - j];
                //Storing the Index values in another array.
                s[i]=j;
            }
        }
    }
    
    /*
    for(int i=0; i<n+1; i++){
        cout<<"S: "<<s[i]<<", "<<i<<endl;
    }
    */
    int ind=n;
    //Printing the Max. Len index values, 
    while (ind>0){
        //cout<<"Hemlo: "<<s[ind]<<endl; 
        cout<<s[ind]<<" ";
        ind-=s[ind];
    }
    // `r[n]` stores the maximum profit achieved from a rod of length `n`
    return r[n];
}
int main() {
    int n;
    cin >> n;
    int p[n];
    for(int i=0; i<n; i++){
        cin>>p[i];
    }
    cout << Memoized_rodCut(p, n);
    return 0;
}
