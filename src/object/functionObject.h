//
// Created by sunjinlong01 on 2022/6/24.
//


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
    // 函数的code对象
    CodeObject * _func_code;
    // 函数名
    PyString * _func_name;
    // 函数标记位
    int _func_flag;
    // 构造
    FunctionObject();
    FunctionObject(PyObject * x);

};



#endif //PYTHON_FUNCTIONOBJECT_H
