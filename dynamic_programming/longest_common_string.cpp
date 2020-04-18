#include <iosrteam>
using namespace std;

int max(int a,int b)
{
    return (a > b) ? a : b;
}

int main()
{
    char str1[]="DEFBCD";
    char str2[]="ABDEFJ";
    int i,j,k;
    int n=strlen(str1)+1;
    int m=strlen(str2)+1;
    //cout<<n<<" "<<m<<"\n";
    int a[m][n];

    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==0 || j==0)
                a[i][j]=0;

            else if(str1[i-1] == str2[j-1])
                    a[i][j]=a[i-1][j-1]+1;

            else
                a[i][j]=0;
        }
    }


/*for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            cout<<a[i][j]<<" ";
        cout<<"\n";
    }*/


int ma=-1;
int indi,indj;
for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i][j]>ma)
            {
                ma=a[i][j];
                indi=i;
                indj=j;
            }
        }
    }

    cout<<str1<<"\n";
    cout<<str2<<"\n";

    cout<<"longest string size = "<<ma/*<<" "<<indi<<" "<<indj*/<<"\n";
    for(i=indi-3;i<indi;i++)
        cout<<str1[i];
    cout<<"\n";
}
