#include <cassert>
#include <string>
#include <iostream>
#include <limits>

#include "tads/ListGraph.cpp"
#include "tads/MinPriorityQueue.cpp"

using namespace std;

//usamos orden topológico (algoritmo de Kahn)
bool findAllCycles(Graph* g){
    int v = g->vertexCount();
    int visited = 0;
    int* vertDegree = new int[v+1]();

    //colocamos los grados
    for (int i=1; i<=v; i++){ //O(E)
        Iterator<Edge>* edges = g->getAdjacentEdges(i);
        while (edges->hasNext()){ 
            Edge e = edges->next();
            vertDegree[e.to]++;
        }
    }

    //Una queue regular sirve, pero uso priority queue para no tener que programar otro tad
    PriorityQueue<int, int>* queue = new MinPriorityQueue<int, int>(v + 1); //queue y dequeue O(1) c.p

    for (int i=1; i<=v; i++){ //O(V)
        if (vertDegree[i] == 0){
            queue->enqueue(i, i);
        }
    }
    
    while (!queue->isEmpty()){ //O(V + E) p.c
        int next = queue->dequeue(); 
        visited++;

        //bajamos el grado de incidencia de los vertices adjacentes
        Iterator<Edge>* edges = g->getAdjacentEdges(next); //cada E se visita una sola vez asi que peor caso de todo es O(E)
        while (edges->hasNext()){
            Edge e = edges->next();
            vertDegree[e.to]--;
            if (vertDegree[e.to] == 0){
                queue->enqueue(e.to, e.to);
            }
        }
    }

    return visited != v; //Si no visitamos todos entonces el algoritmo terminó antes. Esto solo sucede si hay un ciclo.
}

int main()
{
    int verts, edges;
    cin >> verts;
    cin >> edges;

    Graph* g = new ListGraph(verts, true, false);
    for (int i = 0; i < edges; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        g->addEdge(v1, v2);
    }

    bool hasCycle = findAllCycles(g);

    cout << (hasCycle ? 1 : 0);

    return 0;
}

//Dado un grafo disperso, dirigido y sin ponderar, implementar un algoritmo eficiente que determine si existe al menos un ciclo en él.
//La entrada debe seguir este formato:
//V
//E
//v1 w1
//v2 w2
//...
//vE wE
//Donde:
//V es la cantidad de vértices.
//E es la cantidad de aristas.
//Las siguientes E líneas indican las aristas dirigidas del vértice vi al vértice wi.

//Salida
//Imprimir una sola línea con:
//1 si el grafo contiene al menos un ciclo.
//0 si el grafo no contiene ciclos.

//Complejidad temporal: O(V+E).