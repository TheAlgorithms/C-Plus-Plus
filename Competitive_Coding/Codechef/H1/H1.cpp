#include <stdio.h>
#include <map>
#include <queue>
#include <utility>
using namespace std;
#define F first
#define S second
typedef long long int ll;
struct board{
    int a[3][3];
    ll val(){
        ll ans=0;
        for(int i=0;i<3;i++)for(int j=0;j<3;j++){
            ans*=10;
            ans+=a[i][j];
        }
        return ans;
    }
    void in(){
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)scanf("%d",&a[i][j]);
        return ;
    }
    bool operator ==(board b){
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)if(a[i][j]!=b.a[i][j])return false;
        return true;
    }
    void init(){
        int now=1;
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)a[i][j]=now++;
        return ;
    }
};
void swap(int &a,int &b){
    int temp=a;
    a=b;
    b=temp;
    return ;
}
int main(){
    pair<board,int> temp;
    board m;
    queue<pair<board,int>> q;
    ll cal;
    bool prime[20];
    map<ll,int>s;
    int t;
    scanf("%d",&t);
    for(int i=1;i<20;i++)prime[i]=false;
    prime[2]=prime[3]=prime[5]=prime[7]=prime[11]=prime[13]=prime[17]=prime[19]=true;
    temp.F.init();
    temp.S=0;
    q.push(temp);
    s.insert({temp.F.val(),0});
    while(!q.empty()){
        temp=q.front();
        q.pop();
        temp.S++;
        for(int i=0;i<3;i++)for(int j=0;j<3;j++){
            if(i-1>0){
                if(prime[temp.F.a[i][j]+temp.F.a[i-1][j]]){
                    swap(temp.F.a[i][j],temp.F.a[i-1][j]);
                    cal=temp.F.val();
                    if(s.find(cal)==s.end()){
                        s.insert({cal,temp.S});
                        q.push(temp);
                    }
                    swap(temp.F.a[i][j],temp.F.a[i-1][j]);
                }
            }
            if(i+1<3){
                if(prime[temp.F.a[i][j]+temp.F.a[i+1][j]]){
                    swap(temp.F.a[i][j],temp.F.a[i+1][j]);
                    cal=temp.F.val();
                    if(s.find(cal)==s.end()){
                        s.insert({cal,temp.S});
                        q.push(temp);
                    }
                    swap(temp.F.a[i][j],temp.F.a[i+1][j]);
                }
            }
            if(j-1>0){
                if(prime[temp.F.a[i][j]+temp.F.a[i][j-1]]){
                    swap(temp.F.a[i][j],temp.F.a[i][j-1]);
                    cal=temp.F.val();
                    if(s.find(cal)==s.end()){
                        s.insert({cal,temp.S});
                        q.push(temp);
                    }
                    swap(temp.F.a[i][j],temp.F.a[i][j-1]);
                }
            }
            if(j+1<3){
                if(prime[temp.F.a[i][j]+temp.F.a[i][j+1]]){
                    swap(temp.F.a[i][j],temp.F.a[i][j+1]);
                    cal=temp.F.val();
                    if(s.find(cal)==s.end()){
                        s.insert({cal,temp.S});
                        q.push(temp);
                    }
                    swap(temp.F.a[i][j],temp.F.a[i][j+1]);
                }
            }
        }
    }
    while(t--){
        m.in();
        cal=m.val();
        if(s.find(cal)==s.end())printf("-1\n");
        else printf("%d\n",s[cal]);
    }
}
