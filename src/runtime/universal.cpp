//
// Created by sunjinlong01 on 2022/6/17.
//
#include <stdlib.h>
#include "src/object/pyObject.h"
#include "src/object/pyInteger.h"
#include "src/object/pyString.h"
#include "src/object/functionObject.h"
#include "src/object/pyDict.h"
#include "src/runtime/universal.h"

PyObject * Universal::PyTrue = NULL;
PyObject * Universal::PyFalse = NULL;
PyObject * Universal::PyNone = NULL;


PyObject * upper(ArrayList<PyObject* > * args){

    PyString * str_obj =  (PyString * )(args->get(0));
    assert(str_obj->_klass == StringKlass::get_instance());
    for (int i=0; i<str_obj->length(); i++){
        if (str_obj->value()[i] >= 97 && str_obj->value()[i] < 97 + 26){
            str_obj->value()[i] = (str_obj->value()[i] - 32);
        }
    }
    return Universal::PyNone;
}


void Universal::genesis() {

    PyTrue = new PyInteger(1);
    PyFalse = new PyInteger(0);
    PyNone = new PyObject();

    PyDict* attr_dict = new PyDict();
    // 注册方法
    attr_dict->put(new PyString("upper"), new FunctionObject(upper));
    StringKlass::get_instance()->set_attr_dict(attr_dict);

}

void  Universal::destroy() {

    delete PyTrue;
    delete PyFalse;
    delete PyNone;

}
