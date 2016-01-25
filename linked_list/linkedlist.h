// linkedlist.h

/*
 * Generic doubly linked list
 *
 * This implementation of linked list tries to implement
 * the interface specified in the standard template library.
 */


#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template<class T>
class LinkedList {
public:
      // constructor
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    // LinkedList(const initializer_list<T>& elems);

    LinkedList<T> &operator= (const LinkedList<T> &);

    ~LinkedList();

      // iterator
    friend class LinkedIter<T>;
    typedef LinkedIter<T> iterator;

    friend class LinkedConstIter<T>;
    typedef LinkedConstIter<T> const_iterator;

    friend class LinkedReverseIter<T>;
    typedef LinkedReverseIter<T> reverse_iterator;

    friend class LinkedReverseConstIter<T>;
    typedef LinkedReverseConstIter<T> reverse_const_iterator;

    iterator       begin();
    const_iterator begin() const;
    iterator       end();
    const_iterator end()   const;

    reverse_iterator       rbegin();
    reverse_const_iterator rbegin() const;
    reverse_iterator       rend();
    reverse_const_iterator rend()   const;

      // accessor
    bool     empty() const;
    size_t   size () const;
    const T& operator[] (size_t index) const;
    T&       operator[] (size_t index);
    const T& front() const;
    T&       front();
    const T& back () const;
    T&       back ();

      // mutator
    bool     insert(const T& elem, size_t index);
    bool     push_back(const T& elem);
    bool     push_front(const T& elem);
    T        pop(size_t index);
    T        pop_back();
    T        pop_front();

private:
    struct Node {
        T value;
        Node *next;
        Node *prev;

        Node(T val) : value(val)
                    , next(nullptr)
                    , prev(nullptr) {}
    };

    size_t m_size;
    Node *m_start;
    Node *m_end;
};


template<class T>
class LinkedIter {
public:
      // constructor
    LinkedIter(const LinkedList<T> &ll);

    LinkedIter<T>& operator++ ();
    LinkedIter<T>& operator++ (int);
    bool           operator== (const LinkedIter<T> &it) const;
    bool           operator!= (const LinkedIter<T> &it) const;
    T&             operator*  ();

private:
    typename LinkedList<T>::Node *m_ptr;
};


template<class T>
class LinkedConstIter {
public:
      // constructor
    LinkedConstIter(const LinkedList<T> &ll);

    LinkedConstIter<T>& operator++ ();
    LinkedConstIter<T>& operator++ (int);
    bool                operator== (const LinkedConstIter<T> &it) const;
    bool                operator!= (const LinkedConstIter<T> &it) const;
    T&                  operator*  ();

private:
    typename LinkedList<T>::Node *m_ptr;
};


template<class T>
class LinkedReverseIter {
public:
      // constructor
    LinkedReverseIter(const LinkedList<T> &ll);

    LinkedReverseIter<T>& operator++ ();
    LinkedReverseIter<T>& operator++ (int);
    bool                  operator== (const LinkedReverseIter<T> &it) const;
    bool                  operator!= (const LinkedReverseIter<T> &it) const;
    T&                    operator*  ();

private:
    typename LinkedList<T>::Node *m_ptr;
};


template<class T>
class LinkedReverseConstIter {
      // constructor
    LinkedReverseConstIter(const LinkedList<T> &ll);

    LinkedReverseConstIter<T>& operator++ ();
};

template<class T>
LinkedList<T>::LinkedList() : m_size = 0
                            , m_start = nullptr
                            , m_end = nullptr {
}

/*
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    int totalSize = list.size();

    // // start node
    // Node *start = new Node;
    // start->value = list.get_front();
    // m_start = start;
    // // end node
    // Node *end = new Node;
    // end->value = list.get_back();
    // m_end = end;

    for (size_t i = 0; i < totalSize; ++i) {
        push_back(list.get(i));
    }
}


template<class T>
LinkedList<T>::LinkedList(const initializer_list<T>& elems) {
    m_size = 0;
    m_start = nullptr;
    m_end = nullptr;

    for (auto &elem : elems) {
        push_back(elem);
    }
}
*/

template<class T>
size_t LinkedList<T>::size() const {
    return m_size;
}

template<class T>
bool LinkedList<T>::empty() const {
    return m_start == nullptr;
}

template<class T>
const T& LinkedList<T>::operator[] (size_t index) const {
    if (index >= m_size) {
        throw out_of_range("array index out of range");
    }

    // TODO: optimize by choosing which end to go from
    Node *current = m_start;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}

template<class T>
T& LinkedList<T>::operator[] (size_t index) {
    if (index >= m_size) {
        throw out_of_range("array index out of range");
    }

    // TODO: optimize by choosing which end to go from
    Node *current = m_start;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}

template<class T>
const T& LinkedList<T>::front() const {
    if (m_start == nullptr) {
        throw out_of_range("array index out of range");
    }

    return m_start->value;
}

template<class T>
T& LinkedList<T>::front() {
    if (m_start == nullptr) {
        throw out_of_range("array index out of range");
    }

    return m_start->value;
}

template<class T>
const T& LinkedList<T>::back() const {
    if (m_end == nullptr) {
        throw out_of_range("array index out of range");
    }

    return m_end->value;
}

template<class T>
T& LinkedList<T>::back() {
    if (m_end == nullptr) {
        throw out_of_range("array index out of range");
    }

    return m_end->value;
}

template<class T>
bool LinkedList<T>::insert(const T& elem, size_t index) {
    // check for oversize
    if (index >= m_size) {
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
    Node *current = m_start;
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
    ++m_size;

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
        m_start = node;
        m_end = node;
        m_size = 1;
        return true;
    }

    // update the previous node, the node that m_end points to
    m_end->next = node;
    node->next = nullptr;
    node->prev = m_end;

    // update the end pointer
    m_end = node;

    // increase size
    ++m_size;

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
        m_start = node;
        m_end = node;
        m_size = 1;
        return true;
    }

    // update the next node, the node m_start points to
    m_start->prev = node;
    node->prev = nullptr;
    node->next = m_start;

    // update the start pointer
    m_start = node;

    // increase size
    ++m_size;

    return true;
}

template<class T>
T LinkedList<T>::pop(size_t index) {
    // check for oversize
    if (index >= m_size) {
        throw out_of_range("array index out of range");
    }

    // when popping from front or back
    // use pop_front or pop_back to evade nullptr problem
    if (index == 0) {
        return pop_front();
    }
    if (index == m_size-1) {
        return pop_back();
    }

    // TODO: optimize by choosing which end to go from
    // navigate to the index-1
    Node *current = m_start;
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
    --m_size;

    return elem;
}

template<class T>
T LinkedList<T>::pop_back() {
    if (empty()) {
        throw out_of_range("array index out of range");
    }

    T elem;

    // deal with list that has only 1 elem
    if (m_size == 1) {
        elem = m_start->value;
        delete m_start;
        m_start = nullptr;
        m_end == nullptr;
        m_size = 0;

        return elem;
    }

    // change end pointer
    Node *toDel = m_end;
    toDel->prev->next = nullptr;
    m_end = toDel->prev;

    // delete the item
    elem = toDel->value;
    delete toDel;

    // decrease size
    --m_size;

    return elem;
}

template<class T>
T LinkedList<T>::pop_front() {
    if (empty()) {
        throw out_of_range("array index out of range");
    }

    T elem;

    // deal with list that has only 1 elem
    if (m_size == 1) {
        elem = m_start->value;
        delete m_start;
        m_start = nullptr;
        m_end = nullptr;
        m_size = 0;

        return elem;
    }

    // change start pointer
    Node *toDel = m_start;
    toDel->next->prev = nullptr;
    m_start = toDel->next;

    // delete the item
    elem = toDel->value;
    delete toDel;

    // decrease size
    --m_size;

    return elem;
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node *current = m_start;
    for (size_t i = 0; i < m_size; ++i) {
        Node *temp = current->next;
        delete current;
        current = temp;
    }
}


#endif // LINKEDLIST_H
