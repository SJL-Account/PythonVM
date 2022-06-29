//
// Created by sunjinlong01 on 2022/6/7.
//
#include <stdio.h>
#include "src/code/codeObject.h"
#include "src/object/pyObject.h"
#include "src/object/pyString.h"
#include "src/object/pyInteger.h"
#include "src/container/arrayList.h"
#include "src/container/bufferedInputStream.h"
#ifndef PYTHON_BINARYFILEPARSER_H
#define PYTHON_BINARYFILEPARSER_H

// pyc解析类
class BinaryFileParser{
private:
    BufferedInputStream * _buffer;
    ArrayList<PyString * >  _string_table;
    PyString * get_string();

public:
    BinaryFileParser(BufferedInputStream* buffer){_buffer = buffer;};
    CodeObject * parse();
    CodeObject * get_code_object();
    ArrayList<PyObject*> * get_tuple();
    PyString * get_byte_codes();
    ArrayList<PyObject*> * get_consts();
    ArrayList<PyObject*> * get_names();
    ArrayList<PyObject*> * get_var_names();
    ArrayList<PyObject*> * get_free_names();
    ArrayList<PyObject*> * get_cell_names();
    PyString * get_file_name();
    PyString * get_module_name();
    PyString * get_name();
    PyString * get_no_table();

};




#endif //PYTHON_BINARYFILEPARSER_H
