//
// Created by sunjinlong01 on 2022/6/23.
//

#include "src/object/klass.h"


ObjectKlass * ObjectKlass::instance = NULL;

ObjectKlass::ObjectKlass() = default;

Klass * ObjectKlass::get_instance() {

    if(instance==NULL){
        instance = new ObjectKlass();
    }
    return instance;
}
