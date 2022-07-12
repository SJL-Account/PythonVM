//
// Created by sunjinlong01 on 2022/7/12.
//
#include "src/object/pyObject.h"
#include "src/object/klass.h"
#ifndef PYTHON_PYITER_H
#define PYTHON_PYITER_H

class IterKlass: public Klass {
private:
    IterKlass();
public:
    static IterKlass * instance;
    static Klass * get_instance();
};

class PyIter: public PyObject {



};

#endif //PYTHON_PYITER_H
