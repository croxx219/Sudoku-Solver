#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "HTable.h"
#include "pQueue.h"
#include "Vertex.h"
#include "Edge.h"
#include "Node.h"

using namespace std;

template<class Type> 
class DirGraph
{
private:

    int size;
    int numVertices;
    int heloo;

    

    // A hash table is used for faster retrieval of the vertices of the graph
    HTable<string, Vertex<Type>*> * vertices;
    SLinkedList< Vertex<Type>*> * listv;  // List of vertices
    SLinkedList< Edge<Type>*> * edges;    // List of edges

    // Find the edge between ptr and dest (in that direction)
    Edge<Type>* findEdge(Vertex<Type> * ptr, Vertex<Type> *dest)
    {
        Node<Edge<Type>*>* itr = edges->getHead();
        while (itr != NULL)
        {
            if (itr->getNodeData()->getOrigin()->getVertexName() == ptr->getVertexName() && 
                itr->getNodeData()->getDestination()->getVertexName() == dest->getVertexName())
            {
                return itr->getNodeData();
            }
            itr = itr->getNext();
        }
        return NULL;
    }

    //Checks for adjacency following direction of the edge
    bool isAdjacent(Vertex<Type> * u, Vertex<Type> * v)
    {
        // If either one does not exists, program aborts immediately.
        if (u == v) return false;
        Node<Edge<Type>*> *tmp = edges->getHead();
        while (tmp != NULL)
        {
            if (tmp->getNodeData()->getOrigin()->getVertexName() == u->getVertexName())
            {
                if (tmp->getNodeData()->getDestination()->getVertexName() == v->getVertexName())
                    return true;
            }
            tmp = tmp->getNext();
        }
        return false;
    }

public:

    DirGraph() :size(0), numVertices(0) {
        vertices = new HTable<string, Vertex<Type>*>();
        listv = new SLinkedList<Vertex<Type>*>();
        edges = new SLinkedList < Edge<Type>*>();
        this->buildGraph();
    };

    //Reads structure from a text ﬁle called "input.txt" and builds a directed weighted graph.
    void buildGraph()
    {
        string line;
        ifstream myfile("input.txt");
        if (myfile.is_open())
        {
            // Building array of vertices
            while (getline(myfile, line))
            {
                string vname1, vname2;
                Vertex<Type> * v;
                Vertex<Type> * v2;

                int pos = (int) line.find(' ');
                string data = line.substr(0, pos); // First Vertex
                string remain = line.substr(pos + 1);
                int pos2 = (int) remain.find(' ');
                string data2 = remain.substr(0, pos2); // Second Vertex
                string remain2 = remain.substr(pos2 + 1);

                int vertex1 = stoi(data);
                int vertex2 = stoi(data2);
                int weight = stoi(remain2);
        
                vname1 = data;
                vname2 = data2;

                v = new Vertex<Type>(data, vertex1);    // Creates the name,data and key of the vertex 1. 
                v2 = new Vertex<Type>(data2, vertex2);  // Creates the name,data and key of the vertex 1.
                if (vertices->insert(vname1, v))         // Adds to the hash table and to the list if not there already
                    listv->push_back(v);
                if (vertices->insert(vname2, v2))        // Adds to the hash table and to the lis tif not there already
                    listv->push_back(v2);

                Edge<Type> * tmp = new Edge<Type>(v, v2, weight);
                v->adjList->push_back(tmp);
                edges->push_back(tmp);
                size++;
            }
            // changing pointer position to be read to the beggining of the file
            myfile.close();
        }
     
        else
        {
            cout << "Unable to open file";
        }
    }

    ~DirGraph()
    {
        delete listv;
        delete edges;
        delete vertices;
        size = 0;
    }

    //Returns true if the graph is empty, false other-wise.
    bool empty()
    {
        return size == 0;
    }

    //Returns the shortest path between vertices u and v using Dijkstra's Algorithm
    //Throw an illegal argument exception if the arguments do not correspond to existing vertices.
    void shortPath(string origin, string dest)
    {
        Vertex<Type>* initialVertex = vertices->search(origin);
        Vertex<Type>* destination = vertices->search(dest);

        pQueue<Vertex<Type>*> myQueue;
        initialVertex->key = 0;

        int distance = 0;  // Distance to goal

        // Add all vertices of the graph to a priority queue
        Node<Vertex<Type>*> * tmp = listv->getHead();
        while (tmp != NULL) {
            myQueue.penqueue(tmp->getNodeData());
            tmp = tmp->getNext();
        }

        while (!myQueue.empty()) {
            Vertex<Type> * v = myQueue.dequeue();
            v->visited = true;

            if (v == destination) break;  // Path found

            Node<Vertex<Type>*> * vertexPtr = listv->getHead();
            while (vertexPtr != NULL) {
                if (isAdjacent(v, vertexPtr->getNodeData())) {
                    Edge<Type> * path = findEdge(v, vertexPtr->getNodeData());
                    if (vertexPtr->getNodeData()->getKey() > (v->getKey() + path->getWeight())) {
                        if (!vertexPtr->getNodeData()->visited) {
                            vertexPtr->getNodeData()->key = v->getKey() + path->getWeight();
                            myQueue=myQueue.sort();
                            vertexPtr->getNodeData()->pred = v;
                        }
                    }
                }
                vertexPtr = vertexPtr->getNext();
            }
        }
       
        if (destination->pred == NULL){
            cout << "No path found!\n";
            return;
        }
       
        else {
            // Print results
            cout << "The path is: ";
            cout << destination->getVertexName() << "<--";
            distance = this->printResults(destination);
            cout << "\nThe total distance was " << distance << endl << endl;
        }
        this->reset();

    }

    // This function resets the keys, visited boolean and predecesor of every vertex
    void reset() {
        Node<Vertex<Type>*> * itr = listv->getHead();
        while (itr != NULL) {
            itr->getNodeData()->key = INF;
            itr->getNodeData()->visited = false;
            itr->getNodeData()->pred = NULL;
            itr = itr->getNext();
        }
    }

    // Print results backwards, I assumed order was not important when displaying solution.
    // Solution is given from right to left following direction of "<--"
    int printResults(Vertex<Type> * vertex) {
        int pathLength = 0;
        while (vertex->pred != NULL) {
            cout << vertex->pred->getVertexName() << "<--";
            pathLength += findEdge(vertex->pred, vertex)->getWeight();
            vertex = vertex->pred;
        }  
        cout << "start" << endl;
        return pathLength;
    }

};