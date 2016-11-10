#pragma once
#include "SLinkedList.h"
template<class type>
class mQueue:public SLinkedList<type>{
private:
    Node<type> *tail;
public:
    mQueue():tail(nullptr){}
    bool isEmpty() const{
        return SLinkedList<type>::empty();
    }

    void enqueue(const type & data){
        Node<type> *tmp = new Node<type>(data);
        if(this->isEmpty()){
            SLinkedList<type>::head = tmp;
            tail = tmp;
            SLinkedList<type>::sz++;
        }
        else{
            tail->next =tmp;
            tail = tmp;
            SLinkedList<type>::sz++;
        }
    }

    type front() const {
        if (this->isEmpty()) throw underflow_error("Empty mQueue");
        return SLinkedList<type>::head->data;
    }

    type back() {
        if (this->isEmpty()) throw underflow_error("Empty mQueue");
        return tail->getNodeData();
    }

    type dequeue(){
        type dat = this->front();
        Node<type> *ptr = SLinkedList<type>::head;
        SLinkedList<type>::head = ptr->next;
        delete ptr;
        SLinkedList<type>::sz--;
        return dat;
    }

    type find(type ptr) {
        Node<type> * itr = SLinkedList<type>::head;
        while (itr != NULL) {
            if (itr->getNodeData()->isEqual(ptr)) return itr->getNodeData();
            itr = itr->next;
        }
        return NULL;
    }
};
