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
    Klass * _klass;
    void set_klass(Klass* k){_klass = k;};
    Klass * klass(){assert(_klass == NULL); return _klass;}
    void print();
    PyObject * get_attr(PyObject * attr);
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
};

#endif //PYTHON_PYOBJECT_H
