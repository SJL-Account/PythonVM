//
// Created by sunjinlong01 on 2022/6/7.
//
#include "src/object/pyObject.h"
#include "src/object/pyString.h"
#include "src/container/arrayList.h"

#ifndef PYTHON_CODEOBJECT_H
#define PYTHON_CODEOBJECT_H
class CodeObject: public PyObject{

public:
    int _argcount;
    int _nlocals;
    int _stack_size;
    int _flag;
    PyString * _bytecodes;
    ArrayList<PyObject*> *_consts;
    ArrayList<PyObject*> * _names;
    ArrayList<PyObject*> * _varnames;
    ArrayList<PyObject*> * _freevars;
    ArrayList<PyObject*> * _cellvars;
    PyString * _filename;
    PyString * _co_name;
    int _lineno;
    PyString * _notable;
    CodeObject(int argcount, int nlocals, int stack_size, int flag,
               PyString * bytecodes,
               ArrayList<PyObject*> * consts,
               ArrayList<PyObject*> * names,
               ArrayList<PyObject*> * varnames,
               ArrayList<PyObject*> * freevars,
               ArrayList<PyObject*> * cellvars,
               PyString * filename,
               PyString * co_name,
               int lineno,
               PyString * notable):
            _argcount(argcount),
            _nlocals(nlocals),
            _bytecodes(bytecodes),
            _consts(consts),
            _names(names),
            _varnames(varnames),
            _freevars(freevars),
            _cellvars(cellvars),
            _filename(filename),
            _co_name(co_name),
            _lineno(lineno),
            _notable(notable){

    }
};
#endif //PYTHON_CODEOBJECT_H
