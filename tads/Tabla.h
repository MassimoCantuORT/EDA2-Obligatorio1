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
struct ClaveValor {
    K clave;
    V valor;
    
    ClaveValor(K unaClave, V unValor) : clave(unaClave), valor(unValor) {}
    //Usar este constructor solo para comparaciones
    ClaveValor(K unaClave) : clave(unaClave) {}

    void setValor(K nuevoValor) { this->valor = nuevoValor; }

    bool operator==(ClaveValor other) { return this->clave == other.clave; }
    bool operator==(K otherK) { return this->clave == otherK; }
};

#endif