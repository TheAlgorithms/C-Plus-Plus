



#include <algorithm>
#include <iostream>
#include <list>
using namespace std;
intmain() {
//creating the list 'mlist' having integer values in it
list<int>mlist = { 10, 20, 30, 40, 50 };
//pushing the elements at the starting and last
mlist.push_back(60);
mlist.push_front(0);
//printing of the list elements after pushing
list <int> :: iterator it;
cout<< "Elements after insertion are as follows : " <<endl;
for(it = mlist.begin(); it != mlist.end(); it++)
cout<< *it  <<'\n';
//popping the elements from the last
mlist.pop_back();
//printing the list elements after pop
cout<< "Elements after deletion  are as follows : " <<endl;
for(it = mlist.begin(); it != mlist.end(); it++)
cout<< *it <<'\n';
cout<< "Elements after insertion at particular position are as follows: " <<endl;
//searching the element '10' in the list and then inserting the element before it
auto i = find(mlist.begin(), mlist.end(), 10);
if (i != mlist.end()) {
mlist.insert(i, 90);
}
//printing the elements after the new insertion
for(it = mlist.begin(); it != mlist.end(); it++)
cout<< *it  <<'\n';
}
