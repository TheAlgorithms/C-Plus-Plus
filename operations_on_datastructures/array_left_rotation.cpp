#include <iostream>
using namespace std;
int GCD(int a,int b)
{
    if(a==0)
        return b;
    return GCD(b%a,a);
}
int main() {
    int n, k;
    cout << "Enter size of array=\t";
    cin >> n;
    cout << "Enter Number of indices u want to rotate the array to left=\t";
    cin >> k;
    int a[n];
    cout << "Enter  elements of array=\t";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if(k==0)
         k=n;
     int gcd= GCD(k%n,n);
     int l,temp;
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

