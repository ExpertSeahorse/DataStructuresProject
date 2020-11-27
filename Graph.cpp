#include <algorithm>
#include <queue>

#include "Graph.hpp"


void Graph::addVertex(std::string label){
    //If there is a vertex with label already, throw. Else add a new vertex
    auto vertex_exists = [](std::string label){
        return [&](Vertex v) { return (label == v.label); };
    };
    auto i = std::find_if(vertices.begin(), vertices.end(), vertex_exists);

    if (i != vertices.end())
        throw 1;

    vertices.emplace_back(label);
}

void Graph::removeVertex(std::string label){
    // remove vertex with label from list
    auto vertex_exists = [](std::string label){
        return [&](Vertex v) { return (label == v.label); };
    };
    std::size_t s = vertices.size();
    vertices.remove_if(vertex_exists(label));
  
    // If nothing was removed
    if (s == vertices.size())
        throw 1;

    // remove all edges connected to vertex from list
    auto edge_exists = [](std::string label){
        return [&](Edge e) { return ((label == e.end1->label) || (label == e.end2->label)); };
    };

    edges.remove_if(edge_exists(label));

}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    // no circular edges
    if (label1 == label2)
        throw 1;

    // Get labels' vertices from list
    auto vertex_exists = [](std::string label){
        return [&](Vertex v) { return (label == v.label); };
    };
    auto i = std::find_if(vertices.begin(), vertices.end(), vertex_exists(label1));
    auto j = std::find_if(vertices.begin(), vertices.end(), vertex_exists(label2));

    if ((i == vertices.end()) || (j == vertices.end()))
        throw 1;

    Vertex vtx1 = *i;
    Vertex vtx2 = *j;

    // Make sure that there is not an existing edge
    auto k = std::find(edges.begin(), edges.end(), Edge(&vtx1, &vtx2, weight));
    auto l = std::find(edges.begin(), edges.end(), Edge(&vtx2, &vtx1, weight));

    if ((k != edges.end()) || (l != edges.end()))
        throw 1;

    // Create an edge and add both vertices to each others' adjacency lists
    edges.emplace_back(&vtx1, &vtx2, weight);
    vtx1.adjacent.emplace_back(vtx2);
    vtx2.adjacent.emplace_back(vtx1);
}

void Graph::removeEdge(std::string label1, std::string label2){
    // Build a comparator function for remove_if based on the passed labels
    auto edge_exists = [](std::string label1, std::string label2) {
        return [&](Edge e) {
            return (((e.end1->label == label1) || (e.end1->label == label2)) && ((e.end2->label == label1) || (e.end2->label == label2)));
        };
    };

    // Remove the edge from the list matching the boolean in the function builder above
    std::remove_if(edges.begin(), edges.end(), edge_exists(label1, label2));
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
    std::queue<Vertex> q;
}
