#include <iostream>
#include <vector>
using namespace std;
int GCD(int a,int b)
{
    if(a==0)
    {
        return b;
    }
    return GCD(b%a,a);
}
/* this code shifts the elemet to it's desries index in one go
eg 1- say n=5,k=2
gcd(2,5)=1
a[0]->a[2] ; a[2]->a[4] ; a[4]->a[1] ;a[1]->a[3] ; a[3]->a[0] ;

eg 2- say n=6,k=2
gcd(2,6)=2
a[0]->a[2] ;a[2]->a[4] ;a[4]->a[0] ;

a[1]->a[3] ;a[3]->a[5] ;a[5]->a[1] ;
*/
int main() {
    int n=0;
    int k=0;
    int temp=0;
    cout << "Enter size of array=\t";
    cin >> n;
    cout << "Enter Number of indices u want to rotate the array to left=\t";
    cin >> k;
    vector<int> a(n);
    cout << "Enter  elements of array=\t";
    for (int i = 0; i < n; i++) {
        cin >> temp;
        a[i]=temp;
    }

    if(k==0)
    {
      k=n;
    }
    int gcd= GCD(k%n,n);
    int l=0;
    for(int i=0;i<gcd;i++)
     {
         l=(i+k)%n;
         temp=a[i];
         for(int j=0;j<n/gcd;j++)
         {
             temp+=a[l];
             a[l]=temp-a[l];
             temp=temp-a[l];
             l=(l+k)%n;
          }
      }
    cout << "Your rotated array is=\t";
    for (int j = 0; j < n; j++) {
        cout << a[j] << " ";
    }
    return 0;
}
