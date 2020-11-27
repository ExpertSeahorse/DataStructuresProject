#include <algorithm>
#include <queue>
#include <map>
#include <limits>

#include "Graph.hpp"


void Graph::addVertex(std::string label){
    //If there is a vertex with label already, throw. Else add a new vertex
    auto i = findVertex(label, vertices);

    if (i != vertices.end())
        throw 1;

    vertices.emplace_back(label);
}

void Graph::removeVertex(std::string label){
    // remove vertex with label from list
    std::size_t s = vertices.size();
    vertices.erase(findVertex(label, vertices));
  
    // If nothing was removed
    if (s == vertices.size())
        throw 1;

    // remove all edges connected to vertex from list
    edges.erase(findEdge(label, label, edges));
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    // no circular edges
    if (label1 == label2)
        throw 1;

    // Get labels' vertices from list
    auto i = findVertex(label1, vertices);
    auto j = findVertex(label2, vertices);

    // if either vertex does not exist, fail
    if ((i == vertices.end()) || (j == vertices.end()))
        throw 1;

    Vertex vtx1 = *i;
    Vertex vtx2 = *j;

    // Make sure that there is not an existing edge
    if (findEdge(label1, label2, edges) != edges.end())
        throw 1;

    // Create an edge and add both vertices to each others' adjacency lists
    edges.emplace_back(&vtx1, &vtx2, weight);
    vtx1.adjacent.emplace_back(vtx2);
    vtx2.adjacent.emplace_back(vtx1);
}

void Graph::removeEdge(std::string label1, std::string label2){
    // find edge with both labels as endpoints
    auto e = findEdge(label1, label2, edges);

    if (e != edges.end())
        edges.erase(e);
    else
        throw 1;
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
    // Add all vertices to undiscovered list
    std::list<std::string> vtxs;
    for (auto v : vertices)
        vtxs.push_back(v.label);

    std::map<std::string, unsigned long> dist;
    for (auto v : vertices)
        dist[v.label] = std::numeric_limits<unsigned long>::max();
    dist[startLabel] = 0;

    while(vtxs.size() != 0){
        auto i = minDistance(dist, vtxs);
        vtx.erase(i);
    }

}


//####################   Private   ####################

std::list<Vertex>::iterator Graph::findVertex(std::string label, std::list<Vertex> vertices){
    // Returns iterator to the position of the vertex with label, or vertices.end() if no match
    auto vertex_exists = [](std::string label){
        return [&](Vertex v) { return (label == v.label); };
    };

    return std::find_if(vertices.begin(), vertices.end(), vertex_exists);
}

std::list<Edge>::iterator Graph::findEdge(std::string label1, std::string label2, std::list<Edge> edges){
    // Returns iterator to the position of the edge with labels 1 & 2, or edges.end() if no match
    auto edge_exists = [](std::string label1, std::string label2) {
        return [&](Edge e) {
            return (((e.end1->label == label1) || (e.end1->label == label2)) && ((e.end2->label == label1) || (e.end2->label == label2)));
        };
    };

    return std::find_if(edges.begin(), edges.end(), edge_exists(label1, label2));
}

std::list<Vertex>::iterator minDistance(const std::map<std::string, unsigned long>& dist, const std::list<std::string>& vtxs){
    // Find the vertex with the minimum distance in the vtxs list

    // Establish needed variable names
    unsigned long best = std::numeric_limits<unsigned long>::max();
    std::string label;
    unsigned long distance;
    std::list<Vertex>::iterator index;
    bool in_vtxs;

    // if the vertex has the shortest distance and is in the vtxs list, return it
    for (auto const& vtx : dist){
        label = vtx.first; distance = vtx.second;
        in_vtxs = (std::find(vtxs.begin(), vtxs.end(), label) != vtxs.end());
        if ((distance < best) && (in_vtxs){
            best = distance;
            index = i;
        }
    }
    return index;
}