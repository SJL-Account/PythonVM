//
// Created by sunjinlong01 on 2022/7/7.
//
#include "src/runtime/universal.h"
#include "src/object/pyInteger.h"
#include "src/object/pyList.h"
#include "src/object/pyDict.h"
#include "src/object/pyString.h"
#include "src/object/functionObject.h"

PyObject * reverse(ArrayList<PyObject* >* args){
    PyList * list = ((PyList * )args->get(0));
    int m = list->length();
    int i = 0;
    int j = m - 1;
    PyObject * tmp, * i_val, * j_val;

    while(i < j){
        i_val = list->_list->get(i);
        j_val = list->_list->get(j);
        tmp = i_val;
        list->_list->set(i, j_val);
        list->_list->set(j, tmp);
        i++;
        j--;
    }
    return Universal::PyNone;

}

ListKlass * ListKlass::instance = NULL;

ListKlass::ListKlass() {

};

PyObject* ListKlass::in(PyObject * x, PyObject * y){

    assert(y->_klass == this->get_instance());
    PyList * pylist = ((PyList *) y);
    int length = pylist->length();
    for(int i=0; i< length; i++){
        if (x->equal(pylist->get(i))){
            return Universal::PyTrue;
        }
    }

    return Universal::PyFalse;
}

PyObject* ListKlass::not_in(PyObject * x, PyObject * y){

    if (in(x, y) == Universal::PyTrue){
        return Universal::PyFalse;
    }
    else{
        return Universal::PyTrue;
    }

}

PyObject* ListKlass::subscr(PyObject * x, PyObject * y){

    assert(x->_klass == IntegerKlass::get_instance());
    assert(y->_klass == ListKlass::get_instance());
    int index = ((PyInteger *)x)->_value;
    int length = ((PyList *) y)->length();
    assert(index < length);
    return ((PyList *) y)->get(index);
}

void ListKlass::print(PyObject *x) {

    assert(x->_klass == this->get_instance());
    PyList * list = (PyList *)x;
    int m = list->length();
    printf("[");
    for (int i=0; i < m; i++){
        list->get(i)->print();
        printf(",");
    }
    printf("]");
}

Klass* ListKlass::get_instance(){
    if (instance == NULL){
        instance = new ListKlass();
    }
    return instance;
}

PyList::PyList(int n) {

    _list = new ArrayList<PyObject *>(n);
    set_klass(ListKlass::get_instance());
    PyDict * attr_dict = new PyDict();
    attr_dict->put(new PyString("reverse"), new FunctionObject(reverse));
    _klass->set_attr_dict(attr_dict);

}

PyList::PyList(ArrayList<PyObject*>* x) {
    _list = x;
    set_klass(ListKlass::get_instance());
}





