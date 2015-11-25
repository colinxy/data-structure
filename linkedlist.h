/*
  generic doubly linked list
 */

#include <iostream>
#include <initializer_list>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template<class T>
class LinkedList {
public:
    LinkedList();
    LinkedList(T arr[], size_t size);
    LinkedList(std::initializer_list<T> elems);
    bool empty();
    size_t size();
    T& get(size_t index);
    T& get_front();
    T& get_back();
    bool insert(T elem, size_t index);
    bool push_back(T elem);
    bool push_front(T elem);
    T pop(size_t index);
    T pop_back();
    T pop_front();

    ~LinkedList();

private:
    struct Node {
        T value;
        Node *next;
        Node *prev;
    };

    size_t _size;
    Node *_start;
    Node *_end;
};

#endif // LINKEDLIST_H
