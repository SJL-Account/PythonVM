//
// Created by sunjinlong01 on 2022/7/7.
//
#include "src/object/pyObject.h"
#include "src/object/klass.h"
#include "src/container/arrayList.h"

#ifndef PYTHON_PYLIST_H
#define PYTHON_PYLIST_H

class ListKlass:Klass{
private:
    static ListKlass * instance;
    ListKlass();
public:
    static Klass* get_instance();
    virtual void print(PyObject * x);
    virtual PyObject* add(PyObject * x, PyObject * y);
    virtual PyObject* in(PyObject * x, PyObject * y);
    virtual PyObject* not_in(PyObject * x, PyObject * y);
    virtual PyObject* subscr(PyObject * x, PyObject * y);

};
class PyList:public PyObject{
public:
    ArrayList< PyObject* >* _list;
    PyList(int n);
    PyList(ArrayList< PyObject* > * _list);
    void insert(int index, PyObject * x){_list->insert(index, x);};
    PyObject * get(int index){return _list->get(index);};
    void set(int index, PyObject * x){_list->set(index, x);};
    int size(){return _list->size();};
    int length(){return _list->length();};
    PyObject * pop(){return _list->pop();};
    void push(PyObject * x){_list->push(x);};
};

#endif //PYTHON_PYLIST_H
