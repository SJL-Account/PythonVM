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
    PyObject* next(PyObject * x) override;

};

class PyIter: public PyObject {

public:
    PyObject * iter_obj;
    int iter_cnt{};
    explicit PyIter(PyObject * iter_obj);

};

#endif //PYTHON_PYITER_H
