#ifndef TABLA_HASH
#define TABLA_HASH

#include <cassert>
#include "KeyValue.h"
#include "Tabla.h"
#include "LinkedList.cpp"
#include "../funciones/enteros.cpp"

template <class K, class V>
class TablaHashAbierto : public Tabla<K, V>
{
private:
    //Array de listas de pares
    List<KeyValue<K,V>>** buckets;

    float maxLoadFactor = 2.0;
    float minLoadFactor = 0.8;

    int size = 0;
    int count = 0;

    //Puntero a una función que toma K y retorna int. Esta es la función de hash
    int (*fnHash) (K);

    int posHash(K clave, int tSize){
        return abs(this->fnHash(clave)) % tSize;
    }

    // void rehash(bool shrink)
    // {
    //     int newSize = siguientePrimo(shrink ? size * 0.6 : size * 2.0);
    //     List<ClaveValor<K,V>>** bucketsNew = new LinkedList<ClaveValor<K,V>>*[newSize];
    //     for (int i=0; i<newSize; i++){
    //         bucketsNew[i] = nullptr; // inicializa el array en null
    //     }
    //     for (int i = 0; i < size; i++)
    //     {
    //         List<ClaveValor<K,V>>* bucket =this->buckets[i];
    //         if (bucket != nullptr)
    //         {
    //             bucketsNew[i] = bucket;
    //             delete bucket;
    //         }
    //     }
    //     delete[] buckets;
    //     buckets = bucketsNew;
    //     size = newSize;
    // }

    float loadFactor()
    {
        return static_cast<float>(count) / size;
    }

public:

    void printTable(){
        std::cout << "size: " << this->size << ". count: " << this->count << ". load: " << loadFactor() << ". { " << std::endl;
        for (int i=0; i<this->size; i++){
           if (this->buckets[i] == nullptr) std::cout << "   null," << std::endl;
           else {
                List<KeyValue<K,V>>* bucket = this->buckets[i];
                std::cout << "   [ ";
                for (int j=0; j<bucket->getSize(); j++){
                    KeyValue<K,V> kv = bucket->get(j);
                    std::cout << "(" << kv.key<< "," << kv.value << "), ";
                }
                std::cout << "], " << std::endl;
           }
        }
        std::cout << "}" << std::endl;
    }

    TablaHashAbierto (int initialSize, int(*fn)(K)) {
        this->size = siguientePrimo(initialSize * 1.5); // factor de carga de 1.5
        buckets = new List<KeyValue<K,V>>*[this->size];
        for (int i=0; i<this->size; i++){
            buckets[i] = nullptr; // inicializa el array en null
        }
        this->fnHash = fn;
    }

    void insert(K key, V value) override {
        this->remove(key); //Si ya existe nos aseguramos de borrarlo primero

        int pos = posHash(key, this->size);

        if (this->buckets[pos] == nullptr){
            this->buckets[pos] = new LinkedList<KeyValue<K,V>>();
        }

        this->buckets[pos]->insert(KeyValue<K,V>(key, value));

        count++;

        // if (factorDeCarga() > maxFactorCarga){
        //     rehash(false);
        // }
    }

    V get(K key) override {
        int pos = posHash(key, this->size);

        List<KeyValue<K,V>>* bucket = this->buckets[pos];

        assert(bucket != nullptr && !bucket->isEmpty());
        
        KeyValue<K,V> testKV = KeyValue<K,V>(key);

        bool contains = bucket->contains(testKV);
        assert(contains);
        return bucket->getElement(testKV).value;
    }

    bool contains(K key) override {
        int pos = posHash(key, this->size);

        List<KeyValue<K,V>>* bucket = this->buckets[pos];

        if (bucket == nullptr || bucket->isEmpty()) return false;

        KeyValue<K,V> testKV = KeyValue<K,V>(key);
        return bucket->contains(testKV);
    }
    
    void remove(K key) override {
        int pos = posHash(key, this->size);

        List<KeyValue<K,V>>* bucket = this->buckets[pos];

        if (bucket == nullptr || bucket->isEmpty()) return;

        KeyValue<K,V> testKV = KeyValue<K,V>(key);
        if (bucket->remove(testKV)){
            count--;
        }
        
        if (bucket->isEmpty()) {
            delete(bucket);
            this->buckets[pos] = nullptr;
        }

        // if (factorDeCarga() < minFactorCarga){
        //     rehash(true);
        // }
    }

    int getCount() override {
        return this->count;
    }

};

#endif