//Returns the sorted vector after performing SlowSort//
//This algorithm works on multiply and surrender principle



void SlowSort(int a[], int i, int j)
{
  if(i>=j)
    return;
  int m=i+(j-i)/2;
  int temp;
  SlowSort(a, i, m);
  SlowSort(a, m + 1, j);
  if(a[j]<a[m])
  {
    temp=a[j];
    a[j]=a[m];
    a[m]=temp;
  }
  SlowSort(a, i, j - 1);
}

//Sample Programme
int main() {

  int n;
  cin >> n;
  int arr[n];

  for(int i=0;i<n;i++)
  {
    cin >> arr[i];
  }

 SlowSort(arr,0,n-1);

  for(int i=0;i<n;i++)
  {
    cout << arr[i] << " ";
  }

  return 0;
}
