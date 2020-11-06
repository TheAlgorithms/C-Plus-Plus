#include <iostream>
using namespace std;

void merge(int a[], int b[], int m, int n)
{
    int i = 0, j = 0;
    while(i < m && j < n)
    {
        if(a[i] < b[j])
           cout << a[i++] << " ";
        else 
           cout << b[j++] << " ";
    }

    while(i < m)
       cout << a[i++] << " ";
    
    while(j < n)
       cout << b[j++] << " ";
}

int main()
{
    int m,n;
    cout << "Enter the size of two arrays" << endl;
    cin >> m >> n;
    int a[m],b[n];
    cout << "Enter the elements of first array" << endl;
    for(int i = 0;i < m;i++)
       cin >> a[i];
    
    cout << "Enter the elements of second array" << endl;
    for(int i = 0;i < n;i++)
       cin >> b[i];

    merge(a,b,m,n);
    return 0;

}
