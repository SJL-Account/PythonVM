

#include "src/runtime/universal.h"
#include "src/object/pyObject.h"

#ifndef PYTHON_MAP_H
#define PYTHON_MAP_H

template <typename K, typename V>
class MapEntry{
public:
    K _k;
    V _v;
    void set_k(K k){_k = k;};
    void set_v(V v){_v = v;};
    K get_k(){return _k;}
    V get_v(){return _v;}
    MapEntry(const MapEntry<K, V>& map_entry);
    MapEntry(K k, V v): _k(k), _v(v) {};
    MapEntry(): _k(0), _v(0) {};

};

template <typename K, typename V>
class Map{
private:
    MapEntry<K, V> * _entries;
    int _length;
    int _size;
    void expand();
public:
    Map();
    ~Map();
    void put(K k, V v);
    V remove(K k);
    V get(K k);
    K get_key(int index);
    K get_value(int index);
    PyObject * has_key(K v);
    int index(K k);
    MapEntry<K, V> * entries() {return _entries;}
    int length() {return _length;};
    int size() {return _size;};
};


template <typename K, typename V>
Map<K, V>::Map() {
    _entries = new MapEntry<K, V>[8];
    _size = 8;
    _length = 0;
}

template <typename K, typename V>
Map<K, V>::~Map(){
    delete [] _entries;
}

template <typename K, typename V>
void Map<K, V>::expand() {

    if (_length == _size){
        int _new_size = (_size << 1);
        MapEntry <K, V> * _new_entries = new MapEntry<K, V>[_new_size];
        for(int i=0; i<_length; i++){
            _entries[i] = _new_entries[i];
        }
        delete [] _entries;
        _entries = _new_entries;
        _size = _new_size;
    }

}

template <typename K, typename V>
int Map<K, V>::index(K k){

    for(int i=0; i<_length; i++){
        if (_entries[i]._k->equal(k) == Universal::PyTrue){
            return i;
        }
    }
    return -1;
}

template <typename K, typename V>
void Map<K, V>::put(K k, V v){

    if (has_key(k) == Universal::PyTrue){
        int i = index(k);
        _entries[i].set_v(v);
        return ;
    }
    expand();
    _entries[_length] = MapEntry<K, V>(k, v);
    _length ++ ;
}

template <typename K, typename V>
PyObject * Map<K, V>::has_key(K k) {

    int i = index(k);
    if (i != -1){
        return Universal::PyTrue;
    }else{
        return Universal::PyFalse;
    }
}

template <typename K, typename V>
V Map<K, V>::get(K k){

    int i = index(k);
    if (i != -1){
        return _entries[i].get_v();
    }

    return Universal::PyNone;
}

template <typename K, typename V>
K Map<K, V>::get_key(int index){

    return _entries[index].get_k();
}

template <typename K, typename V>
K Map<K, V>::get_value(int index) {

    return _entries[index].get_v();
}

template <typename K, typename V>
V Map<K, V>::remove(K k){

    int idx = index(k);
    if (idx == -1) return Universal::PyNone;
    MapEntry <K, V> tmp;
    tmp = _entries[idx];
    _entries[idx] = _entries[_length-1];
    _entries[_length-1] = tmp;
    _length --;
    return tmp.get_v();
}

#endif