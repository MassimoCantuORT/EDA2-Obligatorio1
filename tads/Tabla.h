#ifndef TABLA_H
#define TABLA_H

#include <iostream>

template <class K, class V>
class Tabla
{

public:

    virtual void insert(K key, V value) = 0;

    virtual V get(K key) = 0;

    virtual void remove(K key) = 0;

    virtual bool contains(K key) = 0;

    virtual int getCount() = 0;

};

template <class K, class V>
struct KeyValue {
    K key;
    V value;
    
    KeyValue(K k, V v) : key(k), value(v) {}
    //Usar este constructor solo para comparaciones
    KeyValue(K k) : key(k) {}

    void setValue(K newValue) { this->value = newValue; }

    bool operator==(KeyValue other) { return this->key == other.key; }
    bool operator==(K otherK) { return this->key == otherK; }
};

#endif