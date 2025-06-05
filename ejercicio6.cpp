#include <cassert>
#include <string>
#include <iostream>
#include <limits>

#include "tads/LinkedList.cpp"

using namespace std;

struct Building{
    int posStart;
    int posEnd;
    int height;
};

int main()
{
    int cantBuildings;
    cin >> cantBuildings;

    List<Building>* buildings = new LinkedList<Building>();

    for (int b = 0; b < cantBuildings; b++)
    {
        int i, f, h;
        cin >> i >> f >> h;
        buildings->insert(Building{i, f, h});
    }
    


    return 0;
}

//Dada una vista horizontal de una ciudad que consta únicamente de edificios rectangulares, 
//le piden diseñar un algoritmo que dada la ubicación y altura exacta de los edificios de la ciudad, 
//halle la “silueta” o línea de corte de todos los edificios con el cielo, es decir, la silueta de todos los edificios juntos, 
//pero eliminando las intersecciones ocultas entre los mismos.

//Los mismos se representarán mediante la secuencia de ternas [(2,9,10), (3,7,15), (5,12,12), (15,20,10), (19,24,8)]. 
//Donde cada terna (I,F,H), representa:

//I: Coordenada en el eje horizontal donde comienza el edificio
//F: Coordenada en el eje horizontal donde termina el edificio
//H: La altura del edificio
//Se pide imprimir una secuencia de pares (x,h) que representan una posicion de la cual a partir de 
//la posicion x la figura tiene altura h. De esta forma, podemos representar la misma silueta utilizando menos memoria.

//Aclaraciones:
//No incluir el par (0,0)
//No puede haber dos pares seguidos con la misma altura.

//Implementar la solucion con la tactica de Divide & Conquer
//O(N∗log N) siendo N la cantidad de edificios.