#ifndef TABLA_H
#define TABLA_H

template <class K, class V>
class Table
{

public:

    virtual void insert(K key, V value) = 0;

    virtual V get(K key) = 0;

    virtual void remove(K key) = 0;

    virtual bool contains(K key) = 0;

    virtual int getCount() = 0;

};


#endif