#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;
class interpolition
{
	public:
		int i,j=0,j1=0,j2=0,j3=0;
		vector<int>a;
		vector<double>a1;
		vector<char>a2;
		vector<string>a3;
		void input(int n)
		{
			a[j]=n;j++;
		}
		void input(double n)
		{
			a1.push_back(n);
		}
		void input(char n)
		{
			a2.push_back(n);
		}
		void input(string n)
		{
			a3.push_back(n);
		}
		void sorting()
		{
			if(a.size()!=0)
			{sort(a.begin(),a.end());
			}
			if(a1.size()!=0)
			{sort(a1.begin(),a1.end());
			}
			if(a2.size()!=0)
			{sort(a2.begin(),a2.end());
			}
			if(a3.size()!=0)
			{sort(a3.begin(),a3.end());
			}
		}
		int binary(int x)
		{
			int s=0,l=a.size(),c=0,mid;
			do
			{
				c=0;
				mid=(l-s/(a[l]-a[s]))*(x-a[s]);
				if(a[mid]==x)
				{
					return mid;
				}
				if(a[mid]>x)
				{
					l=mid-1;
				}
				if(a[mid]<x)
				{
					s=mid+1;
				}
			}while(l<=mid);
			return -1;
		}
		int binary(double x)
		{
			int s=0,l=a.size(),c=0,mid;
			do
			{
				c++;
				mid=(l-s/(a1[l]-a1[s]))*(x-a1[s]);
				if(a1[mid]==x)
				{
					return mid;
				}
				if(a1[mid]>x)
				{
					l=mid-1;
				}
				if(a1[mid]<x)
				{
					s=mid+1;
				}
			}while(l<=mid);
			return -1;
		}
		int binary(char x)
		{
			int s=0,l=a2.size(),c=0,mid;
			do
			{
				c++;
				mid=(l-s/(a[l]-a[s]))*(x-a2[s]);
				if(a2[mid]==x)
				{
					return mid;
				}
				if(a2[mid]>x)
				{
					l=mid-1;
				}
				if(a2[mid]<x)
				{
					s=mid+1;
				}
			}while(l<=mid);
			return -1;
		}
		int binary(string st1)
		{
			int low=0,hi=a3.size()-1,pos=0,h=hi,l=low,x=hi;
			cout<<a3.size()<<endl;
			while(x<=h&&l<=pos&&l<h)
			{
			    l=(int)(a3[low].at(0));
			    h=(int)(a3[hi].at(0));
			    x=(int)(st1.at(0));
				pos=low+((hi-low)*(x-l)/(h-l));
				cout<<pos<<endl;
				if(a3[pos]==st1)
				{
					return pos;
				}
				else if(a3[pos] > st1)
				{
					hi=pos-1;
				}
				else
				{
					low=pos+1;
				}
			}
			return -1;
		}
};
int main()
{
	interpolition b;
	int ch;
	cout<<"what is the datatype of input:-\n1. int\n2. double\n3. char\n4. string"<<endl;
    cin>>ch;
    switch(ch)
    {
        case 1:
            {
                int n,m;
                do
                {
                    cout<<"enter the value to be inserted in array:-";
                    cin>>n;
                    b.input(n);
                    cout<<"do you want to add more elements? 1. yes 2. no\n";
                    cin>>m;
                }while(m!=0);
                b.sorting();
                int x;
                cout<<"enter the value to be searched in array:-";
                cin>>x;
                int k=b.binary(x);
                if(k==-1)
                {
                    cout<<x<<" is not found"<<endl;
                }
                else
                {
                    cout<<x<<" is found at "<<k<<"th location"<<endl;
                }
                break;
            }
        case 2:
            {
                double n;int m;
                do
                {
                    cout<<"enter the value to be inserted in array:-";
                    cin>>n;
                    b.input(n);
                    cout<<"do you want to add more elements? 1. yes 2. no\n";
                    cin>>m;
                }while(m!=0);
                b.sorting();
                double x;
                cout<<"enter the value to be searched in array:-";
                cin>>x;
                int k=b.binary(x);
                if(k==-1)
                {
                    cout<<x<<" is not found"<<endl;
                }
                else
                {
                    cout<<x<<" is found at "<<k<<"th location"<<endl;
                }
                break;
            }
            case 3:
            {
                char n;int m;
                do
                {
                    cout<<"enter the value to be inserted in array:-";
                    cin>>n;
                    b.input(n);
                    cout<<"do you want to add more elements? 1. yes 2. no\n";
                    cin>>m;
                }while(m!=0);
                b.sorting();
                char x;
                cout<<"enter the value to be searched in array:-";
                cin>>x;
                int k=b.binary(x);
                if(k==-1)
                {
                    cout<<x<<" is not found"<<endl;
                }
                else
                {
                    cout<<x<<" is found at "<<k<<"th location"<<endl;
                }
                break;
            }
            case 4:
            {
                string n;int m;
                do
                {
                    cout<<"enter the value to be inserted in array:-";
                    cin>>n;
                    b.input(n);
                    cout<<"do you want to add more elements? 1. yes 2. no\n";
                    cin>>m;
                }while(m!=0);
                b.sorting();
                string x;
                cout<<"enter the value to be searched in array:-";
                cin>>x;
                int k=b.binary(x);
                if(k==-1)
                {
                    cout<<x<<"is not found"<<endl;
                }
                else
                {
                    cout<<x<<" is found at "<<k<<"th location"<<endl;
                }
                break;
            }
    }
}
