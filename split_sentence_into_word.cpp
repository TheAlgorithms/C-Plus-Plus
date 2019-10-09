





 /* Name :- Divyesh Srivastava
 ** Institute :- National Institute of Technology, Meghalaya
 
                    <---  Split Sentence Into Words -->
  */

#include<iostream>
using namespace std;
  
  string s;
  
     void solve()
  {
        string str;    // reference string to print all words
        
        for(auto x:s) // travellling through the sentence
        {
            if(x==' ') // If we reach the whitespace we need to print the word before it
            {
                cout<<str<<endl;
                 str.erase();
            }
            
            else
                  str=str+x; // If not a whitespace then add characters to reference string (str)
        }
        
        cout<<str;  // for last word
  }
  
  int main()
  {
       s = "Hacktober fest is on fire"; // we need to convert this sentence into Words
      
        solve();
  }

/*************  GHOSTRIDER *******************/


















