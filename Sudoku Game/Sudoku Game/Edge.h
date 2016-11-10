#pragma once
#include "Vertex.h"

template<class Type> 
class Edge
{
private:
    bool added;
    Vertex<Type> * origin;
    Vertex<Type> * destination;
    Type weight;   
    template <class M> friend class DirGraph;
    
public:
    Edge(Vertex<Type> * origin_, Vertex<Type> * destination_, const Type & weight_)
    {
        this->origin = origin_;
        this->destination = destination_;
        this->weight = weight_;
        this->added = false;
    }

    Vertex<Type> * getOrigin() { return origin; };
    Vertex<Type> * getDestination() { return destination; };
    int getWeight() { return weight; }
};
