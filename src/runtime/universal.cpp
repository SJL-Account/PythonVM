//
// Created by sunjinlong01 on 2022/6/17.
//
#include <stdlib.h>
#include "src/object/pyObject.h"
#include "src/object/pyInteger.h"
#include "src/object/pyString.h"
#include "src/object/functionObject.h"
#include "src/object/pyDict.h"
#include "src/object/pyList.h"
#include "src/runtime/universal.h"
#include "src/object/type.h"

PyObject * Universal::PyTrue = NULL;
PyObject * Universal::PyFalse = NULL;
PyObject * Universal::PyNone = NULL;


PyObject * upper(ArrayList<PyObject* > * args){
    PyString * str_obj =  (PyString * )(args->get(0));
    assert(str_obj->_klass == StringKlass::get_instance());
    for (int i=0; i<str_obj->length(); i++){
        if (str_obj->value()[i] >= 97 && str_obj->value()[i] < 97 + 26){
            str_obj->value()[i] = (str_obj->value()[i] - 32);
        }
    }
    return Universal::PyNone;
}

PyObject * keys(ArrayList<PyObject *> * args){

    PyDict * dict =((PyDict*)args->get(0));
    int length = dict->length();
    PyList * key_list = new PyList();
    for (int i=0; i<length; i++){
        key_list->push(dict->inner_map()->get_key(i));
    }
    return key_list;
}

PyObject * values(ArrayList<PyObject *> * args){

    PyDict * dict =((PyDict*)args->get(0));
    int length = dict->length();
    PyList * val_list = new PyList();

    for (int i=0; i<length; i++){
        val_list->push(dict->inner_map()->get_value(i));
    }
    return  val_list;
}


void Universal::genesis() {

    PyTrue = new PyInteger(1);
    PyFalse = new PyInteger(0);
    PyNone = new PyObject();

    PyDict* string_attr_dict = new PyDict();
    // 注册方法
    string_attr_dict->put(new PyString("upper"), new FunctionObject(upper));
    StringKlass::get_instance()->set_attr_dict(string_attr_dict);

    PyDict * dict_attr_dict = new PyDict();
    dict_attr_dict->put(new PyString("values"), new FunctionObject(values));
    dict_attr_dict->put(new PyString("keys"), new FunctionObject(keys));
    PyDictKlass::get_instance()->set_attr_dict(dict_attr_dict);

    // 对象类型 对象
    TypeObject * ob_type_ob = new TypeObject();
    // 对象 类型
    Klass * ob_klass = ObjectKlass::get_instance();
    // 对象类型 为 顶级类型
    ob_klass->set_super(NULL);
    // 对象类型对象的 类型 为对象类型
    ob_type_ob->set_klass(ob_klass);
    // 对象类型对象 和 对象类型建立关系
    ob_type_ob->set_ownklass(ob_klass);

    // 类型的类型对象
    TypeObject * type_ob = new TypeObject();
    // 类型类型
    Klass * type_klass = TypeKlass::get_instance();
    // 类型类型对象 和 类型类型 建立关系
    type_ob->set_ownklass(type_klass);
    // 类型类型对象的 类型 为类型类型
    type_ob->set_klass(type_klass);
    // 类型类型的 父类为 对象类型
    type_klass->set_super(ob_klass);

    // 初始化各个类型
    ListKlass::get_instance()->init();
    IntegerKlass::get_instance()->init();
    StringKlass::get_instance()->init();

    ob_klass->set_attr_dict(new PyDict());
    type_klass->set_attr_dict(new PyDict());

    ob_klass->set_name(new PyString("object_klass"));
    type_klass->set_name(new PyString("type_klass"));

}

void  Universal::destroy() {

    delete PyTrue;
    delete PyFalse;
    delete PyNone;

}
