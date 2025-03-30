#include <cassert>
#include <string>
#include <iostream>
#include <limits>

#include "tads/TablaHashDoble.cpp"
#include "funciones/hash.cpp"

using namespace std;

int main()
{
    int cantDict;
    cin >> cantDict;

    TablaHashDoble<string, int>* table = new TablaHashDoble<string, int>(cantDict, stringHash1, stringHash2);

    string palabra;
    for (int i = 0; i < cantDict; i++)
    {
        cin >> palabra;
        //el valor es un dato "dummy" ya que no se va a usar
        table->insert(palabra, i);
    }
    
    //table->printTable();

    int cantConsulta;
    cin >> cantConsulta;
    for (int i = 0; i < cantConsulta; i++)
    {
        cin >> palabra;
        //el valor es un dato "dummy" ya que no se va a usar
        bool contains = table->contains(palabra);

        cout << (contains ? "1" : "0") << endl;
    }

    return 0;
}

//Se tiene un diccionario con palabras almacenadas, y se quiere verificar si una serie de palabras 
//dadas están contenidas en dicho diccionario. Para esto, implementar una solución usando una tabla 
//de hash cerrado con resolución de colisiones mediante doble hashing.
// - La primera línea contiene un entero N (1 ≤ N ≤ 10^6), indicando la cantidad de palabras en el diccionario.
// - Las siguientes N líneas contienen cada una una palabra del diccionario, cada una con una longitud máxima de 20 caracteres.
// - Luego, una línea contiene un entero M (1 ≤ M ≤ 10^6), indicando la cantidad de palabras a consultar.
// - Las siguientes M líneas contienen cada una una palabra para verificar si existe en el diccionario.
//Imprimir M líneas, una por cada palabra de consulta, indicando:
// - 1 si la palabra existe en el diccionario.
// - 0 si la palabra no existe en el diccionario.