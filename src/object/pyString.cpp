#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/runtime/universal.h"
#include "src/object/pyObject.h"
#include "src/object/pyString.h"
#include "src/object/pyInteger.h"

StringKlass * StringKlass::instance = NULL;

Klass* StringKlass::get_instance(){
    if (instance == NULL){
        instance = new StringKlass();
    }
    return instance;
}

StringKlass::StringKlass() {

}

void StringKlass::print(PyObject *x) {

    assert(x->_klass == this->instance);
    for (int i = 0; i < ((PyString *)x)->length(); i++) {
        printf("%c", ((PyString *)x)->value()[i]);
    }
}

PyObject *StringKlass::less(PyObject *x, PyObject *y) {
    return Klass::less(x, y);
}

PyObject *StringKlass::less_equal(PyObject *x, PyObject *y) {
    return Klass::less_equal(x, y);
}

PyObject *StringKlass::equal(PyObject *x, PyObject *y) {

    assert(x->_klass == this->instance);
    assert(y->_klass == this->instance);

    if (x == NULL || y == NULL){
        return Universal::PyFalse;
    }
    if ((((PyString *)y)->length()) != (((PyString *)x)->length()))
        return Universal::PyFalse;

    char * cmp_str = ((PyString *)y)->value();
    for(int i=0; i<((PyString *)x)->length(); i++){
        if (cmp_str[i] != ((PyString *)x)->value()[i]){
            return Universal::PyFalse;
        }
    }
    return Universal::PyTrue;
}

PyObject *StringKlass::not_equal(PyObject *x, PyObject *y) {
    return Klass::not_equal(x, y);
}

PyObject *StringKlass::greater(PyObject *x, PyObject *y) {
    return Klass::greater(x, y);
}

PyObject *StringKlass::greater_equal(PyObject *x, PyObject *y) {
    return Klass::greater_equal(x, y);
}

PyObject *StringKlass::add(PyObject *x, PyObject *y) {
    return Klass::add(x, y);
}

PyObject *StringKlass::sub(PyObject *x, PyObject *y) {
    return Klass::sub(x, y);
}

PyObject *StringKlass::mul(PyObject *x, PyObject *y) {
    return Klass::mul(x, y);
}

PyObject *StringKlass::div(PyObject *x, PyObject *y) {
    return Klass::div(x, y);
}

PyObject *StringKlass::mod(PyObject *x, PyObject *y) {
    return Klass::mod(x, y);
}

PyString::PyString(const char *s) {
    int m = strlen(s);
    _length = m;
    _value = new char[m];
    strcpy(_value, s);
    set_klass(StringKlass::get_instance());
}

PyString::PyString(const char *s, int length) {

    _value = new char[length];
    for(int i=0; i<length; i++) {
        _value[i] = s[i];
    }
    _length = length;
    set_klass(StringKlass::get_instance());
}

PyObject * PyString::add(PyObject * x) {

    return _klass->add(this, x);
}

PyObject * PyString::equal(PyObject *x) {

    return _klass->equal(this, x);
}

PyObject * PyString::len(){

    new PyInteger(_length);
}

void PyString::print(){

    _klass->print(this);
};
