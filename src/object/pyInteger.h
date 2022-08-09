//
// Created by sunjinlong01 on 2022/6/7.
//
#ifndef PYTHON_PYINTEGER_H
#define PYTHON_PYINTEGER_H

#include <stdio.h>
#include "src/object/pyObject.h"
#include "src/object/klass.h"
#include "src/runtime/universal.h"

class IntegerKlass: public Klass{
private:
    IntegerKlass();
    static IntegerKlass * instance;
public:
    static Klass* get_instance();
    virtual void init();
    virtual void print(PyObject * x);
    virtual PyObject* less(PyObject * x, PyObject * y);
    virtual PyObject* less_equal(PyObject * x, PyObject * y);
    virtual PyObject* equal(PyObject * x, PyObject * y);
    virtual PyObject* not_equal(PyObject * x, PyObject * y);
    virtual PyObject* greater(PyObject * x, PyObject * y);
    virtual PyObject* greater_equal(PyObject * x, PyObject * y);
    virtual PyObject* add(PyObject * x, PyObject * y);
    virtual PyObject* sub(PyObject * x, PyObject * y);
    virtual PyObject* mul(PyObject * x, PyObject * y);
    virtual PyObject* div(PyObject * x, PyObject * y);
    virtual PyObject* mod(PyObject * x, PyObject * y);
};


class PyInteger: public PyObject{

public:
    int _value;
    PyInteger(int value);
    void print ();
    PyObject * len();
    PyObject * add(PyObject * x);
    PyObject * sub(PyObject * x);
    PyObject * mul(PyObject * x);
    PyObject * div(PyObject * x);
    PyObject * mod(PyObject * x);
    PyObject * less(PyObject * x) ;
    PyObject * less_equal(PyObject * x);
    PyObject * equal(PyObject * x) ;
    PyObject * not_equal(PyObject * x) ;
    PyObject * greater(PyObject * x) ;
    PyObject * greater_equal(PyObject * x);
};

#endif //PYTHON_PYINTEGER_H
