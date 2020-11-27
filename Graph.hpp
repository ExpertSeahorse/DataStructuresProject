#include <list>

#include "GraphBase.hpp"


#ifndef VERTEX_H
#define VERTEX_H

class Vertex{
    friend class Graph; 
    protected:
    std::string label;
    std::list<Vertex> adjacent;

    public:
    Vertex(const std::string l, const std::list<Vertex> adj): label(l), adjacent(adj) {};
    Vertex(const std::string l): Vertex(l, std::list<Vertex>()) {};
    Vertex(const Vertex &v) { label=v.label; adjacent=v.adjacent; };    // Copy
};

#endif


#ifndef EDGE_H
#define EDGE_H

class Edge{
    friend class Graph; 
    protected:
    Vertex *end1;
    Vertex *end2;
    int weight;

    public:
    Edge(Vertex* vtx1, Vertex* vtx2, int w): end1(vtx1), end2(vtx2), weight(w) {};
    Edge(Vertex* vtx1, Vertex* vtx2): Edge(vtx1, vtx2, -1) {};
};

#endif


#ifndef GRAPH_H
#define GRAPH_H


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