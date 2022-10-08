// Add Strings
// Example 1:

// Input: num1 = "11", num2 = "123"
// Output: "134"
// Example 2:

// Input: num1 = "456", num2 = "77"
// Output: "533"
// Example 3:

// Input: num1 = "0", num2 = "0"
// Output: "0"
// approach first take last character of string
// then see the conditions of l1 and l2
// if we subtract 0 ascii code vlaue that is 48 then we will get the numbers ascii value then for again ocnverting ionto char just add +48
// at the last we just reverse the string bcoz we are peroforming operations from back
// last if(c) is cutial as left over carry are added by that only

// time complexity  - O(n)
// space complexity - O(1)




class Solution {
public:
    string addStrings(string num1, string num2) {
        int l1=num1.length()-1;
        int l2=num2.length()-1;
        char a;
        int c=0;
        string arr;
        while(l1>=0 || l2>=0){
            if(l1<0){
               a= (num2[l2]-48+c)%10+48;
                c=(c+num2[l2]-48)/10;   
                arr.push_back(a);
                l2--;
            
            }
            else if(l2<0){
                 a= (num1[l1]-48+c)%10+48;
        // speciallyy do not fortgot to add +c in the c by this its value is added
                c=(c+num1[l1]-48)/10;   
                arr.push_back(a);
                l1--;
                
            }
            else{
                a=(num1[l1]-48+num2[l2]-48+c)%10+48;
                c=(c+num1[l1]-48+num2[l2]-48)/10;
                arr.push_back(a);
                l1--;
                l2--;
                
            }
        }
        if(c){
            arr.push_back(c+48);
            
        }
        reverse(arr.begin(),arr.end());
        return arr;
        
        
    }
};