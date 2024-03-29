//
// Created by sunjinlong01 on 2022/6/23.
//

#ifndef PYTHON_KLASS_H
#define PYTHON_KLASS_H
#include <stdio.h>
#include "src/container/arrayList.h"

// 上层引用底层，用声明的方式
class PyObject;
class PyString;
class PyDict;

class Klass{
private:
    PyString * _name;
    PyDict * _attr_dict;
    Klass * _super;
public:
    // 属性
    void set_super(Klass * x){_super = x; };
    void set_name(PyString * name){_name = name;};
    void set_attr_dict(PyDict* attr_dict){ _attr_dict = attr_dict;};
    PyDict * attr_dict(){return _attr_dict;};
    PyString * name(){ return _name;};
    Klass * super(){ return _super;};
    // 功能
    virtual void init(){};
    virtual void print(PyObject * x){};
    virtual PyObject* len(PyObject * x){return 0;};
    // 运算
    virtual PyObject* store_subscr(PyObject * x, PyObject * y, PyObject * z){return 0;};
    virtual PyObject* del_subscr(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* subscr(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* in(PyObject * x, PyObject * y){return 0;};
    virtual PyObject* not_in(PyObject * x, PyObject * y){return 0;};
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
    virtual PyObject* iter(PyObject * x){return 0;};

};
class ObjectKlass:Klass {
private:
    static ObjectKlass *instance;
    ObjectKlass();
public:
    static Klass *get_instance();

};

#endif //PYTHON_KLASS_H
