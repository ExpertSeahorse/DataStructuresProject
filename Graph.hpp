#include "GraphBase.hpp"


#ifndef VERTEX_H
#define VERTEX_H

class Vertex{
    friend class Graph; 

    protected:
    std::string label;
    std::list<Vertex> adjacent;
};

#endif


#ifndef EDGE_H
#define EDGE_H

class Edge{
    friend class Graph; 

    protected:
    int weight;
    Vertex *end1, *end2;
};

#endif


#ifndef GRAPH_H
#define GRAPH_H

#include <list>

class Graph : public GraphBase{
    private:
    std::list<Vertex> vertices;
    std::list<Edge> edges;

    public:
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);

};

#endif