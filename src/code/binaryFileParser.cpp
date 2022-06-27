//
// Created by sunjinlong01 on 2022/6/7.
//
#include <iostream>
#include "codeObject.h"
#include "src/object/pyObject.h"
#include "src/object/pyString.h"
#include "src/object/pyInteger.h"
#include "src/container/arrayList.h"
#include "src/container/bufferedInputStream.h"
#include "binaryFileParser.hpp"


// 解析入口
CodeObject* BinaryFileParser::parse() {

    PyObject* pyObject;
    int magic_number = _buffer->readint();
    int datetime = _buffer->readint();
    char c_char = _buffer->read();
    CodeObject * codeObject  = get_code_object();
    return codeObject;

}

// 解析pyc二进制文件
CodeObject * BinaryFileParser::get_code_object() {

    int argcount = _buffer->readint();
    std::cout<<"args count is "<<argcount<<std::endl;
    int nlocals = _buffer->readint();
    int stacksize = _buffer->readint();
    std::cout<<"stack size is "<<stacksize<<std::endl;
    int flags = _buffer->readint();
    PyString * byte_codes = get_byte_codes();
    ArrayList<PyObject*> * consts = get_consts();
    ArrayList<PyObject*> * names = get_names();
    ArrayList<PyObject*> * var_names = get_var_names();
    ArrayList<PyObject*> * free_names = get_free_names();
    ArrayList<PyObject*> * cell_names = get_cell_names();
    PyString * file_name = get_file_name();
    PyString * module_name = get_module_name();
    int begin_line_no = _buffer->readint();
    PyString *  lnotab = get_no_table();
    CodeObject* codeObject = new CodeObject(argcount, nlocals, stacksize, flags,
                                            byte_codes, consts, names, var_names, free_names,
                                            cell_names, file_name, module_name, begin_line_no, lnotab) ;
    return codeObject;

}

// 读取字节码
PyString * BinaryFileParser::get_byte_codes() {

    assert(_buffer->read() == 's');
    return get_string();

}

// 读取字符流
PyString * BinaryFileParser::get_string() {

    int length = _buffer->readint();
    char * str = (char*) malloc(length);
    for (int i = 0; i < length; i++) {
        const char t = _buffer->read();
        str[i] = t;
    }
    PyString * pystring = new PyString(str, length);
    delete [] str;
    return pystring;
}

// 读取常量表
ArrayList<PyObject *> * BinaryFileParser::get_consts() {

    if (_buffer->read() == '('){
        return get_tuple();
    }
    _buffer->unread();
    return NULL;
}

// 读取符号表
ArrayList<PyObject *> * BinaryFileParser::get_names() {

    if (_buffer->read() == '('){
        return get_tuple();
    }
    _buffer->unread();
    return NULL;
}

// 读取变量表
ArrayList<PyObject *> * BinaryFileParser::get_var_names() {

    if (_buffer->read() == '('){
        return get_tuple();
    }
    _buffer->unread();
    return NULL;
}

//
ArrayList<PyObject *> * BinaryFileParser::get_free_names() {

    if (_buffer->read() == '('){
        return get_tuple();
    }
    _buffer->unread();
    return NULL;
}

//
ArrayList<PyObject *> * BinaryFileParser::get_cell_names() {

    if (_buffer->read() == '('){
        return get_tuple();
    }
    _buffer->unread();
    return NULL;
}

// 获取通用元组流
ArrayList<PyObject *> *  BinaryFileParser::get_tuple() {

    int length = _buffer->readint();
    ArrayList<PyObject* > * list = new ArrayList<PyObject* >();
    PyString * str;

    for (int i = 0; i < length; i++){
        char obj_type = _buffer->read();
        switch (obj_type){
            // code object
            case 'c':
                list->push(get_code_object());
                break;
                // integer
            case 'i':
                list->push(new PyInteger(_buffer->readint()));
                break;
                // None
            case 'N':
                list->push(Universal::PyNone);
                break;
                // string (put string table)
            case 't':
                str = get_string();
                list->push(str);
                _string_table.push(str);
                break;
                // string (not put string table)
            case 's':
                str = get_string();
                list->push(str);
                break;
                //
            case 'R':
                list->push(_string_table.get(_buffer->readint()));
                break;

        }
    }

    return list;
}

// 读取文件名
PyString * BinaryFileParser::get_file_name() {

    return get_name();

}

// 读取模块名
PyString * BinaryFileParser::get_module_name() {

    return get_name();

}

// 读取line table
PyString * BinaryFileParser::get_no_table() {

    char ch = _buffer->read();
    if (ch != 's' && ch != 't'){
        _buffer->unread();
        return NULL;
    }
    return get_string();

}

// 获取字符串内容
PyString * BinaryFileParser::get_name() {
    char ch = _buffer->read();

    if (ch == 's'){
        return get_string();
    }else if (ch == 't'){
        PyString * str = get_string();
        _string_table.push(str);
        return str;

    }else if (ch == 'R'){
        return _string_table.get(_buffer->readint());
    }

    return NULL;

}
