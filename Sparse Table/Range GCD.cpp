
// USE of sparse table to get range gcd in O(1) almost

#include<iostream>
#include<numeric>
#define ll long long
#define mp make_pair
#define pb push_back

using namespace std;
using namespace __detail;
const int N=2e6;

ll ar[N],n;

ll sp[N][20];
ll lg[N];

// Building the Sparse Table
void buildSparse(){
    for(int i=1;i<=n;i++) 
        sp[i][0]=ar[i];
    for(int i=2;i<=n;i++) 
        lg[i]=lg[i-1]+!(i&(i-1));
    for(int j=1;j<20;j++)
        for(int i=1;i+(1<<(j-1))<=n;i++) 
            sp[i][j]=__gcd(sp[i][j-1],sp[i+(1<<(j-1))][j-1]);
}

// returns the gcd in O(1)*O(gcd(x,y))
ll query(int tl, int tr){
    // return the gcd of (ar[l],ar[l+1]...ar[r])
    int to=lg[tr-tl+1];
    return __gcd(sp[tl][to],sp[tr-(1<<to)+1][to]);
}


void input(){
    cin>>n;
    for(int i=1;i<=n;i++)  
        cin>>ar[i];
}

void output(){
    int q;
    cin>>q;
    while(q--){
        int l, r;
        cin>>l>>r;
        cout<<query(l,r)<<"\n";
    }
}

int main(){

    input();    
    buildSparse();
    output();

    return 0;
}
