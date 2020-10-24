#include<bits/stdc++.h>
using namespace std;

int main(){

int array[10] = {8 , 9, 7, 1, 6, 5, 4, 3, 2, 0};
int n = sizeof(array) / sizeof(array[0]);

//inbuild sorting function in cpp
//first parameter is array name, second parameter is array name + array size
sort(array, array+n);

return 0;
}
