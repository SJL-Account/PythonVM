
// Created by sunjinlong01 on 2022/6/24.


#include "src/object/functionObject.h"

FunctionKlass * FunctionKlass::instance = NULL;

Klass* FunctionKlass::get_instance(){
    if (instance == NULL){
        instance = new FunctionKlass();
    }
    return instance;
}

FunctionKlass::FunctionKlass(){

}

FunctionObject::FunctionObject(){
    _func_code = NULL;
    _func_name = NULL;
    _func_flag = 0;
    set_klass(FunctionKlass::get_instance());
}

FunctionObject::FunctionObject(PyObject * x){
    _func_code = ((CodeObject *) x);
    _func_name = _func_code->_co_name;
    _func_flag = _func_code->_flag;
    set_klass(FunctionKlass::get_instance());
}
