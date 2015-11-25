#include <iostream>
using namespace std;

#include "linkedlist.h"


template<class T>
LinkedList<T>::LinkedList() {
    _size = 0;
    _start = nullptr;
    _end = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(T arr[], size_t size) {
    _size = 0;
    _start = nullptr;
    _end = nullptr;
    
    for (size_t i = 0; i < size; ++i) {
        push_back(arr[i]);
    }
}

template<class T>
LinkedList<T>::LinkedList(initilizer_list<T> elems) {
    _size = 0;
    _start = nullptr;
    _end = nullptr;

    for (auto &elem : elems) {
        push_back(elem);
    }
}

template<class T>
bool LinkedList<T>::empty() {
    return _start == nullptr;
}

template<class T>
T LinkedList<T>::get(size_t index) {
    Node *current = _start;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}

template<class T>
bool LinkedList<T>::insert(T elem, size_t index) {
    // check for oversize
    if (index > _size) {
        return false;
    }
    
    // construct the Node
    Node *node = new Node;
    if (node == nullptr) {
        return false;
    }
    node->value = elem;
    node->next = nullptr;

    // navigate to the index-1
    Node *current = _start;
    for (size_t i = 0; i < index-1; ++i) {
        current = current->next;
    }

    // update current node and the previous node
    node->next = current->next;
    current->next = node;

    // increase size of linked list
    ++_size;

    return true;
}

template<class T>
bool LinkedList<T>::push_back(T elem) {
    // construct the node
    Node *node = new Node;
    if (node == nullptr) {
        return false;
    }
    node->value = elem;
    node->next = nullptr;

    // update end pointer
    _end = node;

    // increase size of linked list
    ++_size;

    return true;
}
