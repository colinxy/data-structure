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
    // TODO: implement iterator
    // class iter {
    //
    // }

      // constructor
    SinglyLinked();
      // destructor
    ~SinglyLinked();

      // accessor
    bool     empty() const;
    size_t   size() const;
    const T& front() const;
    T&       front();
    const T& operator[] (size_t index) const;
    T&       operator[] (size_t index);

      // override output stream
    friend ostream& operator<< (ostream &output, const SinglyLinked &singly_linked) {
        output << "[";

        Node *current = singly_linked.m_front;
        while (current != nullptr) {
            output << current->value << ", ";
            current = current->next;
        }
        output << "]";
        return output;
    }

      // mutator
    bool     push_front(const T& elem);
    bool     push_back(const T& elem);
    bool     insert(const T& elem, size_t index);
    T        pop_front();
    T        pop(size_t index);

private:
    struct Node {
        T value;
        Node *next;

        Node(const T& val) : value(val), next(nullptr) {}
    };

    size_t m_size;
    Node *m_front;
    Node **m_back_ref;
};

template<class T>
SinglyLinked<T>::SinglyLinked() : m_size(0),
                               m_front(nullptr),
                               m_back_ref(&m_front) {
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

template<class T>
bool SinglyLinked<T>::push_back(const T& elem) {
    Node *node = new Node(elem);
    // fail to construct new node
    if (node == nullptr) return false;

    *m_back_ref = node;
    m_back_ref = &node->next;

    ++m_size;
    return true;
}

// no throw
template<class T>
bool SinglyLinked<T>::insert(const T& elem, size_t index) {
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

    // update end reference in case the
    // node inserted is the last node
    if (old_current == nullptr) {
        m_back_ref = &(node->next);
    }

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

#endif // SINGLYLINKED_H
