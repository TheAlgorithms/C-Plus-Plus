#include<iostream>

using namespace std;

int main(void){
    unsigned long int t, n;
    int flag;
    cin>>t;
    while(t--){
        cin>>n;
        int a[n],b,c;
        for(int i=0;i<n;i++)
        cin>>a[i];
        for(int i =0;i<n-1;i++)
            for(int j =i+1;j<n;j++){
                if(a[i]!=a[j]){
                    b = a[i]-1;
                    c = a[j]-1;
                        if(a[b] == a[c]){
                            cout<<"Truly Happy";
                            flag = 1;
                            goto jump;
                        }
                }
            }
        jump:
        if(flag == 0)
        cout<<"Poor Chef";
        cout<<"\n";
        flag =0;
    }
}

