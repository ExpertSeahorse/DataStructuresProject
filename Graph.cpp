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
    
}

void Graph::removeEdge(std::string label1, std::string label2){

}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){

}