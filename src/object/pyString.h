//
// Created by sunjinlong01 on 2022/6/7.
//
#include <stdlib.h>
#include "src/object/pyObject.h"
#ifndef PYTHON_PYSTRING_H
#define PYTHON_PYSTRING_H

class StringKlass: public Klass{
private:
    StringKlass();
    static StringKlass * instance;
public:
    static Klass* get_instance();
    // 功能
    virtual void init();
    virtual void print(PyObject * x);
    // 运算
    virtual PyObject* len(PyObject * x);
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


class PyString: public PyObject{

private:
    int _length;
    char * _value;
public:
    //构造
    PyString(const char * s);
    PyString(const char * s, int length);
    // 属性
    int length () {return _length; };
    char * value() {return _value; };
    void set_klass(Klass* k){_klass = k;};
    Klass * klass(){assert(_klass == NULL); return _klass;}
    // 功能
    void print ();
    PyObject * len();
    // 运算
    PyObject * add(PyObject * x);
    PyObject * equal(PyObject * x) ;

//    PyObject * sub(PyObject * x);
//    PyObject * mul(PyObject * x);
//    PyObject * div(PyObject * x);
//    PyObject * mod(PyObject * x);
//    PyObject * less(PyObject * x) ;
//    PyObject * less_equal(PyObject * x);
//    PyObject * not_equal(PyObject * x) ;
//    PyObject * greater(PyObject * x) ;
//    PyObject * greater_equal(PyObject * x);
};

#endif //PYTHON_PYSTRING_H
