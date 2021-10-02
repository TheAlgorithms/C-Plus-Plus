#include <iostream>
using namespace std;

void result()
{
    int x,y;
    cin>>x>>y;
    int sum = x+y;
    
    if(sum%2 == 0){
        cout<<"YES"<<"\n";
    }
    else{
        cout<<"NO"<<"\n";
    }
    return;
}




int main() {
	
	int t;
	cin>>t;
	
	while(t--){
	    result();
	}
	return 0;
}