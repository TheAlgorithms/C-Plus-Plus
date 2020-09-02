/**
 * @file
 * @brief Horspool's algorithm that finds if a string contains a substring (https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore%E2%80%93Horspool_algorithm)
 * @author [Harry Kontakis] (https://github.com/ckontakis)
 */

#include <iostream>
#include <unordered_map>
#include <cassert>

/**
 * A function that finds the shift table of the given prototype string that we need in Horpool's algorithm
 * @param prototype
 * @return Shift Table of Horspool's algorithm
 */
std::unordered_map<char, int> findShiftTable(const std::string &prototype){
    std::unordered_map<char,int> shiftTable; // A HashMap for shift table that has characters for keys and integers for values

    for(int i=0;i<prototype.size();i++){ // Checking all characters of prototype string
        if(shiftTable.find(prototype[i]) == shiftTable.end()){ // If character does not exist in HashMap
            if(i!=prototype.size()-1){
                shiftTable.insert(std::make_pair(prototype[i], prototype.size()-i-1)); // Insert the character as key and the size of prototype string - index of character - 1 as value
            }else{
                shiftTable.insert(std::make_pair(prototype[i], prototype.size())); // Insert the character as key and the size of prototype string as value
            }
        }else{
            if(i != prototype.size()-1) {
                shiftTable[prototype[i]] = prototype.size() - i - 1;
            }
        }
    }
    return shiftTable;
}

/**
 * A function that implements Horspool's algorithm
 * @param text
 * @param prototype
 * @returns true if text string contains prototype string
 * @returns false if text string does not contain prototype string
 */
bool horspool(const std::string &text, const std::string &prototype){
    std::unordered_map<char, int> shiftTable = findShiftTable(prototype); // Initialise shift table calling findShiftTable function

    int i=prototype.size()-1; // Index that we shift in text to find the substring
    while(i<text.size()){
        int j=i,k=0;
        bool flag=true;

        for(int z=prototype.size()-1;z>=0 && flag;z--){ // Checking if all characters of substring are equal with all characters of string
            if(text[j] == prototype[z]){
                k++;
                j--;
            }else{
                flag = false; // If two characters are not equal set flag to false and break from loop
            }
        }

        if(k == prototype.size()){ // If all characters match then return true
            return true;
        }else{
            if(shiftTable.find(text[i]) != shiftTable.end()){
                i += shiftTable[text[i]]; // If shift table contains the character then shift index as many steps as value
            }else{
                i += prototype.size(); // If character does not exist in shift table then shift index as many steps as size of prototype string
            }
        }
    }
    return false;
}

/**
 * Main Function that contains test cases
 */
int main(){
    assert(horspool("Hello World","World") == true);
    assert(horspool("Hello World"," World") == true);
    assert(horspool("Hello World","ello") == true);
    assert(horspool("Hello World","rld") == true);
    assert(horspool("Hello","Helo") == false);
    assert(horspool("c++_algorithms","c++_algorithms") == true);
    assert(horspool("c++_algorithms","c++_") == true);
    assert(horspool("Hello","Hello World") == false);
    assert(horspool("c++_algorithms","") == false);
    assert(horspool("c++","c") == true);
    assert(horspool("3458934793","4793") == true);
    assert(horspool("3458934793","123") == false);
    return 0;
}