#ifndef TABLA_HASH
#define TABLA_HASH

#include <cassert>
#include "Tabla.h"
#include "ListImp.cpp"
#include "../funciones/enteros.cpp"

template <class K, class V>
class TablaHashAbierto : public Tabla<K, V>
{
private:
    //Array de listas de pares
    List<ClaveValor<K,V>>** buckets;

    int size = 0;
    int count = 0;

    //Puntero a una función que toma K y retorna int. Esta es la función de hash
    int (*fnHash) (K);

    int posHash(K clave){
        return abs(this->fnHash(clave)) % this->size;
    }

public:

    TablaHashAbierto (int initialSize, int(*fn)(K)) {
        this->size = siguientePrimo(initialSize * 1.5); // factor de carga de 1.5
        buckets = new List<ClaveValor<K,V>>*[this->size];
        for (int i=0; i<this->size; i++){
            buckets[i] = nullptr; // inicializa el array en null
        }
        this->fnHash = fn;
    }

    void insert(K key, V value) override {
        this->remove(key); //Si ya existe nos aseguramos de borrarlo primero

        int pos = posHash(key);

        if (this->buckets[pos] = nullptr){
            this->buckets[pos] = new ListImp<ClaveValor<K,V>>();
        }

        this->buckets[pos]->insert(new ClaveValor<K,V>(key, value));
    }

    V get(K key) override {
        
    }
    void remove(K key) override {
        
    }

    int getCount() override {
        return this->count;
    }

};

#endif