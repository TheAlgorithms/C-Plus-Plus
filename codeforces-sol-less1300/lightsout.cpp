#include<iostream>
using namespace std;
int main(){
    int bulbs[3][3];
    int db[3][3]={1,1,1,1,1,1,1,1,1};
    int i;
    int j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            cin>>bulbs[i][j];
            bulbs[i][j];
        }
    }
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(bulbs[i][j]%2==0&&bulbs[i][j]!=0){
                if(db[i][j]==1)
                db[i][j]=1;
                else
                db[i][j]=0;
                if(i+1<=2){
                if(db[i+1][j]==1)
                db[i+1][j]=1;
                else
                db[i+1][j]=0;
                }
                if(j+1<=2){
                if(db[i][j+1]==1)
                db[i][j+1]=1;
                else
                db[i][j+1]=0;
                }
                if(i-1>=0){
                if(db[i-1][j]==1)
                db[i-1][j]=1;
                else
                db[i-1][j]=0;
                }
                if(j-1>=0){
                if(db[i][j-1]==1)
                db[i][j-1]=1;
                else
                db[i][j-1]=0;
                }

            }
            if(bulbs[i][j]%2!=0){
                if(db[i][j]==1)
                db[i][j]=0;
                else
                db[i][j]=1;
                if(i+1<=2){
                if(db[i+1][j]==1)
                db[i+1][j]=0;
                else
                db[i+1][j]=1;
                }
                if(j+1<=2){
                if(db[i][j+1]==1)
                db[i][j+1]=0;
                else
                db[i][j+1]=1;
                }
                if(i-1>=0){
                if(db[i-1][j]==1)
                db[i-1][j]=0;
                else
                db[i-1][j]=1;
                }
                if(j-1>=0){
                if(db[i][j-1]==1)
                db[i][j-1]=0;
                else
                db[i][j-1]=1;
                }
            }
        }
    }
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            cout<<db[i][j];
        }
        cout<<endl;
    }

}