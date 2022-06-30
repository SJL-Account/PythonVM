//
// Created by sunjinlong01 on 2022/6/24.
//

#include "src/container/map.h"
#include "src/code/codeObject.h"
#include "src/object/pyObject.h"
#include "src/object/klass.h"

#ifndef PYTHON_FUNCTIONOBJECT_H
#define PYTHON_FUNCTIONOBJECT_H

class FunctionKlass: public Klass {
private:
    FunctionKlass();
    static FunctionKlass *instance;
public:
    static Klass *get_instance();
};

class FunctionObject:public PyObject{

public:
    // 局部变量表
    Map<PyObject *, PyObject *> * _local;
    // 全局变量表
    Map<PyObject *, PyObject *> * _global;
    // 内建变量表
    Map<PyObject *, PyObject *> * _build;
    // 参数表
    ArrayList<PyObject *> * _fast;
    // 默认参数表
    ArrayList<PyObject *> * _default;
    // 函数的code对象
    CodeObject * _func_code;
    // 函数名
    PyString * _func_name;
    // 函数标记位
    int _func_flag;
    // 构造
    FunctionObject();
    FunctionObject(PyObject * x);
    // 属性
    void set_global(Map<PyObject*, PyObject *> * x ){_global = x;};
    void set_default(ArrayList<PyObject *> * x){_default = x;};
    Map<PyObject*, PyObject *> * global(){return _global;}
    ArrayList<PyObject *>  * get_default(){return _default;}


};


class MethodKlass: public Klass {
private:
    MethodKlass();
    static MethodKlass *instance;
public:
    static Klass *get_instance();
};

class MethodObject :public FunctionObject{

public:
    PyObject * _owner;
    void set_owner(PyObject * x){_owner=x;};
    PyObject * owner();
};


#endif //PYTHON_FUNCTIONOBJECT_H
