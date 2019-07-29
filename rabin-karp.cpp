#include<iostream>
using namespace std;
#include<cmath>
int main() 
{ 
    int t;
    cin >> t;
    
    while(t--){
	    string s, p;
	    cin >> s >> p;
	    int q = 101; // A prime number 
	    if(Search(p, s, q)) cout << "Yes" << endl;
	    else cout << "No" << endl;
    }
	return 0; 
} 

/* pat -> pattern  aaba
	txt -> text    aabaacaadaabaaba  
	q -> A prime number 
*/
bool Search(string pat, string txt, int q)
{

    long long int hash_pattern=0;
    long long int hash_initial=0;  //hash_initial will be the hash for the initial pat.length() of the text given

    long long int m=pat.length();
    for(long long int i=0;i<m;i++)
        hash_pattern+=pow(q,i)*pat[i];  //generating hash for the pattern : best optimised.
    
    for(long long int i=0;i<m;i++)
        hash_initial+=pow(q,i)*txt[i];
    
    if(hash_initial==hash_pattern)
    {
            if(txt.substr(0,m)==pat)
                return true;
    }
    else{
        
        for(long long int i=0;i<txt.length();i++)
        {
            hash_initial=((hash_initial-txt[i])/q)+txt[m+i]*pow(q,m-1);
            if(hash_initial==hash_pattern){
                if(txt.substr(i+1,m)==pat)
                    return true;
            }
            else
                continue;
    
        }
    }
    return false;
    
}
