//
// Created by sunjinlong01 on 2022/7/12.
//
#include "src/object/pyInteger.h"
#include "src/object/pyList.h"
#include "src/object/pyString.h"
#include "pyIter.h"

IterKlass* IterKlass::instance=NULL;


Klass *IterKlass::get_instance() {
    if (instance==NULL){
        instance = new IterKlass();
    }
    return instance;
}

/*
 * 迭代器方法
 */
PyObject *IterKlass::next(PyObject *x) {

    assert(x->_klass==this->get_instance());
    int len = 0;
    PyIter * iter = ((PyIter*)x);
    PyObject* iter_obj = iter->iter_obj;
    PyObject* iter_item(NULL);
    if (iter_obj->_klass == ListKlass::get_instance()){
        len = ((PyList*)iter_obj)->length();
        iter_item = ((PyList*)iter_obj)->get(iter->iter_cnt);
    }else if (x->_klass == StringKlass::get_instance()){
        // TODO implement string subscr
        len = ((PyString*)iter_obj)->length();
        iter_item = ((PyString*)iter_obj)->subscr(new PyInteger(iter->iter_cnt));
    }
    if (iter->iter_cnt < len){
        iter->iter_cnt += 1;
        return iter_item;
    }else{
        return NULL;
    }

}


IterKlass::IterKlass() = default;


PyIter::PyIter(PyObject * iter_obj) : PyObject() {
    this->iter_obj = iter_obj;
    iter_cnt=0;
    set_klass(IterKlass::get_instance());
}

