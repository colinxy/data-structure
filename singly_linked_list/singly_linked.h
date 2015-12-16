/*
  Generic singly linked list

  Singly linked list with optimized functionality
  to append at the end in O(1) time using reference
  pointer technique
 */

#include <iostream>
using namespace std;

#ifndef SINGLYLINKED_H
#define SINGLYLINKED_H


template<class T>
class SinglyLinked {
public:
      // constructor
    SinglyLinked();
      // copy constructor
    SinglyLinked(const SinglyLinked<T> &sl);
      // destructor
    ~SinglyLinked();

    class iterator;

    iterator begin();
    iterator end();

      // accessor
    bool     empty() const;
    size_t   size() const;
    const T& front() const;
    T&       front();
    const T& operator[] (size_t index) const;
    T&       operator[] (size_t index);

      // mutator
    bool     push_front(const T& elem);
    bool     insert(size_t index, const T& elem);
    // bool     insert_after(iterator it, const T& elem);
    T        pop_front();
    T        pop(size_t index);
    // T        pop_after(iterator it, const T& elem);

      // override output stream
    friend ostream& operator<< (ostream &output,
                                const SinglyLinked<T> &singly_linked) {
        output << "[";

        SinglyLinked<T>::Node *current = singly_linked.m_front;
        while (current != nullptr) {
            if (current->next != nullptr) {
                output << current->value << ", ";
            } else {
                output << current->value;
            }
            current = current->next;
        }
        output << "]";
        return output;
    }

private:
    struct Node {
        T value;
        Node *next;

        Node(const T& val) : value(val), next(nullptr) {}
    };

    size_t m_size;
    Node *m_front;
};

template<class T>
SinglyLinked<T>::SinglyLinked() : m_size(0),
                               m_front(nullptr) {
}

template<class T>
SinglyLinked<T>::SinglyLinked(const SinglyLinked<T> &sl) {
    m_size = sl.size();
    Node **end_ref = &m_front;

    iterator it_end = end();
    for (iterator it = begin(); it != end(); it++) {
        *end_ref = new Node(*it);
        *end_ref = (*end_ref)->next;
    }
}

template<class T>
SinglyLinked<T>::~SinglyLinked() {
    Node *current = m_front;
    while (current != nullptr) {
        Node *toDel = current;
        delete toDel;
        current = current->next;
    }
}

template<class T>
bool SinglyLinked<T>::empty() const {
    return m_front == nullptr;
}

template<class T>
size_t SinglyLinked<T>::size() const {
    return m_size;
}

// check is empty before accessing the first element
template<class T>
const T& SinglyLinked<T>::front() const {
    return m_front->value;
}

// check is empty before accessing the first element
template<class T>
T& SinglyLinked<T>::front() {
    return m_front->value;
}

// no throw
template<class T>
const T& SinglyLinked<T>::operator[] (size_t index) const {
    Node *current = m_front;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}

// no throw
template<class T>
T& SinglyLinked<T>::operator[] (size_t index) {
    Node *current = m_front;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}

template<class T>
bool SinglyLinked<T>::push_front(const T& elem) {
    Node *node = new Node(elem);
    // fail to construct new node
    if (node == nullptr) return false;

    node->next = m_front;
    m_front = node;

    ++m_size;
    return true;
}

// no throw
template<class T>
bool SinglyLinked<T>::insert(size_t index, const T& elem) {
    Node *node = new Node(elem);
    // fail to construct new node
    if (node == nullptr) return false;

    // navigate to element at index
    Node **current = &m_front;
    for (size_t i = 0; i < index; ++i) {
        current = &((*current)->next);
    }

    Node *old_current = *current;
    *current = node;
    node->next = old_current;

    ++m_size;
    return true;
}

template<class T>
T SinglyLinked<T>::pop_front() {
    T elem(m_front->value);

    Node *toPop = m_front;
    m_front = toPop->next;
    delete toPop;

    --m_size;
    return elem;
}

// no throw
template<class T>
T SinglyLinked<T>::pop(size_t index) {
    Node **current = &m_front;
    for (size_t i = 0; i < index; ++i) {
        current = &((*current)->next);
    }

    Node *toPop = *current;
    T elem((*current)->value);
    *current = toPop->next;
    delete toPop;

    --m_size;
    return elem;
}

template<class T>
class SinglyLinked<T>::iterator {
public:
      // constructor
    iterator(Node *ptr) : m_ptr(ptr) {}

      // operator
    const iterator& operator++ ();
    bool     operator== (const iterator &it);
    bool     operator!= (const iterator &it);
    T        operator* ();
private:
    Node *m_ptr;
};

template<class T>
SinglyLinked<T>::iterator begin() {
    return iterator(m_front);
}

template<class T>
SinglyLinked<T>::iterator end() {
    return iterator(nullptr);
}

template<class T>
const SinglyLinked<T>::iterator& SinglyLinked<T>::iterator::operator++ (const iterator &it) {
    this->m_ptr = this->m_ptr->next;

    return *this;
}

template<class T>
bool SinglyLinked<T>::iterator::operator== (const iterator &it) const {
    return *this == it;
}

template<class T>
bool SinglyLinked<T>::iterator::operator!= (const iterator &it) const {
    return *this != it;
}

template<class T>
T& SinglyLinked<T>::iterator::operator* () const {
    return *this->value;
}

#endif // SINGLYLINKED_H
