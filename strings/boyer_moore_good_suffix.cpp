/**
 * \file
 * \brief The [Boyer-Moore Algorithm](Good Suffix Rule)(https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm) for
 * finding a pattern within a piece of text with complexity O(m) in processing + o(mn)(worst case)
 */
 #include <iostream> 
 #include<vector>
// preprocessing for strong good suffix rule
// A border is a substring which is both proper suffix and proper prefix. 
// bpos is border position array,  Each entry bpos[i] contains the starting index of border for suffix starting at index i in given pattern P.
// shift is an integer array,  Each entry shift[i] contain the distance pattern will shift if mismatch occur at position i-1. 

//using struct to return multiple object
struct contain{
    std::vector<int> shift;
    std::vector<int> bpos;
};
contain preprocess_strong_suffix(std::vector<int> shift, std::vector<int> bpos, std::string pat, int m) 
{ 
    contain contain1;    
    // m is the length of pattern  
    int i=m, j=m+1; 
    bpos[i] = j; 
  
    while(i>0) 
    {
        while(j<=m && pat[i-1] != pat[j-1]) 
        { 
            if (shift[j]==0) 
            {
                shift[j] = j-i;
            } 
  
            //Update the position of next border  
            j = bpos[j]; 
        } 
        /* p[i-1] matched with p[j-1], border is found. 
           store the  beginning position of border */
        i--;j--; 
        bpos[i] = j;  
    }
    contain1.shift=shift;contain1.bpos=bpos; 
    return contain1;
}   
//Preprocessing for each suffix the widest border of the whole pattern that is contained in that suffix is determined.
contain preprocess_second(std::vector<int> shift, std::vector<int> bpos, std::string pat, int m) 
{ 
    contain contain1;
    int k=0, l=0; 
    l = bpos[0]; 
    for(k=0; k<=m; k++) 
    { 
        
        if(shift[k]==0) 
        {
            shift[k] = l;
        }
        if (k==l) 
        {
            l = bpos[l];
        }     
    }
    contain1.shift=shift;contain1.bpos=bpos;
    return contain1; 
} 
  
/*Search for a pattern in given text using 
  Boyer Moore algorithm with Good suffix rule */
void search(std::string text, std::string pat) 
{ 
    // s is shift of the pattern with respect to text 
    int s=0, j; 
    int m = pat.length(); 
    int n = text.length(); 
    contain contain1;
  
    std::vector<int> bpos(m+1), shift(m+1); 
  
    //initialize all occurrence of shift to 0 
    for(int i=0;i<m+1;i++) 
    {
        shift[i]=0;
    }     
  
    //do preprocessing 
    contain1=preprocess_strong_suffix(shift, bpos, pat, m); 
    contain1=preprocess_second(contain1.shift, contain1.bpos, pat, m);
    shift=contain1.shift;
    bpos=contain1.bpos;
  
    while(s <= n-m) 
    { 
  
        j = m-1; 
  
        while(j >= 0 && pat[j] == text[s+j]) 
        { 
            j--;
        } 
  
        if (j<0) 
        { 
            std::cout<<"pattern occurs at shift = "<< s<<std::endl; 
            s += shift[0]; 
        } 
        else
        {
            s += shift[j+1];
        } 
    } 
  
} 
int main() 
{ 
    std::string text = "ABAAAABAACD"; 
    std::string pat = "ABA"; 
    search(text, pat); 
    return true; 
} 