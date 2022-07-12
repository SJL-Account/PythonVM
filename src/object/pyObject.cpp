
#include "src/runtime/universal.h"
#include "src/object/pyObject.h"
#include "src/object/functionObject.h"
#include "src/object/pyDict.h"

PyObject * PyObject::len() {

    return _klass->len(this);
}

PyObject * PyObject::get_attr(PyObject *attr) {

    PyObject * result = _klass->attr_dict()->get(attr);
    if (result->is_function()){
        result = new MethodObject((FunctionObject*)result, this);
    }
    return result;
}

void PyObject::set_attr(PyObject * owner, PyObject * attr){

    _klass->attr_dict()->put(owner, attr);
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

PyObject * PyObject::in(PyObject * x){
    return _klass->in(this, x);
}

PyObject * PyObject::not_in(PyObject * x){
    return _klass->not_in(this, x);
}

PyObject * PyObject::subscr(PyObject * x){
    return _klass->subscr(this, x);
}

PyObject * PyObject::store_subscr(PyObject * x, PyObject* y){
    return _klass->store_subscr(this, x, y);
}

PyObject * PyObject::del_subscr(PyObject *x){
    return _klass->del_subscr(this, x);
}

bool PyObject::is_function() {

    return _klass == NativeFunctionKlass::get_instance();
}

PyObject * PyObject::next() {
    return _klass->next(this);
}
