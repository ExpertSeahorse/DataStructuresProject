#include <list>

#include "GraphBase.hpp"


#ifndef VERTEX_H
#define VERTEX_H

class Vertex{
    friend class Graph; 
    protected:
    std::string label;
    std::list<Vertex*> adjacent;

    public:
    Vertex(const std::string l, const std::list<Vertex*> adj): label(l), adjacent(adj) {};
    Vertex(const std::string l): Vertex(l, std::list<Vertex*>()) {};
    Vertex(): Vertex("", std::list<Vertex*>()) {};

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
    unsigned long weight;

    public:
    Edge(Vertex* vtx1, Vertex* vtx2, unsigned int w): end1(vtx1), end2(vtx2), weight(w) {};
};

#endif


#ifndef GRAPH_H
#define GRAPH_H


class Graph : public GraphBase{
    private:
    std::list<Vertex> vertices;
    unsigned int size_v = 0;
    std::list<Edge> edges;
    unsigned int size_e = 0;

    std::list<Vertex>::iterator findVertex(std::string);
    std::list<Edge>::iterator findEdge(std::string, std::string);
    std::list<std::string>::const_iterator minDistance(const std::map<std::string, unsigned long>& dist, const std::list<std::string>& vtxs);

    public:
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
};

#endif