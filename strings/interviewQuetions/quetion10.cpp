// Return the maximum occurring elements.
#include<bits/stdc++.h>
using namespace std;

int main(){
    string result = "Aaaabhirajjjjj";
    unordered_map<char, int> freq;
    
    // Convert all characters to lowercase and count frequency
    for(int i = 0; i < result.size(); i++){
        char lowerChar = tolower(result[i]);
        freq[lowerChar]++;
    }
    
    // Find the maximum occurring character
    char maxChar = result[0];
    int maxCount = 0;
    for(auto& pair : freq){
        if(pair.second > maxCount){
            maxCount = pair.second;
            maxChar = pair.first;
        }
    }
    
    cout << "The maximum occurring character is: " << maxChar << " with " << maxCount << " occurrences." << endl;
    return 0;
}