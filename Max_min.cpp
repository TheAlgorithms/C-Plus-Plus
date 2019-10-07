#include<iostream.h>
void main(){
int arr[10], max, min,i;
cout<<"Enter 10 elements in the array";
for(i=0;i<10;i++){
cin>>arr[i];
}

max = arr[0];
min = arr[0];

for(i=1;i<10;i++){
if(max<arr[i]){
  max = arr[i]; 
  }
else if (min> arr[i]){
  min = arr[i];
}
}

cout<<" Maximum value in the array is "<<max;
cout<<" Minimum value in the array is "<<min;


}
