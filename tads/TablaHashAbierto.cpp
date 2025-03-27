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

    void printTable(){
        std::cout << "{ " << std::endl;
        for (int i=0; i<size; i++){
            if (this->buckets[i] == nullptr) std::cout << "   null," << std::endl;
            else {
                List<ClaveValor<K,V>>* bucket = this->buckets[i];
                std::cout << "   [ ";
                for (int j=0; j<bucket->getSize(); j++){
                    ClaveValor<K,V> kv = bucket->get(j);
                    std::cout << "(" << kv.clave<< "," << kv.valor << "), ";
                }
                std::cout << "], " << std::endl;
            }
        }
        std::cout << "}" << std::endl;
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

        if (this->buckets[pos] == nullptr){
            this->buckets[pos] = new ListImp<ClaveValor<K,V>>();
        }

        this->buckets[pos]->insert(ClaveValor<K,V>(key, value));

        count++;
    }

    V get(K key) override {
        int pos = posHash(key);

        List<ClaveValor<K,V>>* bucket = this->buckets[pos];

        assert(bucket != nullptr && !bucket->isEmpty());
        
        ClaveValor<K,V> testKV = ClaveValor<K,V>(key);

        bool contains = bucket->contains(testKV);
        assert(contains);
        return bucket->getElement(testKV).valor;
    }

    bool contains(K key) override {
        int pos = posHash(key);

        List<ClaveValor<K,V>>* bucket = this->buckets[pos];

        if (bucket == nullptr || bucket->isEmpty()) return false;

        ClaveValor<K,V> testKV = ClaveValor<K,V>(key);
        return bucket->contains(testKV);
    }
    
    void remove(K key) override {
        int pos = posHash(key);

        List<ClaveValor<K,V>>* bucket = this->buckets[pos];

        if (bucket == nullptr || bucket->isEmpty()) return;

        ClaveValor<K,V> testKV = ClaveValor<K,V>(key);
        if (bucket->remove(testKV)){
            count--;
        }
        
        if (bucket->isEmpty()) {
            delete(bucket);
            this->buckets[pos] = nullptr;
        }
    }

    int getCount() override {
        return this->count;
    }

};

#endif