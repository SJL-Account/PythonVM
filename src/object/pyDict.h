//
// Created by sunjinlong01 on 2022/6/30.
//

#include "src/object/klass.h"
#include "src/container/map.h"
#ifndef PYTHON_PYDICT_H
#define PYTHON_PYDICT_H

class PyDictKlass:Klass{
private:
    static PyDictKlass * instance;
    PyDictKlass();
public:
    static Klass* get_instance();

};

class PyDict:PyObject{
public:
    Map<PyObject*, PyObject*>* _map;
    PyDict();
    PyDict(Map<PyObject*, PyObject*>* map);
    void put(PyObject* k, PyObject* v){_map->put(k, v);};
    PyObject * remove(PyObject * k){return _map->remove(k);};
    PyObject * get(PyObject * k){return _map->get(k);};

};

#endif //PYTHON_PYDICT_H
