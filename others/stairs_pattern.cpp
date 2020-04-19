/*
This program is use to print the following pattern
   **
   **
  ****
  ****
 ******
 ******
********
********
where number of pairs line is given by user  
*/
#include<iostream>
int main() {
int l, st = 2, x, r, z, n, sp;
std::cout << "enter Index ";
std::cin >> x;
z = x;
for (r = 1; r <= x; r++) {
z = z - 1;
for (n = 1; n <= 2; n++) {
for (sp = 1; sp <= z; sp++) {
std::cout << " ";
}
for (l = 1; l <= st; l++) {
std::cout << "*";
}
std::cout <<"\n";
}
st = st + 2;
}}
