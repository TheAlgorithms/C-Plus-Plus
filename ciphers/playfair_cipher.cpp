/*
 * @playfair_cipher
 * @code for Playfair cipher in cryptography
 * @details
 * This contains the code for playfair cipher both encryption and decryption. The user will input the key and message.
 * @author Ananya (https://github.com/Ananya322)
 */
 
#include <iostream>
#include <string>
using namespace std;
class playfair
{
public:
    string msg;
    char n[5][5];
    void play(string k, string t, bool m, bool e)
    {
        createEncoder(k, m);
        getText(t, m, e);
        if (e)
            play(1);
        else
            play(-1);
        print();
    }

private:
    void play(int dir)
    {
        int j, k, p, q;
        string nmsg;
        for (string::const_iterator it = msg.begin(); it != msg.end(); it++)
        {
            if (getPos(*it++, j, k))
                if (getPos(*it, p, q))
                {
                    //for same row
                    if (j == p)
                    {
                        nmsg += getChar(j, k + dir);
                        nmsg += getChar(p, q + dir);
                    }
                    //for same column
                    else if (k == q)
                    {
                        nmsg += getChar(j + dir, k);
                        nmsg += getChar(p + dir, q);
                    }
                    else
                    {
                        nmsg += getChar(p, k);
                        nmsg += getChar(j, q);
                    }
                }
        }
        msg = nmsg;
    }
    void print()
    {
        cout
            << "\n\nSolution:" << endl;
        string::iterator it = msg.begin();
        int count = 0;
        while (it != msg.end())
        {
            cout << *it;
            it++;
            cout << *it << " ";
            it++;
            if (++count >= 26)
                cout << endl;
            count = 0;
        }
        cout << endl
             << endl;
    }
    char getChar(int a, int b)
    { //get the characters
        return n[(b + 5) % 5][(a + 5) % 5];
    }
    bool getPos(char l, int &c, int &d)
    { //get the position
        for (int y = 0; y < 5; y++)
            for (int x = 0; x < 5; x++)
                if (n[y][x] == l)
                {
                    c = x;
                    d = y;
                    return true;
                }
        return false;
    }
    
    //get message
    
    void getText(string t, bool m, bool e)
    { //get the original message
        for (string::iterator it = t.begin(); it != t.end(); it++)
        {
            //to choose J = I or no Q in the alphabet.
            *it = toupper(*it);
            if (*it < 65 || *it > 90)
                continue;
            if (*it == 'J' && m)
                *it = 'I';
            else if (*it == 'Q' && !m)
                continue;
            msg += *it;
        }
        if (e)
        {
            string nmsg = "";
            size_t len = msg.length();
            for (size_t x = 0; x < len; x += 2)
            {
                nmsg += msg[x];
                if (x + 1 < len)
                {
                    if (msg[x] == msg[x + 1])
                        nmsg += 'X';
                    nmsg += msg[x + 1];
                }
            }
            msg = nmsg;
        }
        if (msg.length() & 1)
            msg += 'X';
    }
    //encoding
    void createEncoder(string key, bool m)
    { //creation of the key table
        if (key.length() < 1)
            key = "KEYWORD";
        key += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string s = "";
        for (string::iterator it = key.begin(); it != key.end(); it++)
        {
            *it = toupper(*it);
            if (*it < 65 || *it > 90)
                continue;
            if ((*it == 'J' && m) || (*it == 'Q' && !m))
                continue;
            if (s.find(*it) == -1)
                s += *it;
        }
        copy(s.begin(), s.end(), &n[0][0]);
    }
};
int main(int argc, char *argv[])
{
    string k, i, msg;
    bool m, c;
    cout << "Encrpty or Decypt? ";
    getline(cin, i);
    c = (i[0] == 'e' || i[0] == 'E');
    cout << "Enter a key: ";
    getline(cin, k);
    cout << "I <-> J (Y/N): ";  //I similar to J
    getline(cin, i);
    m = (i[0] == 'y' || i[0] == 'Y');
    cout << "Enter the message: ";
    getline(cin, msg);
    playfair pf;
    pf.play(k, msg, m, c);
}
