//
// Created by sunjinlong01 on 2022/6/30.
//

#include "src/container/map.h"
#include "src/object/pyDict.h"

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