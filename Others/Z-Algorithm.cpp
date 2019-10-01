
//Logic = https://cp-algorithms.com/string/z-function.html

vector<int> z_function(string &str)
{
    int n=str.size();
    vector<int> z(n);
    for(int i=1,l=0,r=0;i<n;i++)
    {
        if(i<=r)
            z[i]=min(r-i+1, z[i-l]);
        while(i+z[i]<n && str[z[i]]==str[i+z[i]])
            z[i]++;
        if(i+z[i]-1>r)
            l=i, r=i+z[i]-1;
    }
    return z;
}