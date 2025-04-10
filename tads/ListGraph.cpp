#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include <climits>
#include "Graph.h"
#include "LinkedList.cpp"

class ListGraph : public Graph {
    //El peso es -1 cuando la arista no existe (importante)
    const int NO_EDGE_WEIGHT = -1;

    bool directed;
    bool weighted;

    List<Edge>** adjacencies;
    int vertices;
    int edgeCount;
    
    bool vertExists(int v){
        return v <= vertices && v > 0;
    }

public:

    ListGraph(int size, bool directed, bool weighted){
        vertices = size;
        adjacencies = new List<Edge>*[vertices+1];
        for (int i=1; i<=vertices; i++){
            adjacencies[i] = new LinkedList<Edge>();
        }
        this->directed = directed;
        this->weighted = weighted;
    }

    Iterator<Edge>* getAllEdges() {
        //TO-DO
        assert(false);
    }
    int vertexCount() {
        return this->vertices;
    }
    Iterator<Edge>* getAdjacentEdges(int v) {
        assert(vertExists(v));
        return adjacencies[v]->iterator();
    }
    bool hasEdge(int v1, int v2) {
        assert(vertExists(v1) && vertExists(v2));
        
        Iterator<Edge>* neighbors = getAdjacentEdges(v1);
        while (neighbors->hasNext()){
            Edge edge = neighbors->next();
            if (edge.to == v2) return true;
        }
        return false;
    }
    int getWeight(int v1, int v2) {
        assert(vertExists(v1) && vertExists(v2));
        Iterator<Edge>* neighbors = getAdjacentEdges(v1);
        while (neighbors->hasNext()){
            Edge edge = neighbors->next();
            if (edge.to == v2) return edge.weight;
        }
        return NO_EDGE_WEIGHT; //la arista no existe
    }
    void addEdge(int v1, int v2, int weight) {
        assert(vertExists(v1) && vertExists(v2));
        assert(weight >= 0);
        removeEdge(v1, v2);
        
        adjacencies[v1]->insert(Edge(v1, v2, weight));
        edgeCount++;
    }
    void removeEdge(int v1, int v2) {
        assert(vertExists(v1) && vertExists(v2));
        adjacencies[v1]->remove(Edge(v1, v2));
        edgeCount--;
    }
    int** getAdjMatrix() {
        int** matrix = new int*[vertices+1];
        for (int i=1; i<=vertices; i++){
            matrix[i] = new int[vertices+1];
            List<Edge>* adj = adjacencies[i];
            for (int j=1; j<=vertices; j++){
                Edge edge = Edge(i, j);
                if (adj->contains(edge)){
                    matrix[i][j] = adj->getElement(edge).weight;
                } else {
                    matrix[i][j] = NO_EDGE_WEIGHT;
                }
                
            }
        }
        return matrix;
    }
};

#endif