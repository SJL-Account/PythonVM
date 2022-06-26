//
// Created by sunjinlong01 on 2022/6/5.
//

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <vector>

#ifndef PYTHON_BITMAP_H
#define PYTHON_BITMAP_H

int BIT_VALUE [32] = {0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020,
                      0x00000040, 0x00000080, 0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000,
                      0x00008000, 0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000, 0x00800000,
                      0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000};

class BitMap{

public:


    std::vector<int> * bitmap;
    BitMap(long length);
    void setN(long n);
    bool existN(long n);

};


BitMap::BitMap(long length){

    int n = (int) (length >> 5) + ((length & 31) > 0 ? 1 : 0);

    std::vector<int>* bitmap =new std::vector<int>(n, 0);

};

void BitMap::setN(long n){

    int idx = (int) n >> 5;
    int offset = (int) n & 31;
    std::cout<<idx<<offset<<std::endl;
    bitmap + |= BIT_VALUE[offset];

};

bool BitMap::existN(long n){

    int idx = (int) n >> 5;
    int offset = (int) n & 31;
    //int crt_bits = (int) (&bitmap[idx]);

    //return ((unsigned)(crt_bits & BIT_VALUE[offset])) >> offset;
    return false;
};

#endif //PYTHON_BITMAP_H
