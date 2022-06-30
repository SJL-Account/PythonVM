//
// Created by sunjinlong01 on 2022/6/17.
//
#include <stdlib.h>
#include "src/object/pyObject.h"
#include "src/object/pyInteger.h"
#include "src/object/pyString.h"
#include "src/object/pyDict.h"
#include "src/runtime/universal.h"

PyObject * Universal::PyTrue = NULL;
PyObject * Universal::PyFalse = NULL;
PyObject * Universal::PyNone = NULL;

//
//static PyObject * upper(PyObject * x){
//
//}
//
//static PyObject * lower(PyObject * x){
//
//}

void Universal::genesis() {

    PyTrue = new PyInteger(1);
    PyFalse = new PyInteger(0);
    PyNone = new PyObject();

    PyDict* attr_dict = new PyDict();
    // attr_dict->put(new PyString("upper"), upper());
    // attr_dict->put(new PyString("lower"), lower());

}

void  Universal::destroy() {

    delete PyTrue;
    delete PyFalse;
    delete PyNone;

}
