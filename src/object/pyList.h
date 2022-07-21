//
// Created by sunjinlong01 on 2022/7/7.
//
#include "src/object/pyIter.h"
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
    void print(PyObject * x) override;
    PyObject* len(PyObject * x) override;
    PyObject* add(PyObject * x, PyObject * y) override;
    PyObject* in(PyObject * x, PyObject * y) override;
    PyObject* not_in(PyObject * x, PyObject * y) override;
    PyObject* store_subscr(PyObject * x, PyObject * y, PyObject * z) override;
    PyObject* del_subscr(PyObject * x, PyObject * y) override;
    PyObject* subscr(PyObject * x, PyObject * y) override;
    PyObject* iter(PyObject * x) override;


};

class PyList: public PyObject{
private:
    void register_method();
public:
    ArrayList< PyObject* >* _list;
    // 构造函数
    explicit PyList();
    explicit PyList(int n);
    explicit PyList(ArrayList< PyObject* > * _list);
    // 属性
    int size(){return _list->size();};
    int length(){return _list->length();};
    // 新增
    void insert(int index, PyObject * x){_list->insert(index, x);};
    void push(PyObject * x){_list->push(x);};
    // 修改
    void set(int index, PyObject * x){_list->set(index, x);};
    // 查找
    PyObject * get(int index){return _list->get(index);};
    // 删除
    PyObject * pop(){return _list->pop();};

};

/*---------------List Iter---------------*/

class ListIterKlass: public Klass{
private:
    static ListIterKlass * instance;
    ListIterKlass();
public:
    static Klass* get_instance();

};

class ListIter: public PyObject{
private:
    PyObject * _owner;
    int _index;
public:
    ListIter(PyObject * owner);
    PyObject * owner(){return _owner;};
    int index(){return _index;};
    void inc_index(){_index++;};

};

#endif //PYTHON_PYLIST_H
