//
// Created by sunjinlong01 on 2022/6/17.
//
#include <stdlib.h>
#include "src/object/pyObject.h"
#include "src/object/pyInteger.h"
#include "src/runtime/universal.h"

PyObject * Universal::PyTrue = NULL;
PyObject * Universal::PyFalse = NULL;
PyObject * Universal::PyNone = NULL;

void Universal::genesis() {

    PyTrue = new PyInteger(1);
    PyFalse = new PyInteger(0);
    PyNone = new PyObject();
}

void  Universal::destroy() {

    delete PyTrue;
    delete PyFalse;
    delete PyNone;

}
