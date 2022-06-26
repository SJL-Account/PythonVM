//
// Created by sunjinlong01 on 2022/6/17.
//
#include "src/object/pyObject.h"

#ifndef PYTHON_GENESIS_H
#define PYTHON_GENESIS_H

class Universal{

public:
    static PyObject * PyTrue;
    static PyObject * PyFalse;
    static PyObject * PyNone;

    static void genesis();
    static void destroy();
};

#endif //PYTHON_GENESIS_H
