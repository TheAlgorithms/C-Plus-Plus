#include <bits/stdc++.h>
using namespace std;
unordered_map<char,char> hashMap;

string encrypt(string msg)
{
  string ciphertext;
  for(int i=0; i<msg.size(); i++)
  {
    ciphertext.push_back(hashMap[msg[i]]);
  }
  
  return ciphertext;
}

string decrypt(string msg)
{
  string plaintext;
  for(int i=0; i<msg.size(); i++)
  {
    plaintext.push_back(hashMap[msg[i]]);
  }
  
  return plaintext;
}

void hashFn(string a, string b)
{
  hashMap.clear();
  for(int i=0; i<a.size(); i++)
  {
    hashMap.insert(make_pair(a[i],b[i]));
  }
}

int main() 
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string substitution = "qwertyuiopasdfghjklzxcvbnm";
    string msg = "absdhj";
    
    hashFn(alphabet, substitution);
    
    string cipher = encrypt(msg);
    cout<<"Encrypted Cipher Text: "<<cipher<<endl;
    
    hashFn(substitution, alphabet);
    string plain = decrypt(cipher);
    cout<<"Decrypted Plain Text: "<<plain<<endl;
}
