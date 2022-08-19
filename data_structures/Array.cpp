//
// Created by Ben X on 8/10/22.
//Cherno Array
//

#include "Array.h"
#include "iostream"
#include "array"

int main(){
    int example[5];
    int*ptr = &example[0];
    std::array<int, 5> another;


    for (int i = 0; i <5; i ++)
        example[i] = 2;

    for (int i = 0; i <5; i ++)
        another[i] =3;
};