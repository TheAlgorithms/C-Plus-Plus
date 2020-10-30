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
void preprocess_strong_suffix(std::vector<int> &shift, std::vector<int> &bpos, std::string pat, int m) 
{ 
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
}   
//Preprocessing for each suffix the widest border of the whole pattern that is contained in that suffix is determined.
void preprocess_second(std::vector<int> &shift, std::vector<int> &bpos, 
                      std::string pat, int m) 
{ 
    int i, j; 
    j = bpos[0]; 
    for(i=0; i<=m; i++) 
    { 
        
        if(shift[i]==0) 
        {
            shift[i] = j;
        }
        if (i==j) 
        {
            j = bpos[j];
        }     
    } 
} 
  
/*Search for a pattern in given text using 
  Boyer Moore algorithm with Good suffix rule */
void search(std::string text, std::string pat) 
{ 
    // s is shift of the pattern with respect to text 
    int s=0, j; 
    int m = pat.length(); 
    int n = text.length(); 
  
    std::vector<int> bpos(m+1), shift(m+1); 
  
    //initialize all occurrence of shift to 0 
    for(int i=0;i<m+1;i++) 
    {
        shift[i]=0;
    }     
  
    //do preprocessing 
    preprocess_strong_suffix(shift, bpos, pat, m); 
    preprocess_second(shift, bpos, pat, m); 
  
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
    return 0; 
} 