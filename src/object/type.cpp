//
// Created by sunjinlong01 on 2022/8/9.
//

#include "src/object/type.h"

TypeKlass * TypeKlass::instance = NULL;

TypeKlass::TypeKlass() = default;

Klass *TypeKlass::get_instance() {

    if(instance==NULL){
        instance = new TypeKlass();
    }
    return instance;
}

void TypeKlass::set_typeobject(PyObject *x) {
    type_object = x;
}

void TypeObject::set_ownklass(Klass * x){
    _own_klass = x;
    ((TypeKlass *) (x))->set_typeobject(this);
}
