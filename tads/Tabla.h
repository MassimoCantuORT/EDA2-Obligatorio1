#ifndef TABLA_H
#define TABLA_H

template <class K, class V>
class Tabla
{

public:

    virtual void insert(K key, V value) = 0;

    virtual V get(K key) = 0;

    virtual void remove(K key) = 0;

    virtual int count() = 0;

};

template <class K, class V>
class ClaveValor {
    private:
    K clave;
    V valor;
    
    public:
    ClaveValor(K& unaClave, V& unValor) : clave(unaClave), valor(unValor) {}

    K getClave() {return this->clave;}
    V getValor() {return this->valor;}
    void setClave(K nuevaClave) { this->clave = nuevaClave; }
    void setValor(K nuevoValor) { this->valor = nuevoValor; }

    bool operator==(ClaveValor other) { return this->getClave() == other.getClave(); }
    bool operator==(K otherK) { return this->getClave() == otherK; }
};

#endif