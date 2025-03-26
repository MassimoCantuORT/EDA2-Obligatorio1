#ifndef TABLA_HASH_DOBLE
#define TABLA_HASH_DOBLE

#include "Tabla.h"
#include <cassert>

template <class K, class V>
class TablaHashDoble : public Tabla<K, V>
{
private:

    //Puntero a una función que toma K y retorna int. Esta es la función de hash
    int (*fnHash1) (K);
    int (*fnHash2) (K);

public:

};

#endif