#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include <climits>
#include "Graph.h"
#include "LinkedList.cpp"

class ListGraph : public Graph {
    //El peso es -1 cuando la arista no existe (importante)
    const int NO_EDGE_WEIGHT = -1;
    const int DEFAULT_WEIGHT = 0;

    bool directed;
    bool weighted;

    List<Edge>** adjacencies;
    int vertices;
    int edges;
    
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

    Iterator<Edge>* getAllEdges() override {
        List<Edge>* allEdges = new LinkedList<Edge>();
        for (int i=1; i<=vertices; i++){
            allEdges->insertAll(adjacencies[i]->iterator());
        }
        return allEdges->iterator();
    }
    int edgeCount() override {
        return this->edges;
    }
    int vertexCount() override {
        return this->vertices;
    }
    Iterator<Edge>* getAdjacentEdges(int v) override {
        assert(vertExists(v));
        return adjacencies[v]->iterator();
    }
    bool hasEdge(int v1, int v2) override {
        assert(vertExists(v1) && vertExists(v2));
        
        Iterator<Edge>* neighbors = getAdjacentEdges(v1);
        while (neighbors->hasNext()){
            Edge edge = neighbors->next();
            if (edge.to == v2) return true;
        }
        return false;
    }
    int getWeight(int v1, int v2) override {
        assert(vertExists(v1) && vertExists(v2));

        if (!weighted) return DEFAULT_WEIGHT;

        Iterator<Edge>* neighbors = getAdjacentEdges(v1);
        while (neighbors->hasNext()){
            Edge edge = neighbors->next();
            if (edge.to == v2) return edge.weight;
        }

        return NO_EDGE_WEIGHT; //la arista no existe
    }

    void addEdge(int v1, int v2) override {
        addEdge(v1, v2, DEFAULT_WEIGHT);
    }

    void addEdge(int v1, int v2, int weight) override {
        assert(vertExists(v1) && vertExists(v2));
        assert(weight >= 0);

        if (!weighted) weight = DEFAULT_WEIGHT;

        removeEdge(v1, v2);
        adjacencies[v1]->insert(Edge(v1, v2, weight));

        if (!directed){
            adjacencies[v2]->insert(Edge(v2, v1, weight));
        }

        edges++;
    }
    void removeEdge(int v1, int v2) override {
        assert(vertExists(v1) && vertExists(v2));

        adjacencies[v1]->remove(Edge(v1, v2));

        if (!directed){
            adjacencies[v2]->remove(Edge(v2, v1));
        }

        edges--;
    }

    int** getAdjMatrix() override {
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