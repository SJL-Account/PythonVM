//
// Created by sunjinlong01 on 2022/7/7.
//
#include "src/runtime/universal.h"
#include "src/object/pyInteger.h"
#include "src/object/pyList.h"
#include "src/object/pyDict.h"
#include "src/object/pyString.h"
#include "src/object/functionObject.h"

// 反转
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

// 追加
PyObject * append(ArrayList<PyObject* >* args){
    ((PyList * )(args->get(0)))->push(args->get(1));
    return Universal::PyNone;
}

// 扩展
PyObject * extend(ArrayList<PyObject* >* args){
    PyObject* x = args->get(0);
    PyObject* y = args->get(1);
    assert(x->_klass == ListKlass::get_instance());
    assert(y->_klass == ListKlass::get_instance());
    PyList * list1 = (PyList * )x;
    PyList * list2 = (PyList * )y;
    int list2_n = list2->length();
    for(int i=0; i<list2_n; i++){
        list1->push(list2->get(i));
    }
    return list1;
}

// 排序
PyObject * sort(ArrayList<PyObject* >* args){
    PyList * list = ((PyList * )args->get(0));
    int m = list->length();
    for(int i=0; i<m; i++){
        for(int j=1; j<(m-i); j++){
            if (list->get(j)->less(list->get(j-1)) == Universal::PyTrue){
                PyObject * tmp = list->get(j);
                list->set(j, list->get(j-1));
                list->set(j-1, tmp);
            }

        }
    }
    return Universal::PyNone;
}

// 索引
PyObject * index(ArrayList<PyObject* >* args){

    assert(((PyList * )args->get(0))->_klass == ListKlass::get_instance());
    PyList * list = ((PyList * )args->get(0));
    int index = ((PyInteger * )args->get(1))->_value;
    assert(index < list->length());
    return list->get(index);
}



ListKlass * ListKlass::instance = NULL;

ListKlass::ListKlass() = default;

PyObject* ListKlass::add(PyObject * x, PyObject * y){

    assert(x->_klass == this->get_instance());
    assert(y->_klass == this->get_instance());

    PyList * list1 = (PyList * )y;
    PyList * list2 = (PyList * )x;
    int list1_n = list1->length();
    int list2_n = list2->length();
    PyList * combine_list = new PyList(list1_n + list2_n);
    for (int i=0; i<list1_n; i++)combine_list->set(i, list1->get(i));
    for (int i=0; i<list2_n; i++)combine_list->set(i + list1_n, list2->get(i));
    return  combine_list;
}

PyObject* ListKlass::len(PyObject * x){

    assert(x->_klass == this->get_instance());
    int len = ((PyList*)(x))->length();
    return new PyInteger(len);
}

PyObject* ListKlass::in(PyObject * x, PyObject * y){

    assert(x->_klass == this->get_instance());
    PyList * pylist = ((PyList *) x);
    int length = pylist->length();
    for(int i=0; i< length; i++){
        if (y->equal(pylist->get(i))){
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

    assert(x->_klass == ListKlass::get_instance());
    assert(y->_klass == IntegerKlass::get_instance());
    int index = ((PyInteger *)y)->_value;
    int length = ((PyList *)x)->length();
    assert(index < length);
    return ((PyList *) x)->get(index);
}

PyObject *ListKlass::del_subscr(PyObject *x, PyObject *y) {

    assert(x->_klass == this->get_instance());
    assert(y->_klass == IntegerKlass::get_instance());
    PyList* list = ((PyList *)x);
    int index = ((PyInteger *)y)->_value;
    list->_list->delete_index(index);
    return Universal::PyNone;
}

PyObject *ListKlass::store_subscr(PyObject* x, PyObject* y, PyObject* z) {

    assert(x->_klass == ListKlass::get_instance());
    assert(y->_klass == IntegerKlass::get_instance());
    int index = ((PyInteger *)y)->_value;
    int length = ((PyList *) x)->length();
    assert(index < length);
    ((PyList *) x)->set(index, z);
    return Universal::PyNone;

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

PyList::PyList(int n) : PyObject() {

    _list = new ArrayList<PyObject *>(n);
    set_klass(ListKlass::get_instance());
    // 注册方法
    register_method();

}

PyList::PyList(ArrayList<PyObject*>* x) : PyObject() {
    _list = x;
    set_klass(ListKlass::get_instance());
    // 注册方法
    register_method();
}

void PyList::register_method() {
    // 注册方法
    auto * attr_dict = new PyDict();
    attr_dict->put(new PyString("reverse"), new FunctionObject(reverse));
    attr_dict->put(new PyString("append"), new FunctionObject(append));
    attr_dict->put(new PyString("extend"), new FunctionObject(extend));
    attr_dict->put(new PyString("sort"), new FunctionObject(sort));
    attr_dict->put(new PyString("index"), new FunctionObject(index));
    _klass->set_attr_dict(attr_dict);
}





