#include <algorithm>
#include <queue>
#include <map>
#include <limits>
#include <set>
#include <utility>
#include <iostream>
#include <stack>

#include "Graph.hpp"


void Graph::addVertex(std::string label){
    //If there is a vertex with label already, throw. Else add a new vertex
    auto i = findVertex(label);

    if (i != vertices.end())
        throw 1;

    size_v++;
    vertices.emplace_back(label);
}

void Graph::removeVertex(std::string label){
    // remove vertex with label from list
    auto i = findVertex(label);
    if (i == vertices.end())
        throw 1;

    for(auto v : i->adjacent){
        // Remove all edges with this vertex
        removeEdge(label, v->label);

        // Remove vertex from adjacency list on adjacent vertices
        v->adjacent.erase(std::remove(v->adjacent.begin(), v->adjacent.end(), &*i), v->adjacent.end());
    }
    
    size_v--;
    vertices.erase(i);
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    // no circular edges
    if (label1 == label2)
        throw 1;

    // Get labels' vertices from list
    auto i = findVertex(label1);
    auto j = findVertex(label2);

    // if either vertex does not exist, fail
    if ((i == vertices.end()) || (j == vertices.end()))
        throw 1;

    Vertex* vtx1 = &*i;
    Vertex* vtx2 = &*j;

    // Make sure that there is not an existing edge    
    if (findEdge(label1, label2) != edges.end())
        throw 1;
    
    // Create an edge and add both vertices to each others' adjacency lists
    edges.emplace_back(vtx1, vtx2, weight);
    vtx1->adjacent.emplace_back(vtx2);
    vtx2->adjacent.emplace_back(vtx1);
    size_e++;
}

void Graph::removeEdge(std::string label1, std::string label2){
    // find edge with both labels as endpoints
    auto e = findEdge(label1, label2);

    if (e != edges.end())
        edges.erase(e);
    else
        throw 1;
    size_e--;
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
    // Add all vertices to undiscovered list
    // create distance map for max distanc WalkeWe
    std::list<std::string> vtxs;                // buffer of vertices in string form
    std::map<std::string, std::string> prev;    // The node that is before prev[n]
    std::map<std::string, unsigned long> dist;  // Distances of each node from center
    //std::set<std::string> short_set;          // currently unused
    std::priority_queue<std::pair<unsigned long, std::string> > short_pq;   // somewhat unused, all nodes are added to it (Holds all of the final distances)
    
    // Create buffer and initialize distance and prev maps
    for (auto v : vertices){
        vtxs.push_back(v.label);
        dist[v.label] = std::numeric_limits<unsigned long>::max();  // infinity
        prev[v.label] = "";
    }
    dist[startLabel] = 0;

    Vertex vtx;
    std::string label;
    unsigned long edge_weight;
    // Dijkstra
    while (vtxs.size() != 0){
        // Get min element + remove from vtx list
        auto i = minDistance(dist, vtxs);
        label = *i;
        vtxs.erase(i);
        // Add to priority queue ; no current purpose for this, but this pq will hold the max distances at the end of the algo
        short_pq.push(std::make_pair(dist[label], label));

        // Update distances + prev node of all adjacent vertices to see if they are lower
        vtx = *findVertex(label);        

        for(auto v : vtx.adjacent){ //For every vertex in vtx.adjacent (adjacent list of current vertex) 
            edge_weight = findEdge(v->label, label)->weight;    // Find edge from endpoints
            
            if (dist[v->label] > (dist[label] + edge_weight)){  // if curr_dist < distance through this node, use shorter distance + update prev node
                dist[v->label] = dist[label] + edge_weight;
                prev[v->label] = vtx.label; //Previous of new vertex becomes the current vertex
            }
        }
    }
    // All nodes have been charted by the algo, now to build the path
    std::string current=endLabel;
    std::stack<std::string> temp;
    temp.push(current);
    do{
        current = prev[current]; //Gets previous vertex of the current vertex
        temp.push(current); //Add current vertex
    }while(current != startLabel); //While our current is not the initial label (back at the starting point)

    while(!temp.empty()){
        path.push_back(temp.top());
        temp.pop();
    }

    return dist[endLabel];
    // TODO: Fix Graph Destructor
}

//####################   Private   ####################

std::list<Vertex>::iterator Graph::findVertex(std::string label){
    // Returns iterator to the position of the vertex with label, or vertices.end() if no match
    auto vertex_exists = [](std::string label){
        return [&](Vertex v) { return (label == v.label); };
    };

    return std::find_if(vertices.begin(), vertices.end(), vertex_exists(label));
}

std::list<Edge>::iterator Graph::findEdge(std::string label1, std::string label2){
    // Returns iterator to the position of the edge with labels 1 & 2, or edges.end() if no match
    auto edge_exists = [](std::string label1, std::string label2) {
        return [&](Edge e) {
            return (((e.end1->label == label1) || (e.end1->label == label2)) && ((e.end2->label == label1) || (e.end2->label == label2)));
        };
    };
    return std::find_if(edges.begin(), edges.end(), edge_exists(label1, label2));
}

//Compares the distance map and vtx list against each other, if in the vtx list it's undiscovered, every vertex is within distance list
//Looking to see which entry in distance has the lowest distance and is undiscovered (Distance is a map of labels and distances)
std::list<std::string>::const_iterator Graph::minDistance(const std::map<std::string, unsigned long>& dist, const std::list<std::string>& vtxs){
    // Find the vertex with the minimum distance in the vtxs list

    // Establish needed variable names
    unsigned long best = std::numeric_limits<unsigned long>::max(); //Infinity
    std::string label, sticky_label;
    unsigned long distance;
    bool in_vtxs;

    // if the vertex has the shortest distance and is in the vtxs list, return it
    for (auto const& vtx : dist){
        label = vtx.first; distance = vtx.second;
        in_vtxs = (std::find(vtxs.begin(), vtxs.end(), label) != vtxs.end()); //Checking to see if label is in vtxs
        if ((distance < best) && (in_vtxs)){  //If distance is less than previous minimum distance AND is in the vertex list
            best = distance;
            sticky_label = label;
        }
    }
    // Return the index of the label in the list
    return std::find(vtxs.begin(), vtxs.end(), sticky_label); 
}