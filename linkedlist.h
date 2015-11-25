/*
  generic singly linked list with access to last item
 */

#include <iostream>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template<class T>
class LinkedList {
public:
    LinkedList();
    LinkedList(T arr[], size_t size);
    LinkedList(initilizer_list<T>);
    bool empty();
    T get(size_t index);
    T getFront();
    T getEnd();
    bool insert(T elem, size_t index);
    bool push_back(T elem);
    T del(size_t index);
    T pop_back();

    ~LinkedList();

private:
    struct Node {
        T value;
        Node *next;
    }
    
    size_t _size;
    Node *_start;
    Node *_end;
};

#endif // LINKEDLIST_H
