#ifndef GRAFO_H
#define GRAFO_H

#include "Iterator.h"

struct Edge{
    int from;
    int to;
    int weight;

    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
    Edge(int f, int t) : from(f), to(t), weight(0) {}

    bool operator==(const Edge &other) const {
        return this->from == other.from && this->to == other.to;
    }
};

class Graph
{
public:
    virtual Iterator<Edge>* getAllEdges() = 0;
    virtual int edgeCount() = 0;
    virtual int vertexCount() = 0;
    virtual Iterator<Edge>* getAdjacentEdges(int v) = 0;
    virtual bool hasEdge(int v1, int v2) = 0;
    virtual int getWeight(int v1, int v2) = 0;
    virtual void addEdge(int v1, int v2) = 0;
    virtual void addEdge(int v1, int v2, int weight) = 0;
    virtual void removeEdge(int v1, int v2) = 0;
    virtual int** getAdjMatrix() = 0;
};

#endif