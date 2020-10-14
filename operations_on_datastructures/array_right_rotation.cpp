#include <iostream>
#include<vector>
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

Note that-
the number of sub sequences are equal to the GCD of nand k. If n and k are coprime 
complete process can be completed in one go as the subsequent indices are unique.

But if gcd>1 then the subsequent indices will repeat after n/gcd number of iterations,
hence we need to set our starting index in this case gcd number of times


*/
int main() {
    int n=0;
    int k=0;
    int temp=0;
    std::cout << "Enter size of array=\t";
    std::cin >> n;
    std::cout << "Enter Number of indices u want to rotate the array to right=\t";
    std::cin >> k;
    std::vector<int> a(n); // here vector is used ,BUT IT IS TREATED AS AN ARRAY 
    std::cout << "Enter elements of array=\t";
    for (int i = 0; i < n; i++)
    {
        std::cin >> temp;
        a[i]=temp;
    }
    if(k==0)
    {
      k=n; // rotating an array same number of times as its length makes no changes to the array
    }
    int gcd= GCD(k%n,n); // rotating k times and n+k times are the same
    int l=0;
    for (int i = 0; i < gcd; i++)
    {
        l=(i+k)%n; //here we set the starting element of the subsequence 
        temp=a[i]; //storing initial element of the sub sequence into temporary variable
        for (int j = 0; j<n/gcd; j++)
        {
           //we put the current element to its approptiate place ,fill the emptied place with element in temp
           //element in temp store the diaplaced
           //eg n=5, k=2 ,current element = a[2], so we put temp element into a[2],orignal a[2] element into a[4]
           //and orignal element of a[4] into temp
           temp+=a[l];
           a[l]=temp-a[l];
           temp=temp-a[l];
           l=(l+k)%n;
        }
    }
    std::cout << "Your rotated array is=\t";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
}
