#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	int heap[n],k,a,temp,x,b,c;
	int i=0;
	while(i<n){
		cin>>x;
		heap[i] = x;
		a = i;
		k = (a-1)/2;
		while(a != 0 && heap[k] < heap[a]){
			temp = heap[a];
			heap[a] = heap[k];
			heap[k] = temp;
			a = k;
			k = (a-1)/2;
		}
	i++;
	}
	cout<<"After Inserion"<<endl;
	for(int i = 0;i < n;i++){
		cout<<heap[i]<<" ";
	}
	i=0;
	k=n-1;
	while(k>0){
		i=0;
		temp=heap[i];
		heap[i]=heap[k];
		heap[k]=temp;
		k--;
		while(1){
			a=(2*i)+1;
			b=(2*i)+2;
			if(a<=k && b<=k){
				c=(heap[a]>heap[b] ? a:b);
				if(heap[c]>heap[i]){
					temp=heap[i];
					heap[i]= heap[c];
					heap[c]=temp;
					i=c;
				}
				else{
					break;
				}
			}
			else if(a<=k){
				if(heap[a]>heap[i]){
					temp=heap[a];
					heap[a]=heap[i];
					heap[i]=temp;
					i=a;
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		}
	}
	cout<<"\n"<<"Ater Heap Sort"<<endl;
	for(int i = 0;i < n;i++){
		cout<<heap[i]<<" ";
	}
}
