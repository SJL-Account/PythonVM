
// Created by sunjinlong01 on 2022/6/24.


#include "src/object/functionObject.h"

PyObject * len(ArrayList<PyObject*> * args)
{
    return args->get(0)->len();
}

NativeFunctionKlass * NativeFunctionKlass::instance = NULL;

MethodKlass * MethodKlass::instance = NULL;

FunctionKlass * FunctionKlass::instance = NULL;

Klass* NativeFunctionKlass::get_instance(){
    if (instance == NULL){
        instance = new NativeFunctionKlass();
    }
    return instance;
}

Klass* FunctionKlass::get_instance(){
    if (instance == NULL){
        instance = new FunctionKlass();
    }
    return instance;
}

Klass* MethodKlass::get_instance(){
    if (instance == NULL){
        instance = new MethodKlass();
    }
    return instance;
}

NativeFunctionKlass::NativeFunctionKlass(){

}

MethodKlass::MethodKlass(){

}

MethodObject::MethodObject(FunctionObject * func, PyObject * owner){
    _owner = owner;
    _func = func;
    set_klass(MethodKlass::get_instance());
}

FunctionKlass::FunctionKlass(){

}

FunctionObject::FunctionObject(){
    _func_code = NULL;
    _func_name = NULL;
    _func_flag = 0;
    _global = NULL;
    set_klass(FunctionKlass::get_instance());
}

FunctionObject::FunctionObject(PyObject * x){
    _func_code = ((CodeObject *) x);
    _func_name = _func_code->_co_name;
    _func_flag = _func_code->_flag;
    _global = NULL;
    set_klass(FunctionKlass::get_instance());
}

FunctionObject::FunctionObject(NativeFuncPtr nf_ptr){
    _func_code = NULL;
    _func_name = NULL;
    _func_flag = 0;
    _global = NULL;
    _nf_ptr = nf_ptr;
    set_klass(NativeFunctionKlass::get_instance());

}
