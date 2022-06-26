//
// Created by sunjinlong01 on 2022/6/16.
//


#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>

#ifndef PYTHON_HEAP_H
#define PYTHON_HEAP_H

template <typename T> class Heap{

private:
    int parent(int idx);
    int left(int idx);
    int right(int idx);
    void _overflow(int idx);
    void _underflow(int idx);
    void _swap(int idx1, int idx2);
public:
    std::vector<T> elems;
    Heap(int k);
    ~Heap();
    int _size(){return elems.size();};
    T pop();
    void push(T);

};

template <typename T> Heap<T>::Heap(int k){

}

template <typename T> Heap<T>::~Heap(){
    delete elems;
}

template <typename T> int Heap<T>::parent (int idx){
    return idx / 2;
}

template <typename T> int Heap<T>::left (int idx){
    return (idx * 2) + 1;
}

template <typename T> int Heap<T>::right (int idx){
    return (idx * 2) + 2;
}

template<typename T> void Heap<T>::_swap(int idx1, int idx2){

    T tmp = elems[idx1];
    elems[idx1] = elems[idx2];
    elems[idx2] = tmp;

}

template<typename T> T Heap<T>::pop(){

    //1. swap the first element and last element
    int last_idx = _size() - 1;
    T pop_val = elems[last_idx];
    _swap(0, last_idx);
    //2. delete the last element
    elems.pop_back();
    //3. underflow the top element.
    _underflow(0);
    return pop_val;
}

template<typename T> void Heap<T>::push(T elem){

    // 1. append element to tail
    elems.push_back(elem);
    int last_idx = _size() - 1;
    // 2. overflow the tail element.
    _overflow(last_idx);

};

template<typename T> void Heap<T>::_overflow(int idx){

    // 0. root layer
    if (idx == 0)return;
    // 1.compare with parent node
    T c_elem = elems[idx];
    int p_idx = parent(idx);
    T p_elem = elems[p_idx];
    // 2.current element less than parent -> swap
    if (c_elem < p_elem){
        _swap(p_idx, idx);
        // 3.overflow the parent idx
        _overflow(p_idx);
    }
}

template<typename T> void Heap<T>::_underflow (int idx){

    // 0.tail layer
    if (idx >= _size()) return;
    // 1. compare with childs.
    int l_idx = left(idx);
    int r_idx = right(idx);
    int max_idx = idx;
    T l_elem = elems[l_idx];
    T r_elem = elems[r_idx];
    T c_elem = elems[idx];
    // 2. swap with smaller element.
    if (l_elem > c_elem)max_idx = l_idx;
    if (r_elem > c_elem)max_idx = r_idx;
    // 3. recursion with smaller index with _underflow.
    if (max_idx != idx)
    {
        _swap(idx, max_idx);
        _underflow(max_idx);
    }

}

#endif //PYTHON_HEAP_H
