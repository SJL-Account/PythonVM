//
// Created by sunjinlong01 on 2022/6/7.
//

#include <cassert>
#include <stdlib.h>
#include "src/object/klass.h"

#ifndef PYTHON_PYOBJECT_H
#define PYTHON_PYOBJECT_H

/*
 * 顶级对象：定义了对应字节码的相应功能和对象通用的功能操作
 *
 * */
class PyObject{
public:

    // 属性
    Klass * _klass;
    void set_klass(Klass* k){_klass = k;};
    Klass * klass(){assert(_klass == NULL); return _klass;}
    // 功能
    // 字节码 PRINT
    void print();
    // 字节码 LOAD_ATTR
    PyObject * get_attr(PyObject * attr);
    void set_attr(PyObject * owner, PyObject * attr);
    // 属性
    PyObject * len();
    bool is_function();
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
    PyObject * iter();
};

#endif //PYTHON_PYOBJECT_H
