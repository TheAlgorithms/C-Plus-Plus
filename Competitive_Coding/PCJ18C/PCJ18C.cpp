#include<iostream>

using namespace std;

int main(void)
{
    int T;
    cin>>T;
    for(int i=0;i<T;++i)
    {
        int N;
        int K;
        long A;
        cin>>N>>A>>K;
        long X;
        int Y;
        X=A*N*(N-1)+(K-1)*(360*(N-2)-2*A*N);
        Y=N*(N-1);
        for(int j=N*(N-1);j>0;--j)
        {
            if(X%j==0&&Y%j==0)
            {
                long Z;
                int W;
                Z=X/j;
                W=Y/j;
		cout<<Z<<endl<<W;
                break;
            }

        }
    }
    return 0;
}

