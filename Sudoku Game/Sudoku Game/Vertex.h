#pragma once
#include "SLinkedList.h"
#define INF 1000       // Initial distance assigned to all vertices

using namespace std;

template<class T> class Edge;    // To avoid circular dependency with Edge.h
template <class Type> 
class Vertex {
private:
    int key;
    Type data;
    string name;
    bool visited;
    Vertex<Type> * pred;
    SLinkedList< Edge<Type>* > * adjList;      // Adjacency list representation for the graph
    template<class M> friend class DirGraph;
public:
    Vertex(string & name_, Type & data_) : key(INF), visited(false) {
        this->name = name_;
        this->data = data_;
        this->adjList = new SLinkedList< Edge<Type>* >();
    }
   
    Vertex() : key(INF), visited(false),name(0),data(0),adjList(0) {
    }

    string getVertexName() { return name; }
    Type getData() { return data; }
    int getKey() { return key; }
};
