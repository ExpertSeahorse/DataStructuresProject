#include "Graph.hpp"


void Graph::addVertex(std::string label){
    // Move through the current vertices. If there is a vertex with label already, throw. Else add a new vertex
    for (Vertex v : vertices){
        if (v.label == label)
            throw 1;
    }
    vertices.emplace_back(label);
}

void Graph::removeVertex(std::string label){
    // remove vertex with label from list
    std::string s = "";
    for (auto i = vertices.begin(); i != vertices.end(); i++){
        if (i->label == label){
            s = i->label;
            vertices.erase(i);
            break;
        }
    }

    // if no match
    if (s == "")
        throw 1;

    // remove all edges connected to vertex from list
    for (auto i = edges.begin(); i != edges.end(); i++){
        if ((s == i->end1->label) || (s == i->end2->label))
            edges.erase(i);
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    // no circular edges
    if (label1 == label2)
        throw 1;

    // Get labels' vertices from list
    bool one=false, two=false;
    Vertex *vtx1, *vtx2;
    for(Vertex vtx : vertices){
        if (vtx.label == label1){
            vtx1 = &vtx;
            one = true;
        }
        else if (vtx.label == label2){
            vtx2 = &vtx;
            two = true;
        }
    }

    // if either of the vertices weren't found, error
    if (one && two)
        throw 1;

    // Create an edge and add both vertices to each others' adjacency lists
    edges.emplace_back(vtx1, vtx2, weight);
    vtx1->adjacent.emplace_back(*vtx2);
    vtx2->adjacent.emplace_back(*vtx1);
}

void Graph::removeEdge(std::string label1, std::string label2){

    for (auto i = edges.begin(); i != edges.end(); i++){
        if (((i->end1->label == label1) || (i->end1->label == label2)) && ((i->end2->label == label1) || (i->end2->label == label2)))
            edges.erase(i);
    }
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
    return -1;
}