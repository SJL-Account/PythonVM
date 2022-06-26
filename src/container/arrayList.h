//
// Created by sunjinlong01 on 2022/6/5.
//

#include <iostream>
#include "src/object/pyObject.h"
#ifndef PYTHON_ARRAYLIST_H
#define PYTHON_ARRAYLIST_H

template <typename T>
class ArrayList{
private:
    T * _array;
    int _length;
    int _size;
    void expand();

public:
    ArrayList(int n=8);
    void insert(int index, T t);
    T get(int index);
    void set(int index, T t);
    int size();
    int length();
    T pop();
    void push(T t);
    void print();
};


template <typename T>
ArrayList<T>::ArrayList(int n) {

    _array = new T[n];
    for (int i = 0; i < n; i++ ) _array[i] = 0;
    _size = n;
    _length = 0;
}

template <typename T>
T ArrayList<T>::get(int index) {

    return _array[index];
    // raise exception

}

template <typename T>
void ArrayList<T>::set(int index, T t) {

    if (index < _length){
        _array[index] = t;
    }
    // raise exception
    throw index;
}

template <typename T>
void ArrayList<T>::insert(int index, T t) {

    if ((_length + 1 ) > _size) expand();

    for(int i = index; i < _length; i++)
        _array[index + 1] = _array[index];
    _array[index] = t;
    _length++;
}

template <typename T>
void ArrayList<T>::expand(){

    T * _new_array = new T[(_size << 1)];
    for(int i = 0; i < _length; i++) _new_array[i] = _array[i];
    delete [] _array;
    _array = _new_array;
    _size = _size << 1;
}

template <typename T>
T ArrayList<T>::pop(){
    return  _array[--_length];
    // raise exception
}

template <typename T>
void ArrayList<T>::push(T t){
    if ((_length + 1 ) > _size) expand();
    _array[_length++] = t;
    // raise exception
}

template <typename T>
int ArrayList<T>::size(){ return _size;}

template <typename T>
int ArrayList<T>::length(){ return _length;}

template <typename T>
void ArrayList<T>::print(){
    for (int i = 0; i < _length; i++ ) std::cout<<_array[i]<<std::endl;
}

class PyObject;
#endif //PYTHON_ARRAYLIST_H
