
#include "src/runtime/universal.h"
#include "src/object/pyObject.h"
#include "src/object/pyDict.h"

PyObject * PyObject::len() {

    return Universal::PyNone;
}

PyObject * PyObject::get_attr(PyObject *attr) {

    return klass()->attr_dict()->get(attr);
}

void PyObject::set_attr(PyObject * owner, PyObject * attr){

    klass()->attr_dict()->put(owner, attr);

}

void PyObject::print() {
    _klass->print(this);
}

PyObject * PyObject::add(PyObject * x){
    return _klass->add(this, x);
}

PyObject * PyObject::sub(PyObject * x){
    return _klass->sub(this, x);
}

PyObject * PyObject::mul(PyObject * x){
    return _klass->mul(this, x);
}

PyObject * PyObject::div(PyObject * x){
    return _klass->div(this, x);
}

PyObject * PyObject::mod(PyObject * x){
    return _klass->mod(this, x);
}

PyObject * PyObject::less(PyObject * x){
    return _klass->less(this, x);
}

PyObject * PyObject::less_equal(PyObject * x){
    return _klass->less_equal(this, x);
}

PyObject * PyObject::equal(PyObject * x){
        return _klass->equal(this, x);
}

PyObject * PyObject::not_equal(PyObject * x){
    return _klass->not_equal(this, x);
}

PyObject * PyObject::greater(PyObject * x){
    return _klass->greater(this, x);
}

PyObject * PyObject::greater_equal(PyObject * x){
    return _klass->greater_equal(this, x);
}

PyObject * PyObject::is(PyObject * x){
    return (this == x)? Universal::PyTrue: Universal::PyFalse;
}

PyObject * PyObject::is_not(PyObject * x){
    return (this != x)? Universal::PyTrue: Universal::PyFalse;
}