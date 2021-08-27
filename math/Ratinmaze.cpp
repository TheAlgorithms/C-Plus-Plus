#include<iostream>
#include<vector>
using namespace std;

void ratincagewithoutreturntype(int sc,int sr,int er,int ec, string ans){
    
    if(sc==ec &&  sr==er){
        cout<<ans<<endl;
        return;
    }
    if(sc+1<=ec){
        
        ratincagewithoutreturntype(sr,sc+1,er,ec,ans+"H");

    }
    if(sr+1<=er){
        ratincagewithoutreturntype(sr,sc+1,er,ec,ans+"V");

    }
   
}
 void ratinmazewithoutreturntype(int sr,int sc,int er,int ec){
     
     ratincagewithoutreturntype(sr,sc,er,ec,"");

     }
int main(){
    int sr=0,sc=0;
    int endrow;
    cin>>endrow;
    int endcol;
    cin>>endcol;
    
    ratinmazewithoutreturntype(sr,sc,endrow,endcol);
}
