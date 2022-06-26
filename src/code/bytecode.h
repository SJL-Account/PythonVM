//
// Created by sunjinlong01 on 2022/6/16.
//

#ifndef PYTHON_BYTECODE_H
#define PYTHON_BYTECODE_H

class ByteCode{

public:

    static const unsigned char POP_TOP = 1;
    static const unsigned char BINANY_ADD = 23;
    static const unsigned char PRINT_ITEM = 71;
    static const unsigned char PRINT_NEW_LINE = 72;
    static const unsigned char BREAK_LOOP = 80;
    static const unsigned char RETURN_VALUE = 83;
    static const unsigned char POP_BLOCK = 87;
    static const unsigned char HAVE_ARG = 90;
    static const unsigned char STORE_NAME = 90;
    static const unsigned char LOAD_CONST = 100;
    static const unsigned char LOAD_NAME = 101;
    static const unsigned char COMPARE_OP = 107;
    static const unsigned char JUMP_FORWARD = 110;
    static const unsigned char SETUP_LOOP = 120;
    static const unsigned char JUMP_ABSOLUTE = 113;
    static const unsigned char POP_JUMP_IF_FALSE = 114;
    static const unsigned char CALL_FUNCTION = 131;
    static const unsigned char MAKE_FUNCTION = 132;
};

enum COMPAREOP{
    LESS, LESS_EQUAL, EQUAL, NOT_EQUAL, GREATER, GREATER_EQUAL
};

#endif //PYTHON_BYTECODE_H
