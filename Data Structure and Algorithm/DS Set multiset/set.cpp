#include <iostream>
#include <set>  
using namespace std;
int main()
{
	
   	set< int, less< int > > ms;
   	set < int, greater< int > >::iterator it; 
  	ms.insert( 10 );  // insert 10
   	ms.insert( 35 );  // insert 35
   	ms.insert( 10 );  // insert 10 again (allowed)
   	ms.insert(30);
   	ms.insert(40);//10 10 30 30 35 40 40 50 50 
   	ms.insert(30);
   	ms.insert(50);
   	ms.insert(40);
   	ms.insert(50);
   	ms.insert(3);
   	ms.insert(4);
   	cout<<"elements are"<<endl;
	for(it=ms.begin();it!=ms.end();it++)	      
	cout<<*it<<endl;
	
	/*cout << "There are " << ms.count( 10 )<<"10s inserted"; 
	// returns the number of entries = 10 	
	it = ms.find(35);

	if ( it != ms.end() ) // iterator not at end
	      cout << "\nelement was found";
	else
		cout<<"not found";
	
	cout<<"elements are"<<endl;
	for(it=ms.begin();it!=ms.end();it++)	      
	cout<<*it<<endl;
	multiset<int>:: iterator low,low1;
	low=ms.lower_bound(10);
	low1=ms.lower_bound(40);
	ms.erase(low,low1);
	
	cout<<"elements are"<<endl;
	for(it=ms.begin();it!=ms.end();it++)	      
	cout<<*it<<endl;*/
	return 0;
}

