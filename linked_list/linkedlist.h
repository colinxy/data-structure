// linkedlist.h


/*
 * Generic doubly linked list with dummy node
 *
 * This implementation of linked list tries to implement
 * the interface specified in the standard template library.
 */


#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template <typename T>
class LinkedList {
public:
      // constructor
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    // LinkedList(const initializer_list<T>& elems);

    LinkedList<T> &operator= (const LinkedList<T> &);

    ~LinkedList();

      // iterator
    // friend class LinkedIter<T>;
    // typedef LinkedIter<T> iterator;

    // friend class LinkedConstIter<T>;
    // typedef LinkedConstIter<T> const_iterator;

    // friend class LinkedReverseIter<T>;
    // typedef LinkedReverseIter<T> reverse_iterator;

    // friend class LinkedReverseConstIter<T>;
    // typedef LinkedReverseConstIter<T> reverse_const_iterator;

    // iterator       begin();
    // const_iterator begin() const;
    // iterator       end();
    // const_iterator end()   const;

    // reverse_iterator       rbegin();
    // reverse_const_iterator rbegin() const;
    // reverse_iterator       rend();
    // reverse_const_iterator rend()   const;

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
    void     insert(const T& elem, size_t index);
    void     push_back(const T& elem);
    void     push_front(const T& elem);
    T        pop(size_t index);
    T        pop_back();
    T        pop_front();

      // swap two doubly linked list
    template <typename J>
    friend void swap(LinkedList<J> &, LinkedList<J> &);

      // override output stream
    template <typename J>
    friend std::ostream& operator<< (std::ostream &output,
                                     const LinkedList<J> &);

private:
    struct Node {
        T     value;
        Node *next;
        Node *prev;

        Node(T val, nxt=nullptr, prv=nullptr)
            : value(val)
            , next(nxt)
            , prev(prv) {}
    };

    size_t m_size;
    Node  *m_head;
};


template <typename T>
inline void swap(LinkedList<T> &lhs, LinkedList<T> &rhs) {
    size_t size = lhs.m_size;
    lhs.m_size = rhs.m_size;
    rhs.m_size = size;

    typename LinkedList<T>::Node *head = lhs.m_head;
    lhs.m_head = rhs.m_head;
    rhs.m_head = head;
}


// template<typename T>
// class LinkedIter {
// public:
//       // constructor
//     LinkedIter(const LinkedList<T> &ll);

//     LinkedIter<T>& operator++ ();
//     LinkedIter<T>& operator++ (int);
//     bool           operator== (const LinkedIter<T> &it) const;
//     bool           operator!= (const LinkedIter<T> &it) const;
//     T&             operator*  ();

// private:
//     typename LinkedList<T>::Node *m_ptr;
// };


// template<typename T>
// class LinkedConstIter {
// public:
//       // constructor
//     LinkedConstIter(const LinkedList<T> &ll);

//     LinkedConstIter<T>& operator++ ();
//     LinkedConstIter<T>& operator++ (int);
//     bool                operator== (const LinkedConstIter<T> &it) const;
//     bool                operator!= (const LinkedConstIter<T> &it) const;
//     T&                  operator*  ();

// private:
//     typename LinkedList<T>::Node *m_ptr;
// };


// template<typename T>
// class LinkedReverseIter {
// public:
//       // constructor
//     LinkedReverseIter(const LinkedList<T> &ll);

//     LinkedReverseIter<T>& operator++ ();
//     LinkedReverseIter<T>& operator++ (int);
//     bool                  operator== (const LinkedReverseIter<T> &it) const;
//     bool                  operator!= (const LinkedReverseIter<T> &it) const;
//     T&                    operator*  ();

// private:
//     typename LinkedList<T>::Node *m_ptr;
// };


// template<typename T>
// class LinkedReverseConstIter {
//       // constructor
//     LinkedReverseConstIter(const LinkedList<T> &ll);

//     LinkedReverseConstIter<T>& operator++ ();
// };


/***********************
 ***   Constructor   ***
 ***    Destructor   ***
 ***********************/


template <typename T>
LinkedList<T>::LinkedList()
    : m_size(0) {

    // TODO: make it work for non default constructable objects
    m_head = new Node(T());
    m_head->next = m_head;
    m_head->prev = m_head;
}


template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
    : m_size(rhs.size())
    , m_head(nullptr) {

    const Node *elem_rhs = rhs.m_head;

    for (size_t i = 0; i < size(); ++i) {
        push_back(elem_rhs->value);
    }
}


template <typename T>
LinkedList<T> & LinkedList<T>::operator= (const LinkedList<T> &rhs) {
    if (this != &rhs) {
        LinkedList<T> temp(rhs);
        swap(*this, rhs);
    }

    return *this;
}


template <typename T>
LinkedList<T>::~LinkedList() {
    Node *current = m_head->next;
    while (current != m_head) {
        Node *toDel = current;
        current = current->next;
        delete toDel;
    }

    delete m_head;
}


// template<typename T>
// LinkedList<T>::LinkedList(const initializer_list<T>& elems) {
//     m_size = 0;
//     m_start = nullptr;
//     m_end = nullptr;

//     for (auto &elem : elems) {
//         push_back(elem);
//     }
// }


/********************
 ***   Accessor   ***
 ********************/

template <typename T>
inline size_t LinkedList<T>::size() const {
    return m_size;
}


template <typename T>
inline bool LinkedList<T>::empty() const {
    return m_size == 0;
}


template <typename T>
inline const T& LinkedList<T>::operator[] (size_t index) const {
    // TODO: optimize by choosing which end to go from
    Node *current = m_head->next;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}


template <typename T>
inline T& LinkedList<T>::operator[] (size_t index) {
    // TODO: optimize by choosing which end to go from
    Node *current = m_head->next;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->value;
}


template <typename T>
inline const T& LinkedList<T>::front() const {
    return m_head->next->value;
}


template <typename T>
inline T& LinkedList<T>::front() {
    return m_head->next->value;
}


template <typename T>
inline const T& LinkedList<T>::back() const {
    return m_head->prev->value;
}


template <typename T>
inline T& LinkedList<T>::back() {
    return m_head->prev->value;
}


/*******************
 ***   Mutator   ***
 *******************/

template <typename T>
void LinkedList<T>::insert(const T& elem, size_t index) {
    // construct the Node
    Node *node = new Node(elem);


    // increase size
    ++m_size;

    return true;
}


template <typename T>
void LinkedList<T>::push_back(const T& elem) {
    // construct the Node
    Node *node = new Node(elem);


    // increase size
    ++m_size;

    return true;
}


template <typename T>
void LinkedList<T>::push_front(const T& elem) {
    // construct the Node
    Node *node = new Node(elem);
    node->value = elem;


    // increase size
    ++m_size;

    return true;
}


template <typename T>
T LinkedList<T>::pop(size_t index) {
    // check for oversize
    if (index >= m_size) {
        throw out_of_range("array index out of range");
    }


    // decrease size
    --m_size;

    return elem;
}

template <typename T>
T LinkedList<T>::pop_back() {
    if (empty()) {
        throw out_of_range("array index out of range");
    }


    // decrease size
    --m_size;

    return elem;
}


template <typename T>
T LinkedList<T>::pop_front() {
    if (empty()) {
        throw out_of_range("array index out of range");
    }


    // decrease size
    --m_size;

    return elem;
}


#endif  // LINKEDLIST_H
