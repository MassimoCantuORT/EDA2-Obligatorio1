#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    // TODO
    return 0;
}

//Dado un grafo dirigido, ponderado (sin costos negativos) y disperso, implementar un algoritmo 
//que devuelva el costo total de los caminos más cortos desde un vértice dado a todos los demás.

//La entrada está estructurada de la siguiente manera:
//  V
//  E
//  v_1 w_1 c_1
//  v_2 w_2 c_2
//  ...
//  v_E w_E c_E
//  N
//  u_1
//  u_2
//  ...
//  u_N
//Donde:
//- V es la cantidad de vértices.
//- E es la cantidad de aristas.
//- Las siguientes E líneas contienen las aristas dirigidas desde el vértice v_i al vértice w_i con costo c_i.
//- Luego, un número N que indica la cantidad de vértices desde los cuales se desea conocer la menor distancia hacia los demás.
//- Seguido por N líneas, cada una representando un vértice u desde el cual se quiere calcular la distancia.

//Imprimir N × V líneas con los costos del camino más corto desde cada vértice seleccionado hacia todos los demás vértices, 
//siguiendo el formato:
//Si no existe camino o es el mismo vértice origen, imprimir -1.
//  C_{1,1}
//  C_{1,2}
//  ...
//  C_{1,V}
//  ...
//  C_{N,1}
//  ...
//  C_{N,V}

//- Utilizar el algoritmo de Dijkstra con cola de prioridad eficiente (heap).
//- Complejidad esperada: O((V+E) log V)