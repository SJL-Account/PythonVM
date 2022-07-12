//
// Created by sunjinlong01 on 2022/6/7.
//

#include <cassert>
#include <stdlib.h>
#include "src/object/klass.h"

#ifndef PYTHON_PYOBJECT_H
#define PYTHON_PYOBJECT_H

class PyObject{
public:
    // 属性
    Klass * _klass;
    void set_klass(Klass* k){_klass = k;};
    Klass * klass(){assert(_klass == NULL); return _klass;}
    // 功能
    void print();
    PyObject * len();
    PyObject * get_attr(PyObject * attr);
    bool is_function();
    void set_attr(PyObject * owner, PyObject * attr);
    // 运算
    PyObject * add(PyObject * x);
    PyObject * sub(PyObject * x);
    PyObject * mul(PyObject * x);
    PyObject * div(PyObject * x);
    PyObject * mod(PyObject * x);
    PyObject * less(PyObject * x);
    PyObject * less_equal(PyObject * x);
    PyObject * equal(PyObject * x);
    PyObject * not_equal(PyObject * x);
    PyObject * greater(PyObject * x);
    PyObject * greater_equal(PyObject * x);
    PyObject * is(PyObject * x);
    PyObject * is_not(PyObject * x);
    PyObject * in(PyObject * x);
    PyObject * not_in(PyObject * x);
    PyObject * subscr(PyObject * x);
    PyObject * del_subscr(PyObject * x);
    PyObject * store_subscr(PyObject * x, PyObject* y);
    PyObject * next();
};

#endif //PYTHON_PYOBJECT_H
