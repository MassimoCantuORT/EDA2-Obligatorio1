#include <cassert>
#include <string>
#include <iostream>
#include <limits>

#include "tads/HashTableOpen.cpp"
#include "funciones/hash.cpp"

using namespace std;

int main()
{
    int cantObjetos;
    cin >> cantObjetos;

    HashTableOpen<string, int>* table = new HashTableOpen<string, int>(cantObjetos, stringHash1);

    string mail;
    for (int i = 0; i < cantObjetos; i++)
    {
        cin >> mail;
        //el valor es un dato "dummy" ya que no se va a usar
        table->insert(mail, i);
    }
    cout << table->getCount() << endl;

    return 0;
}

//Se tiene una base de datos de usuarios identificados por su dirección de correo electrónico. 
//Se detectó que existen usuarios duplicados (que comparten el mismo e-mail). 
//El objetivo es determinar cuántos usuarios únicos hay en realidad.
//- La primera línea contiene un entero positivo N (2 ≤ N ≤ 10^5), que indica el número de usuarios registrados actualmente en el sistema.
//- Las siguientes N líneas contienen cada una un correo electrónico registrado.
//- Imprimir un único entero: la cantidad total de usuarios únicos (sin repetidos).
//- Se debe usar una tabla hash abierta.
//- Resolver con complejidad temporal promedio O(N), siendo N la cantidad de usuarios en el sistema.