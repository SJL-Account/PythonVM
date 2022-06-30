//
// Created by sunjinlong01 on 2022/6/12.
//
#include <stdio.h>
#include "src/runtime/block.h"
#include "src/runtime/frameObject.h"
#include "src/container/map.h"
#include "src/code/codeObject.h"
#include "src/code/bytecode.h"
#include "src/object/functionObject.h"
#include "src/object/pyString.h"
#include "src/object/pyInteger.h"
#include "src/runtime/universal.h"
#include "src/runtime/interpreter.h"

#define PUSH(x) _frame->stack()->push(x)
#define POP() _frame->stack()->pop()
#define LEVEL() _frame->stack()->length()

Interpreter::Interpreter() {
    _build = new Map<PyObject *, PyObject *>();
    _build->put(new PyString("True"), Universal::PyTrue);
    _build->put(new PyString("False"), Universal::PyFalse);
    _build->put(new PyString("None"), Universal::PyNone);
}

void Interpreter::build_frame(PyObject * x, ArrayList<PyObject *> * arg_list) {

    FrameObject * _new_frame;
    // 函数
    _new_frame = new FrameObject((FunctionObject *)x, arg_list);
    _new_frame->set_sender(_frame);
    // 方法
    _frame = _new_frame;

}

void Interpreter::destroy_frame() {

    // 获取调用者
    FrameObject * call_frame = _frame->_sender;
    // 获取被调用者
    FrameObject * called_frame = _frame;
    // 销毁被调用者
    delete called_frame;
    // 重置调用者为_frame
    _frame = call_frame;
}

void Interpreter::leave_frame(PyObject * ret_value) {

    destroy_frame();
    PUSH(ret_value);

}

void Interpreter::run(CodeObject *code) {

    // 建立顶级模块帧
    _frame = new FrameObject(code);
    // 运算
    eval_frame();
    // 销毁帧
    destroy_frame();

}

void Interpreter::eval_frame() {

    while (_frame->has_more_code()){
        // 字节码
        unsigned char op_code = _frame->get_op_code();
        short op_arg = -1 ;
        // 字节码 存在参数
        bool have_arg = op_code >= ByteCode::HAVE_ARG;
        if (have_arg){
            op_arg = _frame->get_op_arg();
        }
        
        PyObject * const_ptr, * name_ptr, * code_ptr, * func_ptr, * reval_ptr;
        ArrayList<PyObject *> * arg_list;
        FunctionObject * fo;
        PyObject * v, * w,  * u; // 操作数1， 操作数2， 操作数3
        PyInteger * lhs, * rhs;  // 左表达式，右表达式
        Block * b; // 当前block信息
        switch (op_code) {
            case ByteCode::LOAD_ATTR:
                break;
            case ByteCode::STORE_ATTR:
                break;
            case ByteCode::LOAD_FAST:
                PUSH(_frame->_fast->get(op_arg));
                break;
            case ByteCode::STORE_FAST:
                _frame->_fast->set(op_arg, POP());
                break;
            case ByteCode::LOAD_GLOBAL:
                // op_arg为符号表中下标
                name_ptr = _frame->names()->get(op_arg);
                const_ptr = _frame->global()->get(name_ptr);
                PUSH(const_ptr);
                break;
            case ByteCode::STORE_GLOBAL:
                v = POP();
                // op_arg为符号表中下标
                name_ptr = _frame->names()->get(op_arg);
                _frame->global()->put(name_ptr, v);
                break;
            case ByteCode::STORE_NAME:
                // fecth 栈顶元素
                v = POP();
                // 填充变量表
                name_ptr = _frame->names()->get(op_arg);
                _frame->local()->put(name_ptr, v);
                break;
            case ByteCode::LOAD_NAME:
                // LEGB原则： Local -> Enclosing -> Global -> BuildIn
                // 从符号表中提取字符
                name_ptr = _frame->names()->get(op_arg);
                // 从局部变量中提取变量值
                const_ptr = _frame->local()->get(name_ptr);
                //(const_ptr->is_not(Universal::PyNone) == Universal::PyTrue)
                if (const_ptr != Universal::PyNone){
                    // 入栈
                    PUSH(const_ptr);
                    break;
                }
                // 从全局变量中提取变量值
                const_ptr = _frame->global()->get(name_ptr);
                if (const_ptr != Universal::PyNone){
                    PUSH(const_ptr);
                    break;
                }
                // 从build变量中提取变量值
                const_ptr = _build->get(name_ptr);
                if (const_ptr != Universal::PyNone){
                    PUSH(const_ptr);
                    break;
                }
                PUSH(Universal::PyNone);
                break;
            case ByteCode::LOAD_CONST:
                // 从常量表中提取数值
                const_ptr = _frame->consts()->get(op_arg);
                // 入栈
                PUSH(const_ptr);
                break;
            case ByteCode::BINANY_ADD:
                v = POP();
                w = POP();
                PUSH(v->add(w));
                break;
            case ByteCode::COMPARE_OP:
                v = POP();
                w = POP();
                switch (op_arg){
                    case COMPAREOP ::LESS:
                        PUSH(w->less(v));
                        break;
                    case COMPAREOP ::LESS_EQUAL:
                        break;
                    case COMPAREOP ::EQUAL:
                        break;
                    case COMPAREOP ::NOT_EQUAL:
                        break;
                    case COMPAREOP ::GREATER:
                        PUSH(w->greater(v));
                        break;
                    case COMPAREOP ::GREATER_EQUAL:
                        break;
                    case COMPAREOP ::IS:
                        PUSH(w->is(v));
                        break;
                    case COMPAREOP ::IS_NOT:
                        PUSH(w->is(v));
                        break;
                    default:
                        throw op_arg;
                }
                break;
            case ByteCode::POP_JUMP_IF_FALSE:
                v = POP();
                if (v == Universal::PyFalse){
                    _frame->set_pc(op_arg);
                }
                break;
            case ByteCode::JUMP_ABSOLUTE:
                _frame->set_pc(op_arg);
                break;
            case ByteCode::JUMP_FORWARD:
                _frame->set_pc(_frame->pc + op_arg);;
                break;
            case ByteCode::SETUP_LOOP:
                // 创建block 压入栈
                _frame->loop_stack()->push(new Block(op_code, _frame->pc + op_arg, LEVEL()));
                break;
            case ByteCode::BREAK_LOOP:
                // 栈顶为当前嵌套层次
                b = _frame->loop_stack()->pop();
                // 层层弹栈，恢复循环前的现场
                while(LEVEL() > b->b_level){
                    POP();
                }
                // 跳转到循环结束
                _frame->set_pc(b->b_target);
                break;
            case ByteCode::POP_BLOCK:
                // 栈顶为当前嵌套层次
                b = _frame->loop_stack()->pop();
                // 层层弹栈，恢复循环前的现场
                while(LEVEL() > b->b_level){
                    POP();
                }
                break;
            case ByteCode::MAKE_FUNCTION:
                // 函数和栈帧的区别：
                // 1.函数是静态的，是代码执行片段，执行期间变量无活动，只读，
                // 2.栈帧时动态的，在调用时确定动态确定，执行期间内部变量有活动
                // 3.全局变量在定义时确定
                // 4.参数在调用时确定

                // 获取函数code对象
                code_ptr = POP();
                // 创建函数对象
                fo = new FunctionObject(code_ptr);
                arg_list = new ArrayList<PyObject *>(op_arg);
                while (op_arg --){
                    arg_list->set(op_arg, POP());
                }
                // 对象定义时，global表就已经确定了
                fo-> set_global(_frame->global());
                fo->set_default(arg_list);
                // 入栈
                PUSH(fo);
                break;
            case ByteCode::CALL_FUNCTION:
                // 获取函数对象
                if (op_arg > 0){
                    arg_list = new ArrayList<PyObject *>(op_arg);
                    while (op_arg--){
                        arg_list->push(POP());
                    }
                }
                func_ptr = POP();
                // 切换frame
                build_frame(func_ptr, arg_list);
                if (arg_list!=NULL){
                    delete arg_list;
                    arg_list = NULL;

                }
                break;
            case ByteCode::RETURN_VALUE:
                // 获取返回值
                reval_ptr = POP();
                // 切换 sender_frame
                if(!_frame->is_first_frame()){
                    leave_frame(reval_ptr);
                }
                break;
            case ByteCode::PRINT_ITEM:
                v = POP();
                v->print();
                break;
            case ByteCode::PRINT_NEW_LINE:
                printf("\n");
                break;
            case ByteCode::POP_TOP:
                POP();
                break;
            default:
                throw op_code;
        }

    }

}
