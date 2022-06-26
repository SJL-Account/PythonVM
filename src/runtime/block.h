//
// Created by sunjinlong01 on 2022/6/24.
//

#ifndef PYTHON_BLOCK_H
#define PYTHON_BLOCK_H

class Block{
public:
    unsigned char b_type;
    unsigned int b_target;
    int b_level;
    Block(unsigned char type, unsigned int target, int level):b_type(type), b_target(target), b_level(level){}
};

#endif //PYTHON_BLOCK_H
