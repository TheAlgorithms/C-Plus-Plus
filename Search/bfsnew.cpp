#include <iostream>
using namespace std;
int queue[5];
int a[5];
int root;
int L;
int R;
int front=0;
int end=0;
void BFS();
void push();
void pop();

int main()
{
	for(int i=0;i<5;i++)
	{
		cin>>a[i];
	}
	cout<<"\nPrinting in bfs order";
	BFS();
	
	return 0;
 } 
 void BFS()
 {

 	queue[0]=a[root];
 	end++;
 	while(front<5)
 	{
 		pop();
 		push();
	 }

 }
 void push()
 {
    L=2*root+1;
 	R=L+1;
	 queue[end]=a[L];
 	end++;
 	queue[end]=a[R];
 	end++;	
 }
 void pop()
 {
 	cout<<"\n"<<queue[front];
 	for(int i=0;i<5;i++)
 	{
 		if(queue[front]==a[i])
 		{
 			root=i;
		 }
	 }
	 cout<<"\n root is"<<root<<"\t a[root] "<<a[root];
 	front++;
 }
