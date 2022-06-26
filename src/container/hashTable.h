//
// Created by sunjinlong01 on 2022/6/5.
//
#include<iostream>
#include <stdio.h>
#include<stdlib.h>
#include "math_tool.h"
#define EMPTY 0
#define DELETE 1
#define rank long

#ifndef PYTHON_HASHTABLE_H
#define PYTHON_HASHTABLE_H


template<typename K, typename V> class hashTable{
private:
    // 在堆区申请内存
    K * k_table;
    V * v_table;
    rank hash(K k);
    rank rehash(rank idx);
    rank _search(K k);
    void add_item(rank idx, K k, V v){
        *(k_table + idx) = k;
        *(v_table + idx) = v;
        size ++;

    }
    void update_item(rank idx, V v){
        *(v_table + idx) = v;
    }

    void del_item(rank idx){
        *(k_table + idx) = DELETE;
        size --;
    }
    float capcity_rate;
    rank capcity;

public:
    hashTable();
    ~hashTable();
    rank size;
    bool insert(K k,V v);
    bool remove(K k);
    rank get(K k);
    void enrich_memo();

};

template<typename K, typename V>  hashTable<K, V>::hashTable(){

    capcity = 3;
    k_table = new K[capcity];
    v_table = new V[capcity];
    memset(k_table, EMPTY, capcity);
    memset(v_table, EMPTY, capcity);
    size = 0;
};

template<typename K, typename V>  hashTable<K, V>::~hashTable(){

    delete [] k_table;
    k_table = nullptr;
    delete [] v_table;
    v_table = nullptr;
}

template<typename K, typename V>  void hashTable<K, V>::enrich_memo(){

    rank old_capcity = capcity;
    K* src_k_table = k_table;
    V* src_v_table = v_table;

    rank new_capcity = getNextOdd(old_capcity);
    //std::cout<<"enrich memory from " << old_capcity << " to "<< new_capcity << std::endl;

    k_table = new K[new_capcity];
    v_table = new V[new_capcity];
    memset(k_table, EMPTY, new_capcity);
    memset(v_table, EMPTY, new_capcity);

    //copy
    memcpy(src_k_table, k_table, old_capcity);
    memcpy(src_v_table, v_table, old_capcity);
    capcity = new_capcity;

    //std::cout<<"enrich memory from " << src_k_table << " to "<< k_table << std::endl;


}

/*
插入函数

1.求解hash值
2.检查槽位是否被占用
2.1 如果没被占用，直接插入
2.2 如果被占用，重新插入的key和当前key相同，更新value
2.3 如果被占用，重新插入的key和当前key不相同，重新探测新的key
2.3.1 求解到新的key，判断是否和当前key相同，相同则更新，不相同则插入
*/
template<typename K, typename V>  bool hashTable<K, V>::insert(K k, V v){

    rank idx = hash(k);
    if (k_table[idx] == EMPTY){
        add_item(idx, k, v);
    }else if (k_table[idx] == k){
        update_item(idx, v);
    } else{
        while (true){
            rank re_idx = rehash(idx);
            if (k_table[re_idx] == EMPTY || k_table[re_idx] == DELETE || k_table[re_idx] == k)
                break;
            if (re_idx == idx){
                return false;
            }
            if (k_table[re_idx] == k){
                update_item(idx, v);
            }else{
                add_item(idx, k, v);
            }
        }
    }

    capcity_rate =  float(size) / float(capcity);
    //std::cout<<capcity<<std::endl;
    if (capcity_rate>0.6) {
        enrich_memo();
    }

    return true;
}

template<typename K, typename V> rank hashTable<K, V>::_search(K k){

    rank idx = hash(k);

    if (k_table[idx] == EMPTY){
        throw k;
    }else if (k_table[idx] == k){

        return idx;
    } else{

        while (true){
            rank re_idx = rehash(idx);
            if (k_table[re_idx] == DELETE){
                continue;
            }
            if (k_table[re_idx] == EMPTY || k_table[re_idx] == k)
                break;

            if (re_idx == idx){
                throw k;
            }
            if (k_table[re_idx] == k){
                return idx;
            }else{
                throw k;
            }
        }
    }
    return 0;
}

template<typename K, typename V> rank hashTable<K, V>::get(K k){

    rank s_idx  = _search(k);
    return v_table[s_idx];
}

template<typename K, typename V> bool hashTable<K, V>::remove(K k){

    rank s_idx = _search(k);
    del_item(s_idx);
    return true;
}

template<typename K, typename V> rank hashTable<K, V>::hash(K k){
    rank idx = k % capcity;
    return idx % capcity;
}

template<typename K, typename V> rank hashTable<K, V>::rehash(rank idx){
    return (idx + 1) % capcity;
}

#endif //PYTHON_HASHTABLE_H
