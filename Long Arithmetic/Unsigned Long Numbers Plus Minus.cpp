#include<iostream>
#include<vector>
#include<string>
#include<cassert>
#include<algorithm>
#include<sstream>
#include<iomanip>

using namespace std;

class UInt{
    const int BASE = 1000;      //greater BASE 
    const int BASE_LOG_10 = 3;

    static int to_int(string::iterator, string::iterator);

    vector<int> digits;
    
    bool is_zero() const;
    void erase_leading_zeroes();

    bool digit_exists(size_t) const;
    int & operator [](size_t);
    int at(size_t) const;
    
public:
    explicit UInt(long long = 0);
    UInt(string);
    UInt(const UInt &);

    operator string() const;
    const UInt & operator = (const UInt &);
    bool operator < (const UInt & ) const;
    bool operator == (const UInt & ) const;
    bool operator != (const UInt & ) const;
    UInt operator + (const UInt & ) const;
    UInt operator - (const UInt & ) const;
};

ostream & operator << (ostream & out, const UInt & to_print){
    out << (string)to_print;
    return out;
}

istream & operator >> (istream & in, UInt & to_read){
    string s;
    in >> s;
    to_read = UInt(s);
    return in;
}


int UInt::to_int(string::iterator first, string::iterator last){
    int res = 0;
    reverse(first, last);
    for(; first != last; first++)
        res *= 10,
        res += *first - '0';
    return res;
}

bool UInt::is_zero() const{
    return digits.empty();
}

void UInt::erase_leading_zeroes(){
    while(!digits.empty() && digits.back() == 0)
        digits.pop_back();
}

bool UInt::digit_exists(size_t i) const{
    return i < digits.size();
}

int & UInt::operator [](size_t i){
    if(!this->digit_exists(i))
        digits.resize(i + 1);
    return digits[i];
}
int UInt::at(size_t i) const{
    if(!this->digit_exists(i))
        return 0;
    return digits[i];
}

UInt::UInt(long long src){
    assert(src >= 0);
    for(int i = 0; src > 0; src /= BASE, i++)
        digits[i] = src % BASE;
}

UInt::UInt(string src){
    reverse(src.begin(), src.end());
    digits.assign((src.size() - 1) / BASE_LOG_10 + 1, 0); //fllor(src.size() / BASE_LOG_10)
    for(size_t i = 0; i < src.size(); i += BASE_LOG_10){
        size_t j = min(i + BASE_LOG_10, src.size());
        digits[i / BASE_LOG_10] = UInt::to_int(src.begin() + i, src.begin() + j);
    }
    
    erase_leading_zeroes();
}

UInt::UInt(const UInt & src) : digits(src.digits) {}

UInt::operator string() const{
    ostringstream ss;
    if(this->is_zero())
        ss << "0";
    else{
        ss << setfill('0');
        cout << digits.back();

        for(size_t i = digits.size(); i > 1; i--)
            ss << setw(BASE_LOG_10) << digits[i - 2];
    }
    return ss.str();
}
const UInt & UInt::operator = (const UInt & src){
    this->digits = src.digits;
    return *this;
}

bool UInt::operator < (const UInt & rhs) const {
    if(digits.size() != rhs.digits.size())
        return this->digits.size() < rhs.digits.size();
    
    for(size_t i = digits.size(); i >= 0; i--)
        if(at(i) != rhs.at(i))
            return at(i) < rhs.at(i);
    return false;
}
bool UInt::operator == (const UInt & rhs) const {
    return digits == rhs.digits;
}
bool UInt::operator != (const UInt & rhs) const {
    return digits != rhs.digits;
}

UInt UInt::operator + (const UInt & rhs) const{
    UInt res;
    int carry = 0;
    for(size_t i = 0; this->digit_exists(i) || rhs.digit_exists(i) || carry != 0; i++){
        carry += this->at(i) + rhs.at(i);
        res[i] = carry % BASE;
        carry /= BASE; 
    }
    return res;
}

UInt UInt::operator - (const UInt & rhs) const {
    assert(!(*this < rhs));

    UInt res;
    int carry = 0;
    for(size_t i = 0; this->digit_exists(i) || rhs.digit_exists(i) || carry != 0; i++){
        carry += this->at(i) - rhs.at(i);
        if(carry < 0)
            res[i] = carry + BASE,
            carry = -1;
        else 
            res[i] = carry,
            carry = 0; 
    }
    res.erase_leading_zeroes();
    return res;
}


int main(){
    UInt x = string("1234567891234567890987654321"),
         y =  string("000000209147896325987654321"); 

    UInt a = string("999999999"),
         b = string("1000000000");
    cout << (x + y) << endl 
         << (x - y) << endl;    
    cout << a + a << endl 
         << b - a << endl;
         
    // Outputs the following:
    // 1234568100382464216975308642
    // 1234567682086671565000000000
    // 1999999998
    // 1

    return 0;
}