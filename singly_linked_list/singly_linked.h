// singly_linked.h
/*
 * Generic singly linked list
 *
 * Fully featured generic singly linked list with iterator
 */

#ifndef SINGLYLINKED_H
#define SINGLYLINKED_H


template<class T>
class SinglyLinkedIter;
template<class T>
class SinglyLinkedConstIter;


template<class T>
class SinglyLinked {
public:
      // constructor
    SinglyLinked();
      // copy constructor
    SinglyLinked(const SinglyLinked<T> &sl);
      // destructor
    ~SinglyLinked();

      // iterator
    friend class SinglyLinkedIter<T>;
    typedef SinglyLinkedIter<T> iterator;

    friend class SinglyLinkedConstIter<T>;
    typedef SinglyLinkedConstIter<T> const_iterator;

    iterator       begin();
    const_iterator begin() const;
    iterator       end();
    const_iterator end()   const;

      // accessor
    bool     empty() const;
    size_t   size () const;
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
    friend std::ostream& operator<< (std::ostream &output,
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
class SinglyLinkedIter {
public:
      // constructor
    SinglyLinkedIter(const SinglyLinked<T> &sl, size_t pos);
    SinglyLinkedIter(const SinglyLinked<T> &sl, bool front);

      // operator
    SinglyLinkedIter<T>& operator++ ();
    SinglyLinkedIter<T>& operator++ (int);
    bool                 operator== (const SinglyLinkedIter<T> &it) const;
    bool                 operator!= (const SinglyLinkedIter<T> &it) const;
    T&                   operator*  ();
private:
    typename SinglyLinked<T>::Node *m_ptr;
};

template<class T>
class SinglyLinkedConstIter {
public:
    // constructor
    SinglyLinkedConstIter(const SinglyLinked<T> &sl, size_t pos);
    SinglyLinkedConstIter(const SinglyLinked<T> &sl, bool front);

    // operator
    SinglyLinkedConstIter<T>& operator++ ();
    SinglyLinkedConstIter<T>& operator++ (int);
    bool                 operator== (const SinglyLinkedConstIter<T> &it) const;
    bool                 operator!= (const SinglyLinkedConstIter<T> &it) const;
    T&                   operator*  ();
private:
    typename SinglyLinked<T>::Node *m_ptr;
};


/***********************
 ***   Constructor   ***
 ***    Destructor   ***
 ***********************/

template<class T>
SinglyLinked<T>::SinglyLinked() : m_size(0),
                                  m_front(nullptr) {
}

template<class T>
SinglyLinked<T>::SinglyLinked(const SinglyLinked<T> &sl) {
    m_size = sl.size();
    m_front = nullptr;
    Node **end_ref = &m_front;

    const_iterator it_end = sl.end();
    for (const_iterator it = sl.begin(); it != it_end; ++it) {
        *end_ref = new Node(*it);
        end_ref = &((*end_ref)->next);
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

/********************
 ***   Iterator   ***
 ********************/

template<class T>
SinglyLinkedIter<T> SinglyLinked<T>::begin() {
    return SinglyLinkedIter<T>(*this, true);
}

template<class T>
SinglyLinkedConstIter<T> SinglyLinked<T>::begin() const {
    return SinglyLinkedConstIter<T>(*this, true);
}

template<class T>
SinglyLinkedIter<T> SinglyLinked<T>::end() {
    return SinglyLinkedIter<T>(*this, false);
}

template<class T>
SinglyLinkedConstIter<T> SinglyLinked<T>::end() const {
    return SinglyLinkedConstIter<T>(*this, false);
}

/********************
 ***   Accessor   ***
 ********************/

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

/*******************
 ***   Mutator   ***
 *******************/

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


/****************************
 ***   SinglyLinkedIter   ***
 ****************************/

template<class T>
SinglyLinkedIter<T>::SinglyLinkedIter(const SinglyLinked<T> &sl, size_t pos) {
    m_ptr = sl.m_front;
    for (size_t i = 0; i < pos; ++i) {
        m_ptr = m_ptr->next;
    }
}

template<class T>
SinglyLinkedIter<T>::SinglyLinkedIter(const SinglyLinked<T> &sl, bool front) {
    if (front) {
        m_ptr = sl.m_front;
    } else { // end
        m_ptr = nullptr;
    }
}

template<class T>
SinglyLinkedIter<T>& SinglyLinkedIter<T>::operator++ () {
    this->m_ptr = this->m_ptr->next;
    return *this;
}

template<class T>
SinglyLinkedIter<T>& SinglyLinkedIter<T>::operator++ (int) {
    SinglyLinkedIter<T> *rtn = this->m_ptr;
    this->m_ptr = this->m_ptr->next;
    return *rtn;
}

template<class T>
bool SinglyLinkedIter<T>::operator== (const SinglyLinkedIter<T> &it) const {
    return this->m_ptr == it.m_ptr;
}

template<class T>
bool SinglyLinkedIter<T>::operator!= (const SinglyLinkedIter<T> &it) const {
    return this->m_ptr != it.m_ptr;
}

template<class T>
T&   SinglyLinkedIter<T>::operator* () {
    return this->m_ptr->value;
}

/*********************************
 ***   SinglyLinkedConstIter   ***
 *********************************/

template<class T>
SinglyLinkedConstIter<T>::SinglyLinkedConstIter(const SinglyLinked<T> &sl, size_t pos) {
    m_ptr = sl.m_front;
    for (size_t i = 0; i < pos; ++i) {
        m_ptr = m_ptr->next;
    }
}

template<class T>
SinglyLinkedConstIter<T>::SinglyLinkedConstIter(const SinglyLinked<T> &sl, bool front) {
    if (front) {
        m_ptr = sl.m_front;
    } else { // end
        m_ptr = nullptr;
    }
}

template<class T>
SinglyLinkedConstIter<T>& SinglyLinkedConstIter<T>::operator++ () {
    this->m_ptr = this->m_ptr->next;
    return *this;
}

template<class T>
SinglyLinkedConstIter<T>& SinglyLinkedConstIter<T>::operator++ (int) {
    SinglyLinkedConstIter<T> *rtn = this->m_ptr;
    this->m_ptr = this->m_ptr->next;
    return *rtn;
}

template<class T>
bool SinglyLinkedConstIter<T>::operator== (const SinglyLinkedConstIter<T> &it) const {
    return this->m_ptr == it.m_ptr;
}

template<class T>
bool SinglyLinkedConstIter<T>::operator!= (const SinglyLinkedConstIter<T> &it) const {
    return this->m_ptr != it.m_ptr;
}

template<class T>
T&   SinglyLinkedConstIter<T>::operator* () {
    return this->m_ptr->value;
}


#endif // SINGLYLINKED_H
