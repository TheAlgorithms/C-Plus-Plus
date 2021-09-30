#include<iostream>
using namespace std;
int main(){
    string name;
    int c;
    int i=0;
    int small=0,large=0;
    do{
        c=getchar();
        name[i]=c;
        i++;
    }while(c!='\n');
    for(int k=0;k<i-1;k++){
        if(name[k]>='A'&&name[k]<='Z')
        large++;
        else
        small++;
    }
    for(int h=0;h<i-1;h++){
        if(large>small){
            name[h]=toupper(name[h]);
        }
        else{
            name[h]=tolower(name[h]);
        }
        cout<<name[h];
    }
    
}