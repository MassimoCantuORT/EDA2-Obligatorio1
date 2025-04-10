#include <cassert>
#include <string>
#include <iostream>
#include <limits>

#include "tads/ListGraph.cpp"
#include "tads/MinPriorityQueue.cpp"

using namespace std;

void printMatrix(int** matrix, int verts){
    cout << "   || ";
    for (int i = 1; i <= verts; i++) {
        cout << i << (i < 10 ? "  | " : (i<100? " | " : "| "));
    }
    cout << endl << "=====";
    for (int i = 1; i <= verts; i++) {
        cout << "=====";
    }
    cout << endl;
    for (int i = 1; i <= verts; i++) {
        cout << i << (i < 10 ? "  || " : (i<100? " || " : "|| "));
        for (int j = 1; j <= verts; j++) {
            int w = matrix[i][j];
            if (w == -1) cout << "   | ";
            else {
                cout << w << (w < 10 ? "  | " : " | ");
            }
        }
        cout << endl;
    }
}

int* dijkstra (Graph* g, int origin){
    int v = g->vertexCount();
    int* costos = new int[v+1];
    for (int i=1; i<=v; i++){
        costos[i] = INT_MAX; //inicializamos en INT_MAX para facilitar los calculos, pero despues los vamos a settear en -1
    }
    costos[origin] = 0; //inicializamos en 0 para facilitar los calculos, pero despues lo vamos a settear en -1

    int* comingFrom = new int[v+1]();
    comingFrom[origin] = origin;

	PriorityQueue<int, int>* pq = new MinPriorityQueue<int, int>(v+1);
	pq->enqueue(origin, 0);
	while (!pq->isEmpty()){
		int v = pq->dequeue();
        Iterator<Edge>* adj = g->getAdjacentEdges(v);
		while (adj->hasNext()){
            Edge e = adj->next();
            int v2 = e.to;
			if (costos[v2] > costos[v] + e.weight){
				costos[v2] = costos[v] + e.weight;
				comingFrom[v2] = v;
				pq->enqueue(v2, costos[v2]);
			}
		}
	}

    //comingFrom no se utiliza por ahora
    return costos;
}

int main()
{
    //READ
    int verts, edges;
    cin >> verts;
    cin >> edges;

    Graph* g = new ListGraph(verts, true, true);
    for (int i = 0; i < edges; i++) {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        g->addEdge(v1, v2, w);
    }

    int calcVerts;
    cin >> calcVerts;

    for (int i = 0; i < calcVerts; i++) {
        int v;
        cin >> v;
        int* minTotalCosts = dijkstra(g, v);
        minTotalCosts[v] = -1; //La letra pide que el mismo vert sea -1
        for (int j = 1; j <= verts; j++) {
            if (minTotalCosts[j] == INT_MAX) minTotalCosts[j] = -1; //los vertices sin alcanzar tambien deberian ser -1
            cout << minTotalCosts[j] << endl;
        }
    }

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