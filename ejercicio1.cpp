#include <cassert>
#include <string>
#include <iostream>
#include <limits>

#include "tads/TablaHashAbierto.cpp"

using namespace std;

int hasha(int key){
    return key;
}

int main()
{
    TablaHashAbierto<int, string>* table = new TablaHashAbierto<int,string>(5, hasha);

    table->insert(5, "hola");
    table->insert(4, "ads");
    table->insert(2, "gfd");
    table->insert(2, "hgdg");
    table->insert(100, "qweqds");

    cout << table->get(4);

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