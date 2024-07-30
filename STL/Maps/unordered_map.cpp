#include <unordered_map>
#include <iostream>
using namespace std;
int main()
{
    /*maps and  unordered maps are alomost same with little difference.
    //1->inbuild implimentation:-it use hash table 
    //2->Time complexcity:- O(1)
    //3->valid keys ki datatype:-Koi bhi complex datatypes nahi daal sakte hai bas basic datatypes use kar sakte hai e.g int, double ,string etc. jinke internally hash funtion defined hote hai.
    // we can't put complex data type inside unorded map.because the unordered map implimented internally with hash and maps are implimented using red black tree data structure*/
    unordered_map<int, int> m;
    m[9] = 43;
    m[0] = 92;
    m[3] = 23;
    m[2] = 89;
    for (auto &x : m)
        cout << x.first << " " << x.second << endl;
}