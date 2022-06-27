//
// Created by sunjinlong01 on 2022/6/12.
//
#include <stdio.h>
#include "src/runtime/frameObject.h"
#include "src/code/bytecode.h"
#include "src/code/codeObject.h"
#include "src/object/pyString.h"
#include "src/object/pyInteger.h"
#ifndef PYTHON_INTERPRETER_H
#define PYTHON_INTERPRETER_H

class Interpreter{
private:
    FrameObject * _frame;
    CodeObject * code;
    Map<PyObject *, PyObject *> * _build;
public:
    Interpreter();
    void run(CodeObject * code);
    void build_frame(PyObject * x, ArrayList<PyObject *> * arg_list);
    void eval_frame();
    void leave_frame(PyObject * ret_value);
    void destroy_frame();
};

#endif //PYTHON_INTERPRETER_H

