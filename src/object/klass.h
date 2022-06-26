//
// Created by sunjinlong01 on 2022/6/23.
//
#ifndef PYTHON_KLASS_H
#define PYTHON_KLASS_H

class PyObject;
class PyString;

class Klass{
private:
    PyString * _name;
public:

    // 属性
    void set_name(PyString * name){_name = name;};
    PyString * name(){ return _name;};
    // 功能
    virtual void print(PyObject * x){};
    // 运算
    virtual PyObject* less(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* less_equal(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* equal(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* not_equal(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* greater(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* greater_equal(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* add(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* sub(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* mul(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* div(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* mod(PyObject * x, PyObject * y){return 0;};
};

#endif //PYTHON_KLASS_H
