/*
  Generic doubly linked list

  This implementation of linked list tries to implement
  the interface specified in the standard template library.
 */

#include <iostream>
#include <initializer_list>
#include <stdexcept>
using namespace std;

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template<class T>
class LinkedList {
public:
    // TODO: implement iterator
    // class iter {
    //     
    // }

    LinkedList();
    LinkedList(const LinkedList<T>& list);
    LinkedList(const initializer_list<T>& elems);
    bool empty() const;
    size_t size() const;
    const T& get(size_t index) const;
    T&       get(size_t index);
    const T& get_front() const;
    T&       get_front();
    const T& get_back() const;
    T&       get_back();
    bool insert(const T& elem, size_t index);
    bool push_back(const T& elem);
    bool push_front(const T& elem);
    T pop(size_t index);
    T pop_back();
    T pop_front();

    ~LinkedList();

private:
    struct Node {
        T value;
        Node *next = nullptr;
        Node *prev = nullptr;
    };

    size_t _size;
    Node *_start = nullptr;
    Node *_end = nullptr;
};


template<class T>
LinkedList<T>::LinkedList() {
    _size = 0;
    _start = nullptr;
    _end = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    int totalSize = list.size();

    // // start node
    // Node *start = new Node;
    // start->value = list.get_front();
    // _start = start;
    // // end node
    // Node *end = new Node;
    // end->value = list.get_back();
    // _end = end;

    for (size_t i = 0; i < totalSize; ++i) {
        push_back(list.get(i));
    }
}

template<class T>
LinkedList<T>::LinkedList(const initializer_list<T>& elems) {
    _size = 0;
    _start = nullptr;
    _end = nullptr;

    for (auto &elem : elems) {
        push_back(elem);
    }
}

template<class T>
size_t LinkedList<T>::size() const {
    return _size;
}

template<class T>
bool LinkedList<T>::empty() const {
    return _start == nullptr;
}

template<class T>
const T& LinkedList<T>::get(size_t index) const {
    if (index >= _size) {
        throw out_of_range("array index out of range");
    }

    // TODO: optimize by choosing which end to go from
    Node *current = _start;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}

template<class T>
T& LinkedList<T>::get(size_t index) {
    if (index >= _size) {
        throw out_of_range("array index out of range");
    }

    // TODO: optimize by choosing which end to go from
    Node *current = _start;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}

template<class T>
const T& LinkedList<T>::get_front() const {
    if (_start == nullptr) {
        throw out_of_range("array index out of range");
    }
    
    return _start->value;
}

template<class T>
T& LinkedList<T>::get_front() {
    if (_start == nullptr) {
        throw out_of_range("array index out of range");
    }
    
    return _start->value;
}

template<class T>
const T& LinkedList<T>::get_back() const {
    if (_end == nullptr) {
        throw out_of_range("array index out of range");
    }
    
    return _end->value;
}

template<class T>
T& LinkedList<T>::get_back() {
    if (_end == nullptr) {
        throw out_of_range("array index out of range");
    }
    
    return _end->value;
}

template<class T>
bool LinkedList<T>::insert(const T& elem, size_t index) {
    // check for oversize
    if (index >= _size) {
        return false;
    }
    
    // construct the Node
    Node *node = new Node;
    if (node == nullptr) {
        return false;
    }
    node->value = elem;

    // TODO: optimize by choosing which end to go from
    // navigate to the index-1
    Node *current = _start;
    for (size_t i = 0; i < index-1; ++i) {
        current = current->next;
    }

    // update the node before and the node after
    Node *before = current;
    Node *after = current->next;
    node->next = after;
    node->prev = before;
    before->next = node;
    after->prev = node;

    // increase size
    ++_size;

    return true;
}

template<class T>
bool LinkedList<T>::push_back(const T& elem) {
    // construct the Node
    Node *node = new Node;
    if (node == nullptr) {
        return false;
    }
    node->value = elem;

    // in case the linked list is empty
    if (empty()) {
        _start = node;
        _end = node;
        _size = 1;
        return true;
    }

    // update the previous node, the node that _end points to
    _end->next = node;
    node->next = nullptr;
    node->prev = _end;

    // update the end pointer
    _end = node;

    // increase size
    ++_size;

    return true;
}

template<class T>
bool LinkedList<T>::push_front(const T& elem) {
    // construct the Node
    Node *node = new Node;
    if (node == nullptr) {
        return false;
    }
    node->value = elem;

    // in case the linked list is empty
    if (empty()) {
        _start = node;
        _end = node;
        _size = 1;
        return true;
    }

    // update the next node, the node _start points to
    _start->prev = node;
    node->prev = nullptr;
    node->next = _start;

    // update the start pointer
    _start = node;

    // increase size
    ++_size;

    return true;
}

template<class T>
T LinkedList<T>::pop(size_t index) {
    // check for oversize
    if (index >= _size) {
        throw out_of_range("array index out of range");
    }

    // when popping from front or back
    // use pop_front or pop_back to evade nullptr problem
    if (index == 0) {
        return pop_front();
    }
    if (index == _size-1) {
        return pop_back();
    }

    // TODO: optimize by choosing which end to go from
    // navigate to the index-1
    Node *current = _start;
    for (size_t i = 0; i < index-1; ++i) {
        current = current->next;
    }

    // change the previous and next of item to be deleted
    Node *toDel = current->next;
    current->next = toDel->next;
    toDel->prev = current;

    // delete the item
    T elem = toDel->value;
    delete toDel;

    // decrease size
    --_size;

    return elem;
}

template<class T>
T LinkedList<T>::pop_back() {
    if (empty()) {
        throw out_of_range("array index out of range");
    }
    
    T elem;

    // deal with list that has only 1 elem
    if (_size == 1) {
        elem = _start->value;
        delete _start;
        _start = nullptr;
        _end == nullptr;
        _size = 0;
        
        return elem;
    }

    // change end pointer
    Node *toDel = _end;
    toDel->prev->next = nullptr;
    _end = toDel->prev;

    // delete the item
    elem = toDel->value;
    delete toDel;

    // decrease size
    --_size;

    return elem;
}

template<class T>
T LinkedList<T>::pop_front() {
    if (empty()) {
        throw out_of_range("array index out of range");
    }

    T elem;

    // deal with list that has only 1 elem
    if (_size == 1) {
        elem = _start->value;
        delete _start;
        _start = nullptr;
        _end = nullptr;
        _size = 0;
        
        return elem;
    }

    // change start pointer
    Node *toDel = _start;
    toDel->next->prev = nullptr;
    _start = toDel->next;

    // delete the item
    elem = toDel->value;
    delete toDel;

    // decrease size
    --_size;

    return elem;
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node *current = _start;
    for (size_t i = 0; i < _size; ++i) {
        Node *temp = current->next;
        delete current;
        current = temp;
    }
}


#endif // LINKEDLIST_H
