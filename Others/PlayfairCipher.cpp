#include <iostream>
#include <string>
#include <vector>
#define ENGLISH_ABC "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

using namespace std;

inline pair<uint8_t, uint8_t> getCoordinate(char*code_table,const char character) {
        for (uint8_t x(0); x < 5;x++) {
                for (uint8_t y(0); y < 5;y++) {
                        if (*(code_table + (x * 5) + y) == character)
                                return make_pair(x, y);
                }
        }
}
string playfair(string str, string keyword) {

        char code_table[5][5];
        int32_t keyword_index(-1);

        string::iterator str_iter = str.begin(), keywor_iter = keyword.begin();

        while (str_iter != str.end() || keywor_iter != keyword.end())
        {
                if (str_iter != str.end()) {
                        if ((*str_iter = toupper(*str_iter)) >= 'A' && *str_iter <= 'Z')
                                str_iter++;
                        else str.erase(str_iter);
                 }
                if (keywor_iter != keyword.end()) {
                        if ((*keywor_iter = toupper(*keywor_iter)) >= 'A' && *keywor_iter <= 'Z')
                                keywor_iter++;
                        else keyword.erase(keywor_iter);
                }
        }
        if (str.length() == 0)return str;

        keyword.append(ENGLISH_ABC);
        for (uint8_t x(0); x < 5;x++) {
                for (uint8_t y(0); y < 5;y++) {
                        while (true)
                        {
                                if (keyword.find_first_of(keyword.at(++keyword_index)) == keyword_index){
                                        code_table[x][y] = keyword.at(keyword_index);
                                        break;
                                }
                        }
                }
        }

        for (string::iterator iter = str.begin() + 1; iter != str.end(); iter+= iter == str.end() - 1 ? 1 : 2) {
                if (*(iter - 1) == *iter)
                        str.insert(iter, 'x');
        }
        if (str.length() % 2 != 0) str.append("x");

        for (string::iterator iter = str.begin(); iter != str.end(); iter += 2) {
                pair<pair<uint8_t, uint8_t>, pair<uint8_t, uint8_t>> character_pair_coordinate;
                character_pair_coordinate.first = getCoordinate(&code_table[0][0], *iter);
                character_pair_coordinate.second = getCoordinate(&code_table[0][0], *(iter + 1));
                if (character_pair_coordinate.first.first == character_pair_coordinate.second.first) // x1 == x2
                {
                        *iter = (code_table[character_pair_coordinate.first.first][(character_pair_coordinate.first.second + 1) % 5]);
                        *(iter + 1) = (code_table[character_pair_coordinate.second.first][(character_pair_coordinate.second.second + 1) % 5]);
                }
                else if (character_pair_coordinate.first.second == character_pair_coordinate.second.second) //y1 == y2
                {
                        *iter = (code_table[(character_pair_coordinate.first.first + 1) % 5][character_pair_coordinate.first.second]);
                        *(iter + 1) = (code_table[(character_pair_coordinate.second.first + 1) % 5][character_pair_coordinate.second.second]);
                }
                else
                {
                        *iter = (code_table[character_pair_coordinate.first.first ][character_pair_coordinate.second.second]);
                        *(iter + 1) = (code_table[character_pair_coordinate.second.first][character_pair_coordinate.first.second]);
            }
        }

        return str;
}
int main(){
    playfair("Welcome from Hungary!","playfair"); //return the encrypted text
    return 0;
}
