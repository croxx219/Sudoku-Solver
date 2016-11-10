#pragma once
#include <string>
#include "Vertex.h"
#include "SLinkedList.h"

template <typename kType, class myType>
class HTable {
private:
    int totalElements;
    int entries;
    int capacity;
    SLinkedList<myType> *listArray;
  
    // This is the hash function. It takes a string, converts it to int and then
    // mod it with the total capacity of the table.
    int getIndex(const string & key) {
        int hash = stoi(key);
        int idx = hash%capacity;
        //cout <<"index->" << idx << endl;
        return idx;
    }

public:  
    HTable() :totalElements(0),entries(0) {
        this->capacity = 26;     // The capacity was chosen to be 26 since the graph is fairly small.
        listArray = new SLinkedList<myType>[capacity];
    }
    
    bool isEmpty() const {
        return totalElements == 0;
    }

    bool isEmpty(const kType & key) {
        int idx = HTable::getIndex(key);
        return listArray[idx].empty();
    }
    
    // Since the push_back function is being used for insertion, collision treatment happens automatically.
    bool insert(const kType & key, const myType & value) {
        int idx = HTable::getIndex(key);
        
        if (!this->isEmpty(key)) // Avoid adding duplicates vertices to the hash table
            return false;

        listArray[idx].push_back(value);
        totalElements++;
        entries++;
        return true;
    }

    myType search(const kType & key) {
        int i = HTable::getIndex(key);
        if (!HTable::isEmpty(key)) {
           Vertex<int> * result = listArray[i].find(key)->getNodeData();
           return result;
        }
        else 
           throw underflow_error("Vertex not found");
    }

    ~HTable() {
        delete[] listArray;
        totalElements = entries = capacity = 0;
    }
};


