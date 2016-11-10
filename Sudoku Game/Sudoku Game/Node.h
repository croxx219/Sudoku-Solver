#pragma once

// A node class for the linked list
template <class type> class Node{
private:
    type data;
    Node * next;
    template<class U> friend class SLinkedList;
    template<class P> friend class pQueue;
    template<class O> friend class mQueue;
public:
    Node(const type & data) :next(0) {
        this->data = data;

    }
    type getNodeData() { return data; }
    Node * getNext() { return next; }
};
