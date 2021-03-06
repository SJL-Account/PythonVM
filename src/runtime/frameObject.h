//
// Created by sunjinlong01 on 2022/6/24.
//
#include "src/runtime/block.h"
#include "src/object/functionObject.h"
#include "src/object/pyObject.h"
#include "src/code/codeObject.h"
#include "src/container/arrayList.h"
#include "src/container/map.h"

#ifndef PYTHON_FRAMEOBJECT_H
#define PYTHON_FRAMEOBJECT_H

class FrameObject{
public:
    // 链表指针
    FrameObject * _sender;
    // 字节码
    PyString * byte_codes;
    // 运行栈
    ArrayList<PyObject *> * _stack;
    // 符号表
    ArrayList<PyObject *> * _names;
    // 变量符号表
    ArrayList<PyObject *> * _varnames;
    // 常量表
    ArrayList<PyObject *> * _consts;
    // 嵌套栈
    ArrayList<Block* > * _loop_stack;
    // 局部变量表
    Map<PyObject *, PyObject *> * _local;
    // 全局变量表
    Map<PyObject *, PyObject *> * _global;
    // 参数表
    ArrayList<PyObject *> * _fast;
    // 默认参数表
    ArrayList<PyObject *> * _default;
    // 程序计数器
    int pc;
    // 构造
    FrameObject(CodeObject * code);
    FrameObject(FunctionObject * func);
    FrameObject(FunctionObject * func, ArrayList<PyObject* > * args);
    FrameObject(FunctionObject * func, ArrayList<PyObject* > * args, int op_arg);
    // 属性
    void set_pc(int p_pc){ pc = p_pc;};
    int get_pc(){return pc;};
    // 帧相关
    void set_sender(FrameObject * sender){_sender = sender;};
    bool is_first_frame(){ return  (_sender == NULL);};
    // 数据表相关
    ArrayList<PyObject *> * names(){return _names;};
    ArrayList<PyObject *> * consts(){return _consts;};
    ArrayList<PyObject *> * stack(){return _stack;};
    ArrayList<Block *> * loop_stack(){return _loop_stack;};
    Map<PyObject *, PyObject *> * local(){return _local;};
    Map<PyObject *, PyObject *> * global(){return _global;};
    ArrayList<PyObject *> *  fast(){return _fast;};
    // 功能
    unsigned char get_op_code();
    short get_op_arg();
    bool has_more_code();
    // 运算
};

#endif //PYTHON_FRAMEOBJECT_H
