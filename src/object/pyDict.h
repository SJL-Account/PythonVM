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

class PyDict: public PyObject{
private:
    void register_method();
    Map<PyObject*, PyObject*>* _map;
public:
    PyDict();
    Map<PyObject*, PyObject*>*  inner_map(){return _map;};
    PyDict(Map<PyObject*, PyObject*>* map);
    int length(){return _map->length();};
    void put(PyObject* k, PyObject* v){_map->put(k, v);};
    PyObject * remove(PyObject * k){return _map->remove(k);};
    PyObject * get(PyObject * k){return _map->get(k);};
};

/*------------------DictIter------------------*/

class DictIterKlass: public Klass{
private:
    static DictIterKlass * instance;
    DictIterKlass();
public:
    static Klass* get_instance();

};

class DictIter: public PyObject{
private:
    PyObject * _owner;
    int _index;
public:
    DictIter(PyObject * owner);
    PyObject * owner(){return _owner;};
    int index(){return _index;};
    void inc_index(){_index++;};

};




#endif //PYTHON_PYDICT_H
