//
// Created by sunjinlong01 on 2022/6/24.
//
#include "src/container/map.h"
#include "src/object/pyObject.h"
#include "src/code/codeObject.h"
#include "src/runtime/frameObject.h"

FrameObject::FrameObject(CodeObject *code) {

    int stack_size = code->_stack_size;
    byte_codes = code->_bytecodes;
    _names  = code->_names;
    _consts = code->_consts;
    _stack  = new ArrayList<PyObject*>(stack_size);
    _loop_stack = new ArrayList<Block*>();
    _local  = new Map<PyObject*, PyObject*>();
    _global = new Map<PyObject*, PyObject*>();
    pc = 0;
    // 代码片段global用loval表初始化
    _global = _local;
}

FrameObject::FrameObject(FunctionObject * func) {

    CodeObject * code = func->_func_code;
    int stack_size = code->_stack_size;
    byte_codes = code->_bytecodes;
    _names  = code->_names;
    _consts = code->_consts;
    _stack  = new ArrayList<PyObject*>(stack_size);
    _loop_stack = new ArrayList<Block*>();
    _local  = new Map<PyObject*, PyObject*>();
    _global = new Map<PyObject*, PyObject*>();
    pc = 0;
    // 从上层模块继承下来的global变量表
    _global = func->global();
}

FrameObject::FrameObject(FunctionObject * func, ArrayList<PyObject* > * args){
    CodeObject * code = func->_func_code;
    int stack_size = code->_stack_size;
    byte_codes = code->_bytecodes;
    _names  = code->_names;
    _consts = code->_consts;
    _stack  = new ArrayList<PyObject*>(stack_size);
    _loop_stack = new ArrayList<Block*>();
    _local  = new Map<PyObject*, PyObject*>();
    _global = new Map<PyObject*, PyObject*>();
    // 局部参数表
    int fast_cnt = code->_argcount;
    _fast   = new ArrayList<PyObject *>();
    // 默认参数表
    _default = func->get_default();
    int default_cnt = func->get_default()->length();
    // 无默认参数表
    int arg_cnt = args->length();

    // 构造fast表
    while ((default_cnt--) > 0){
        _fast->set((--fast_cnt), _default->pop());
    }
    for(int i=0; i< arg_cnt; i++){
        _fast->set(i, args->pop());
    }
    pc = 0;

    // 从上层模块继承下来的global变量表
    _global = func->global();
}

//FrameObject::FrameObject(FunctionObject * func, ArrayList<PyObject* > * args, int op_arg){
//    CodeObject * code = func->_func_code;
//    int stack_size = code->_stack_size;
//    int flag = code->_flag;
//    byte_codes = code->_bytecodes;
//    _names  = code->_names;
//    _consts = code->_consts;
//    _varnames = code->_varnames;
//    _stack  = new ArrayList<PyObject*>(stack_size);
//    _loop_stack = new ArrayList<Block*>();
//    _local  = new Map<PyObject*, PyObject*>();
//    _global = new Map<PyObject*, PyObject*>();
//
//    // 局部参数数量
//    int fast_cnt = code->_argcount;
//    // 局部参数表
//    _fast   = new ArrayList<PyObject *>();
//
//    // 默认参数表
//    _default = func->get_default();
//    // 默认参数数量
//    int default_cnt = func->get_default()->length();
//    // 参数数量
//    int argcnt = code->_argcount;
//    // 位置扩展参数参数
//    // int na = op_arg >> 0xff;
//    // 键扩展参数数量
//    // int nk = op_arg >> 8;
//    // 是否存在位置扩展参数
//    bool existArgs = (flag & 0x4);
//    // 是否存在键扩展参数
//    bool existKwArgs = (flag & 0x8);
//
//    // default构造fast表
//    while ((default_cnt--) > 0){
//        _fast->set((--fast_cnt), _default->pop());
//    }
//
//    // 加载位置扩展参数
//    if (na > argcnt){
//
//    }else{
//        for(int i=0; i< argcnt; i++){
//            _fast->set(i, args->pop());
//        }
//    }
//
//    //
//
//    pc = 0;
//    // 从上层模块继承下来的global变量表
//    _global = func->global();
//}
//

short FrameObject::get_op_arg() {

    char byte1 = 0xff & byte_codes->value()[pc++];
    short op_arg = (0xff & byte_codes->value()[pc++]) << 8 | byte1;
    return op_arg;
}

unsigned char FrameObject::get_op_code() {
    return  byte_codes->value()[pc++];
}

bool FrameObject::has_more_code() {
    int byte_code_len = byte_codes->length();
    return pc < byte_code_len;
}