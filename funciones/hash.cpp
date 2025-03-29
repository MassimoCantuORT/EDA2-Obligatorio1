#ifndef HASH_FUNC
#define HASH_FUNC

#include <string>
#include <cstring>
#include <iostream>

//Las funciones son identicas, pero no pasamos el numero como parametro ya que 
//necesitamos pasar la referencia a la función y C++ no tiene currificación o lambdas
int intHash1(int dato)
{
    int magicNum1 = 0x45d9f3b;
    int newDato = ((dato >> 16) ^ dato) * magicNum1;
    newDato = ((newDato >> 16) ^ newDato) * magicNum1;
    newDato = (newDato >> 16) ^ newDato;
    return newDato;
}
int intHash2(int dato)
{
    int magicNum2 = 0x846ca68b;
    int newDato = ((dato >> 16) ^ dato) * magicNum2;
    newDato = ((newDato >> 16) ^ newDato) * magicNum2;
    newDato = (newDato >> 16) ^ newDato;
    return newDato;
}

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

#endif