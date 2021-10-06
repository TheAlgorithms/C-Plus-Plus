/*
 * @vernam_cipher
 * @code for Vernam cipher in cryptography
 * @details
 * This contains the code for Vernam cipher both encryption and decryption. The user will input the key and message.
 * @author Ananya (https://github.com/Ananya322)
 */

#include <iostream>
using namespace std;
class vernam
{
public:
    string k;
    vernam(string b)
    {

        k = b;
    }
    void encrypt(string s)
    {
        int i, j;
        int mod = k.size();
        j = 0;
        for (i = k.size(); i < s.size(); i++)
        {
            k += k[j % mod];
            j++;
        }
        string ans = "";
        for (i = 0; i < s.size(); i++)
        {
            ans += (k[i] - 'A' + s[i] - 'A') % 26 + 'A';
        }
        cout << ans;
    }
    void decrypt(string s)
    {
        int i, j = 0;
        int mod = k.size();
        for (i = k.size(); i < s.size(); i++)
        {
            k += k[j % mod];
            j++;
        }
        string ans = "";
        for (i = 0; i < s.size(); i++)
        {
            ans += (s[i] - k[i] + 26) % 26 + 'A';
        }
        cout << ans;
    }
};

int main()
{
    string s, k;
    cout << "Enter 1 for encrytion\n2 for Decryption: ";
    int ch;
    cin >> ch;
    cout << "Enter the Key: " << endl;
    cin >> k;
    vernam v(k);
    if (ch == 1)
    {
        cout << "Enter the Plain Text Message: " << endl;
        cin >> s;
        cout << "Encrypted Message : ";
        v.encrypt(s);
        cout << endl;
    }
    else
    {
        cout << "Enter the cipher text: ";
        string ci;
        cin >> ci;
        cout << "Decrypted Message : ";
        v.decrypt(ci);
        cout << endl;
    }
    return 0;
}
