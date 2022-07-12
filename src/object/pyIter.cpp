//
// Created by sunjinlong01 on 2022/7/12.
//

#include "pyIter.h"

IterKlass* IterKlass::instance=NULL;

Klass *IterKlass::get_instance() {
    if (instance==NULL){
        return new IterKlass();
    }
    return instance;
}

IterKlass::IterKlass() {

}
