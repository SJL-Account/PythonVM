
#include <stdio.h>
#include "src/object/pyObject.h"
#include "src/object/pyInteger.h"
#include "src/runtime/universal.h"

// TODO 重新定义？
IntegerKlass * IntegerKlass::instance = NULL;

Klass* IntegerKlass::get_instance(){
    if (instance == NULL){
        instance = new IntegerKlass();
    }
    return instance;
}

IntegerKlass::IntegerKlass()= default;

void IntegerKlass::print(PyObject * x) {

    if (x->_klass == this->instance){
        printf("%d", ((PyInteger *)x)->_value);
    }

}

PyObject * IntegerKlass::add(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass){
        int result = ((PyInteger *)x)->_value + ((PyInteger *)y)->_value;
        return new PyInteger(result);
    }
    return Universal::PyNone;

}

PyObject * IntegerKlass::sub(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass){
        int result = ((PyInteger *)x)->_value - ((PyInteger *)y)->_value;
        return new PyInteger(result);
    }
    return Universal::PyNone;

}

PyObject * IntegerKlass::mul(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass){
        int result = ((PyInteger *)x)->_value * ((PyInteger *)y)->_value;
        return new PyInteger(result);
    }
    return Universal::PyNone;

}

PyObject * IntegerKlass::div(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass){
        int result = ((PyInteger *)x)->_value / ((PyInteger *)y)->_value;
        return new PyInteger(result);
    }
    return Universal::PyNone;

}

PyObject * IntegerKlass::mod(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass){
        int result = ((PyInteger *)x)->_value % ((PyInteger *)y)->_value;
        return new PyInteger(result);
    }
    return Universal::PyNone;

}

PyObject * IntegerKlass::less(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass) {
        if (((PyInteger *)x)->_value < ((PyInteger *)y)->_value){
            return  Universal::PyTrue;
        }
        return Universal::PyFalse;
    }
    return Universal::PyFalse;
}

PyObject * IntegerKlass::less_equal(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass) {
        if (((PyInteger *)x)->_value <= ((PyInteger *)y)->_value){
            return  Universal::PyTrue;
        }
        return Universal::PyFalse;
    }
    return Universal::PyFalse;
}

PyObject * IntegerKlass::equal(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass) {
        if (((PyInteger *)x)->_value == ((PyInteger *)y)->_value){
            return  Universal::PyTrue;
        }
        return Universal::PyFalse;
    }
    return Universal::PyFalse;
}

PyObject * IntegerKlass::not_equal(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass) {
        if (((PyInteger *)x)->_value != ((PyInteger *)y)->_value){
            return  Universal::PyTrue;
        }
        return Universal::PyFalse;
    }
    return Universal::PyFalse;
}

PyObject * IntegerKlass::greater(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass) {
        if (((PyInteger *)x)->_value > ((PyInteger *)y)->_value){
            return  Universal::PyTrue;
        }
        return Universal::PyFalse;
    }
    return Universal::PyFalse;
}

PyObject * IntegerKlass::greater_equal(PyObject *x, PyObject *y) {

    if(x->_klass == y->_klass) {
        if (((PyInteger *)x)->_value >= ((PyInteger *)y)->_value){
            return  Universal::PyTrue;
        }
        return Universal::PyFalse;
    }
    return Universal::PyFalse;
}

void IntegerKlass::init() {

    set_super(ObjectKlass::get_instance());
}

PyInteger::PyInteger(int value){
    _value = value;
    set_klass(IntegerKlass::get_instance());
};

void PyInteger::print(){
    printf("%d", _value);
};

PyObject * PyInteger::add(PyObject * x) {

    return this->_klass->add(this, x);
}

PyObject * PyInteger::sub(PyObject * x) {

    return this->_klass->sub(this, x);
}

PyObject * PyInteger::mul(PyObject * x) {

    return this->_klass->mul(this, x);
}

PyObject * PyInteger::div(PyObject * x) {

    return this->_klass->div(this, x);
}

PyObject * PyInteger::mod(PyObject * x) {

    return this->_klass->mod(this, x);
}

PyObject * PyInteger::less(PyObject * x) {

    return this->_klass->less(this, x);
}

PyObject * PyInteger::less_equal(PyObject * x) {

    return this->_klass->less_equal(this, x);
}

PyObject * PyInteger::equal(PyObject * x) {

    return this->_klass->equal(this, x);
}

PyObject * PyInteger::not_equal(PyObject * x) {

    return this->_klass->not_equal(this, x);
}

PyObject * PyInteger::greater(PyObject * x) {

    return this->_klass->greater(this, x);
}

PyObject * PyInteger::greater_equal(PyObject * x) {

    return this->_klass->greater_equal(this, x);
}

PyObject * PyInteger::len() {

    return 0;
}