//
// Created by sunjinlong01 on 2022/8/9.
//
#include "src/object/klass.h"
#include "src/object/pyObject.h"

#ifndef PYTHON_TYPE_H
#define PYTHON_TYPE_H


class TypeKlass:Klass {
private:
    static TypeKlass *instance;
    TypeKlass();
public:
    PyObject * type_object;
    void set_typeobject(PyObject * x);
    static Klass *get_instance();

};

class TypeObject: public PyObject {
private:
    Klass * _own_klass;
public:
    void set_ownklass(Klass * x);
    Klass * own_klass(){ return _own_klass;};
};


#endif //PYTHON_TYPE_H
