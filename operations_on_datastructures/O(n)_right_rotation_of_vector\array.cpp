
#include <iostream>
#include<vector>
/*
Lets place place every number of the array at its desired correct position. But while doing this, we will lose the original elements.
Thus, we need to store the number being replaced in a 'temp' variable. Then, we can place the replaced number(which is stored in temp) 
at its correct position and so on, n times, where n is the length of array. We have chosen n to be the number of replacements since we 
have to shift all the elements of the array(which is n). But, there could be a problem with this method, if n % k =0 
where k = k%n (since a value of k larger than n eventually leads to a k equivalent to k%n). In this case, while picking up numbers to
be placed at the correct position, we will eventually reach the number from which we originally started. Thus, in such a case, when we
hit the original number's index again, we start the same process with the index following our starting point.
*/
//recursive funcion for GCD
int GCD(int a,int b)
{
    if(a==0)
    {
        return b;
    }
    return GCD(b%a,a);
}

/*
eg 1- say n=5,k=2
gcd(2,5)=1 (gcd=1 means all shifts an be done in one cycle)
a[0]->a[2] ; a[2]->a[4] ; a[4]->a[1] ;a[1]->a[3] ; a[3]->a[0] ;

eg 2- say n=6,k=2
gcd(2,6)=2 (gcd=2 means we need to have 2 cycles)
a[0]->a[2] ;a[2]->a[4] ;a[4]->a[0] ;

a[1]->a[3] ;a[3]->a[5] ;a[5]->a[1] ;

Note that-
the number of sub sequences are equal to the GCD of nand k. If n and k are coprime
complete process can be completed in one go as the subsequent indices are unique.

But if gcd>1 then the subsequent indices will repeat after n/gcd number of iterations,
hence we need to set our starting index in this case gcd number of times
*/

int main()
 {
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
