//
// Created by sunjinlong01 on 2022/6/24.
//

#include "src/container/map.h"
#include "src/code/codeObject.h"
#include "src/object/pyObject.h"
#include "src/object/klass.h"

#ifndef PYTHON_FUNCTIONOBJECT_H
#define PYTHON_FUNCTIONOBJECT_H

PyObject * len(ArrayList<PyObject*>* args);

/*---------------- Native方法 ----------------*/
class NativeFunctionKlass: public Klass {
private:
    NativeFunctionKlass();
    static NativeFunctionKlass *instance;
public:
    static Klass *get_instance();
};

class NativeFunctionObject :public PyObject{

public:
    NativeFunctionObject();
};
/*---------------- Native方法 ----------------*/

/*typedef int integer_t;     //整型类型
typedef int *pointer_t;     //整型指针类型
typedef int array_t [5]; //整型数组类型
typedef int *p_array_t [5];    //整型指针的数组的类型
typedef int (*array_pointer_t) [5]; //整型数组的指针的类型
typedef int function_t (int param);     //函数类型
typedef int *function_t (int param);    //函数类型
typedef int (*function_t) (int param); //指向函数的指针的类型*/

typedef PyObject * (* NativeFuncPtr)(ArrayList<PyObject*>* args);


/*---------------- 函数 ----------------*/
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
    // native 函数指针
    NativeFuncPtr _nf_ptr;
    // 构造
    FunctionObject();
    FunctionObject(PyObject * x);
    FunctionObject(NativeFuncPtr nf_ptr);
    // 属性
    void set_global(Map<PyObject*, PyObject *> * x ){_global = x;};
    void set_default(ArrayList<PyObject *> * x){_default = x;};
    Map<PyObject*, PyObject *> * global(){return _global;}
    ArrayList<PyObject *>  * get_default(){return _default;}
    // 功能
    PyObject * call(ArrayList<PyObject*>* args){
        return (*_nf_ptr)(args);
    };


};
/*---------------- 函数 ----------------*/


/*---------------- 方法 ----------------*/
class MethodKlass: public Klass {
private:
    MethodKlass();
    static MethodKlass *instance;
public:
    static Klass *get_instance();
};

class MethodObject :public PyObject{

public:
    MethodObject(FunctionObject * func, PyObject* owner);
    PyObject * _owner;
    void set_owner(PyObject * x){_owner=x;};
    PyObject * owner();
};
/*---------------- 方法 ----------------*/


#endif //PYTHON_FUNCTIONOBJECT_H
