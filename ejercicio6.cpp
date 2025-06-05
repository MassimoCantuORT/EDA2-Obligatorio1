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
    
    bool operator==(Building other) {
        return this->posStart == other.posStart && this->posEnd == this->posEnd && this->height == this->height; 
    }
};

struct Point{
    int pos;
    int height;

    bool operator==(Point other) {
        return this->pos == other.pos && this->height == this->height; 
    }
};

List<Point>* trivialSolve(List<Building>* buildings){
    List<Point>* ret = new LinkedList<Point>();
    Building building = buildings->get(0);
    ret->insert(Point{building.posStart, building.height});
    ret->insert(Point{building.posEnd, 0});
    return ret;
}

int max(int a, int b){
    return a > b ? a : b;
}

List<Point>* merge(List<Point>* pairs1, List<Point>* pairs2){
    int maxHeight = 0;
    Iterator<Point>* iter1 = pairs1->iterator();
    Iterator<Point>* iter2 = pairs2->iterator();
    int currentHeight1 = 0;
    int currentHeight2 = 0;
    int currentX = 0;
    List<Point>* results = new LinkedList<Point>();
    while (iter1->hasNext() && iter2->hasNext()){
        Point point1 = iter1->peek();
        Point point2 = iter2->peek();
        
        //Matamos el menor X
        if (point1.pos < point2.pos){
            //actualizamos 1, porque es el menor
            currentHeight1 = point1.height;
            currentX = point1.pos;
            iter1->next();
        } else if (point1.pos > point2.pos){
            //actualizamos 2, porque es el menor
            currentHeight2 = point2.height;
            currentX = point2.pos;
            iter2->next();
        } else {
            //son iguales asi que actualizamos ambos
            currentHeight1 = point1.height;
            currentHeight2 = point2.height;
            currentX = point1.pos;
            iter1->next();
            iter2->next();
        }

        //Calculamos la actura maxima en la posición actual e insertamos el resultado si cambia
        int currentMaxHeight = max(currentHeight1, currentHeight2);
        if (maxHeight !=  currentMaxHeight){
            maxHeight = currentMaxHeight;
            results->insert(Point{currentX, maxHeight});
        }
    }
    //insertamos lo que sobró
    while (iter1->hasNext()){
        results->insert(iter1->next());
    }
    
    while (iter2->hasNext()){
        results->insert(iter2->next());
    }
    return results;
}

List<Point>* DivideAndConquer(List<Building>* buildings){
    if (buildings->getSize() == 0)
        return new LinkedList<Point>();
    if (buildings->getSize() == 1)
		return trivialSolve(buildings);
	//Divide
    List<Building>* left = new LinkedList<Building>();
	List<Building>* right = new LinkedList<Building>();
    int len  = buildings->getSize();
    for (int i=0; i<len; i++){
        if (i < len/2){
            left->insert(buildings->get(i));
        } else {
            right->insert(buildings->get(i));
        }
    }

	//Conquer
	List<Point>* s1 = DivideAndConquer(left);
	List<Point>* s2 = DivideAndConquer(right);
	//Merge
	return merge(s1, s2);
}

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
    
    List<Point>* result = DivideAndConquer(buildings);

    Iterator<Point>* iter = result->iterator();
    while (iter->hasNext()){
        Point pair = iter->next();
        cout << pair.pos << " " << pair.height << endl;
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