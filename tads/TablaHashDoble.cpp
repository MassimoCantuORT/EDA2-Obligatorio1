#ifndef TABLA_HASH_DOBLE
#define TABLA_HASH_DOBLE

#include <cassert>
#include "Tabla.h"
#include "../funciones/enteros.cpp"

template <class K, class V>
class TablaHashDoble : public Tabla<K, V>
{
private:

    //Array de pares
    KeyValue<K,V>** table;
    //Guardamos si el valor fue borrado o no
    bool* erased;

    int size = 0;
    int count = 0;

    //Puntero a una función que toma K y retorna int. Esta es la función de hash
    int (*fnHash1) (K);
    int (*fnHash2) (K);

    int normalizedHash(K dato, int attempt, int tSize)
    {
        return abs((fnHash1(dato) + attempt * fnHash2(dato)) % tSize);
    }

    float loadFactor()
    {
        return static_cast<float>(count) / size;
    }

public:

    void printTable(){
        std::cout << "size: " << this->size << ". count: " << this->count << ". load: " << loadFactor() << ". { " << std::endl;
        for (int i=0; i<this->size; i++){
           if (this->table[i] == nullptr) std::cout << "   null ["<< (erased[i]?"X":" ") <<"]," << std::endl;
           else {
                KeyValue<K,V>* kv = this->table[i];
                std::cout << "   (" << kv->key << "," << kv->value << "), " << std::endl;
           }
        }
        std::cout << "}" << std::endl;
    }

    TablaHashDoble (int initialSize, int(*fn1)(K),  int(*fn2)(K)) {
        this->size = siguientePrimo(initialSize * 1.5); // factor de carga de 1.5
        table = new KeyValue<K,V>*[this->size];
        erased = new bool[this->size];
        for (int i=0; i<this->size; i++){
            table[i] = nullptr; // inicializa el array en null
            erased[i] = false;
        }
        this->fnHash1 = fn1;
        this->fnHash2 = fn2;
    }

    void insert(K key, V value) override {
        int maxTries = this->size;
        int pos;
        bool inserted = false;
        for (int i = 0; i < maxTries; i++)
        {
            pos = normalizedHash(key, i, this->size);
            if (this->table[pos] == nullptr){
                this->table[pos] = new KeyValue<K,V>(key, value);
                inserted = true;
                break;
            } else {
                KeyValue<K,V>* kv = this->table[pos];
                if (kv->key == key){
                    kv->value = value;
                    inserted = true;
                    break;
                } 
                // Si llegamos a este punto entonces la posición en la tabla está ocupada por otro valor.
                // Se hace otro intento recalculando la posición con el for loop.
            }
        }
        if (inserted){
            erased[pos] = false;
            this->count++;
        } else {
            assert(false); //Falló la inserción de alguna manera
        }
        
    }

    V get(K key) override {
        int maxTries = this->size;
        int pos;
        bool inserted = false;
        for (int i = 0; i < maxTries; i++)
        {
            pos = normalizedHash(key, i, this->size);
            if (this->table[pos] == nullptr){
                if (!erased[pos]){
                    assert(false); //Es null y no esta marcado como borrado, entonces no existe.
                }
            } else {
                KeyValue<K,V>* kv = this->table[pos];
                if (kv->key == key){
                    return kv->value;
                } 
                // Si llegamos a este punto entonces la posición en la tabla está ocupada por otro valor.
                // Se hace otro intento recalculando la posición con el for loop.
            }
        }
        //No se como podriamos llegar acá pero si sucede no existe el elemento.
        assert(false);
    }

    void remove(K key) override {
        int maxTries = this->size;
        int pos;
        bool inserted = false;
        for (int i = 0; i < maxTries; i++)
        {
            pos = normalizedHash(key, i, this->size);
            if (this->table[pos] == nullptr){
                if (!erased[pos]){
                    return; //Es null y no esta marcado como borrado, entonces no existe.
                }
            } else {
                KeyValue<K,V>* kv = this->table[pos];
                if (kv->key == key){
                    delete kv;
                    this->table[pos] = nullptr;
                    erased[pos] = true;
                    this->count--;
                    return;
                } 
                // Si llegamos a este punto entonces la posición en la tabla está ocupada por otro valor.
                // Se hace otro intento recalculando la posición con el for loop.
            }
        }
    }

    bool contains(K key) override {
        int maxTries = this->size;
        int pos;
        bool inserted = false;
        for (int i = 0; i < maxTries; i++)
        {
            pos = normalizedHash(key, i, this->size);
            if (this->table[pos] == nullptr){
                if (!erased[pos]){
                    return false; //Es null y no esta marcado como borrado, entonces no existe.
                }
            } else {
                KeyValue<K,V>* kv = this->table[pos];
                if (kv->key == key){
                    return true;
                } 
                // Si llegamos a este punto entonces la posición en la tabla está ocupada por otro valor.
                // Se hace otro intento recalculando la posición con el for loop.
            }
        }
        //No se como podriamos llegar acá pero si sucede no existe el elemento.
        return false;
    }

    int getCount() override {
        return this->count;
    }

};

#endif