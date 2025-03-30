#ifndef HASH_FUNC
#define HASH_FUNC

#include <string>
#include <iostream>

//Las funciones son identicas, pero no pasamos el numero como parametro ya que 
//necesitamos pasar la referencia a la función y C++ no tiene currificación o lambdas
//djb2
int stringHash1(std::string dato)
{
    unsigned long hash = 5381;
    char c;
    for (int i=0; i<dato.length(); i++){
        c = dato.at(i);
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}
int stringHash2(std::string dato)
{
    unsigned long hash = 10771;
    char c;
    for (int i=0; i<dato.length(); i++){
        c = dato.at(i);
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

#endif