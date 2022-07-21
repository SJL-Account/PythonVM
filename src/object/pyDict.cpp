//
// Created by sunjinlong01 on 2022/6/30.
//
#include "src/container/map.h"
#include "src/object/pyDict.h"
#include "src/object/pyString.h"
#include "src/object/functionObject.h"



PyDictKlass * PyDictKlass::instance = NULL;

PyDictKlass::PyDictKlass() {

}

Klass* PyDictKlass::get_instance(){
    if (instance == NULL){
        instance = new PyDictKlass();
    }
    return instance;
}

PyDict::PyDict(){
    _map = new Map<PyObject*, PyObject*>();
    set_klass(PyDictKlass::get_instance());
};

PyDict::PyDict(Map<PyObject*, PyObject*>* map){
    _map = map;
    set_klass(PyDictKlass::get_instance());
};

DictIterKlass::DictIterKlass() {
    PyDict * attr_dict = new PyDict();
    //attr_dict->put(new PyString("next"), new FunctionObject(list_next));
    set_attr_dict(attr_dict);
    set_name(new PyString("dict_iter"));
}

DictIterKlass * DictIterKlass::instance = NULL;


Klass* DictIterKlass::get_instance() {
    if (instance == NULL){
        instance = new DictIterKlass();
    }
    return instance;
}

DictIter::DictIter(PyObject *owner) {

    this->_owner = owner;
    this->_index = 0;

}

