/**
 * @brief [ROT13 Encoding and
 * Decoding](https://en.wikipedia.org/wiki/ROT13)
 * ROT13 ("rotate by 13 places", sometimes hyphenated ROT-13) is a simple letter substitution cipher that replaces a letter with the 13th letter after it in the alphabet. ROT13 is a special case of the Caesar cipher which was developed in ancient Rome.
 * @author [pond](https://github.com/pond-e)
 */
#include <iostream>
#include <string>

using namespace std;

string rot13_encode(string s){
    // Encode only A~Z, a~z.
    int tmp;
    for(int i = 0; i < s.length(); i++){
        if(s[i]>='A'&&s[i]<='Z'){
            tmp = s[i] - 'A';
            // Shift by 13 characters
            tmp += 13;
            tmp %= 26;
            s[i] = 'A' + tmp;
        }else if(s[i]>='a'&&s[i]<='z'){
            tmp = s[i] - 'a';
            // Shift by 13 characters
            tmp += 13;
            tmp %= 26;
            s[i] = 'a' + tmp;
        }
    }
    return s;
}

string rot13_decode(string s){
    // Decode only A~Z, a~z .
    int tmp;
    for(int i = 0; i < s.length(); i++){
        if(s[i]>='A'&&s[i]<='Z'){
            tmp = s[i] - 'A';
            // Fixed so that the value does not become negative when "-13" is set.
            tmp += 26;
            // Shift by 13 characters
            tmp -= 13;
            tmp %= 26;
            s[i] = 'A' + tmp;
        }else if(s[i]>='a'&&s[i]<='z'){
            tmp = s[i] - 'a';
            // Fixed so that the value does not become negative when "-13" is set.
            tmp += 26;
            // Shift by 13 characters
            tmp -= 13;
            tmp %= 26;
            s[i] = 'a' + tmp;
        }
    }
    return s;
}

static void test(){
    string s;
    s = "test_WOrd01";
    
    s = rot13_encode(s);
    cout << "rot13_encode:"<< s << endl;

    s = rot13_decode(s);
    cout << "rot13_decode:" << s << endl;
}

int main() {
    test();
    return 0;
}