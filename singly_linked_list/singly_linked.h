// singly_linked.h


/*
 * Generic singly linked list
 *
 * Fully featured generic singly linked list with iterator
 */


#ifndef SINGLYLINKED_H
#define SINGLYLINKED_H


template <typename T>
class SinglyLinkedIter;
template <typename T>
class SinglyLinkedConstIter;


template <typename T>
class SinglyLinked {
public:
      // constructor
    SinglyLinked();
      // copy constructor
    SinglyLinked(const SinglyLinked<T> &sl);
      // assignment operator
    SinglyLinked<T> &operator= (const SinglyLinked<T> &);
      // destructor
    ~SinglyLinked();

      // iterator
    // friend class SinglyLinkedIter<T>;
    // typedef SinglyLinkedIter<T> iterator;

    // friend class SinglyLinkedConstIter<T>;
    // typedef SinglyLinkedConstIter<T> const_iterator;

    // iterator       begin();
    // const_iterator begin() const;
    // iterator       end();
    // const_iterator end()   const;

      // accessor
    bool     empty() const;
    size_t   size () const;
    const T& front() const;
    T&       front();
    const T& operator[] (size_t index) const;
    T&       operator[] (size_t index);

      // mutator
    void     push_front(const T& elem);
    void     insert(size_t index, const T& elem);
    // bool     insert_after(iterator it, const T& elem);
    T        pop_front();
    T        pop(size_t index);
    // T        pop_after(iterator it, const T& elem);

      // swap two linked list
    template <typename J>
    friend void swap(SinglyLinked<J> &, SinglyLinked<J> &);

      // override output stream
    template <typename J>
    friend std::ostream& operator<< (std::ostream &output,
                                     const SinglyLinked<J> &singly_linked);

private:
    struct Node {
        T     value;
        Node *next;

        Node(const T& val, Node* nxt=nullptr)
            : value(val), next(nxt) {}
    };

    size_t m_size;
    Node  *m_front;
};


template <typename T>
inline void swap(SinglyLinked<T> &a, SinglyLinked<T> &b) {
    size_t size = a.m_size;
    a.m_size = b.m_size;
    b.m_size = size;

    typename SinglyLinked<T>::Node *front = a.m_front;
    a.m_front = b.m_front;
    b.m_front = front;
}


// template <typename T>
// class SinglyLinkedIter {
// public:
//       // constructor
//     SinglyLinkedIter(const SinglyLinked<T> &sl, size_t pos);
//     SinglyLinkedIter(const SinglyLinked<T> &sl, bool front);

//       // operator
//     SinglyLinkedIter<T>& operator++ ();
//     SinglyLinkedIter<T>& operator++ (int);
//     bool                 operator== (const SinglyLinkedIter<T> &it) const;
//     bool                 operator!= (const SinglyLinkedIter<T> &it) const;
//     T&                   operator*  ();
// private:
//     typename SinglyLinked<T>::Node *m_ptr;
// };

// template<typename T>
// class SinglyLinkedConstIter {
// public:
//     // constructor
//     SinglyLinkedConstIter(const SinglyLinked<T> &sl, size_t pos);
//     SinglyLinkedConstIter(const SinglyLinked<T> &sl, bool front);

//     // operator
//     SinglyLinkedConstIter<T>& operator++ ();
//     SinglyLinkedConstIter<T>& operator++ (int);
//     bool                 operator== (const SinglyLinkedConstIter<T> &it) const;
//     bool                 operator!= (const SinglyLinkedConstIter<T> &it) const;
//     T&                   operator*  ();
// private:
//     typename SinglyLinked<T>::Node *m_ptr;
// };


// TODO: rewrite with constant iterator
template <typename T>
inline std::ostream& operator<< (std::ostream &output,
                          const SinglyLinked<T> &singly_linked) {
    output << "[";

    typename SinglyLinked<T>::Node *current = singly_linked.m_front;
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


/***********************
 ***   Constructor   ***
 ***    Destructor   ***
 ***********************/


template <typename T>
SinglyLinked<T>::SinglyLinked()
    : m_size(0)
    , m_front(nullptr) {
}


template <typename T>
SinglyLinked<T>::SinglyLinked(const SinglyLinked<T> &rhs)
    : m_size(rhs.size())
    , m_front(nullptr) {

    Node **end_ref = &m_front;
    const Node *elem_rhs = rhs.m_front;

    for (size_t i = 0; i < size(); ++i) {
        *end_ref = new Node(elem_rhs->value);

        elem_rhs = elem_rhs->next;
        end_ref = &((*end_ref)->next);
    }

    // const_iterator it_end = rhs.end();
    // for (const_iterator it = rhs.begin(); it != it_end; ++it) {
    //     *end_ref = new Node(*it);
    //     end_ref = &((*end_ref)->next);
    // }
}


template <typename T>
SinglyLinked<T> & SinglyLinked<T>::operator= (const SinglyLinked<T> &rhs) {
    if (this != &rhs) {
        SinglyLinked<T> temp(rhs);
        swap(*this, temp);
    }

    return *this;
}


template <typename T>
SinglyLinked<T>::~SinglyLinked() {
    Node *current = m_front;
    while (current != nullptr) {
        Node *toDel = current;
        current = current->next;
        delete toDel;
    }
}


/********************
 ***   Iterator   ***
 ********************/

// template <typename T>
// SinglyLinkedIter<T> SinglyLinked<T>::begin() {
//     return SinglyLinkedIter<T>(*this, true);
// }


// template <typename T>
// SinglyLinkedConstIter<T> SinglyLinked<T>::begin() const {
//     return SinglyLinkedConstIter<T>(*this, true);
// }


// template <typename T>
// SinglyLinkedIter<T> SinglyLinked<T>::end() {
//     return SinglyLinkedIter<T>(*this, false);
// }


// template <typename T>
// SinglyLinkedConstIter<T> SinglyLinked<T>::end() const {
//     return SinglyLinkedConstIter<T>(*this, false);
// }


/********************
 ***   Accessor   ***
 ********************/

template <typename T>
inline bool SinglyLinked<T>::empty() const {
    return m_front == nullptr;
}


template <typename T>
inline size_t SinglyLinked<T>::size() const {
    return m_size;
}


// check is empty before accessing the first element
template <typename T>
inline const T& SinglyLinked<T>::front() const {
    return m_front->value;
}


// check is empty before accessing the first element
template <typename T>
inline T& SinglyLinked<T>::front() {
    return m_front->value;
}

// no throw
template <typename T>
const T& SinglyLinked<T>::operator[] (size_t index) const {
    Node *current = m_front;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->value;
}


// no throw
template <typename T>
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

template <typename T>
inline void SinglyLinked<T>::push_front(const T& elem) {
    Node *node = new Node(elem);
    // if fail to construct new node
    // C++ will throw bad_alloc

    node->next = m_front;
    m_front = node;

    ++m_size;
}


template <typename T>
void SinglyLinked<T>::insert(size_t index, const T& elem) {
    Node *node = new Node(elem);
    // if fail to construct new node
    // C++ will throw bad_alloc

    // navigate to element at index
    Node **current = &m_front;
    for (size_t i = 0; i < index; ++i) {
        current = &((*current)->next);
    }

    Node *old_current = *current;
    *current = node;
    node->next = old_current;

    ++m_size;
}


template <typename T>
inline T SinglyLinked<T>::pop_front() {
    T elem(m_front->value);

    Node *toPop = m_front;
    m_front = toPop->next;
    delete toPop;

    --m_size;
    return elem;
}


template <typename T>
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

// template <typename T>
// SinglyLinkedIter<T>::SinglyLinkedIter(const SinglyLinked<T> &sl, size_t pos) {
//     m_ptr = sl.m_front;
//     for (size_t i = 0; i < pos; ++i) {
//         m_ptr = m_ptr->next;
//     }
// }


// template <typename T>
// SinglyLinkedIter<T>::SinglyLinkedIter(const SinglyLinked<T> &sl, bool front) {
//     if (front) {
//         m_ptr = sl.m_front;
//     } else { // end
//         m_ptr = nullptr;
//     }
// }


// template <typename T>
// SinglyLinkedIter<T>& SinglyLinkedIter<T>::operator++ () {
//     this->m_ptr = this->m_ptr->next;
//     return *this;
// }


// template <typename T>
// SinglyLinkedIter<T>& SinglyLinkedIter<T>::operator++ (int) {
//     SinglyLinkedIter<T> *rtn = this->m_ptr;
//     this->m_ptr = this->m_ptr->next;
//     return *rtn;
// }


// template <typename T>
// bool SinglyLinkedIter<T>::operator== (const SinglyLinkedIter<T> &it) const {
//     return this->m_ptr == it.m_ptr;
// }


// template <typename T>
// bool SinglyLinkedIter<T>::operator!= (const SinglyLinkedIter<T> &it) const {
//     return this->m_ptr != it.m_ptr;
// }


// template <typename T>
// T&   SinglyLinkedIter<T>::operator* () {
//     return this->m_ptr->value;
// }


// /*********************************
//  ***   SinglyLinkedConstIter   ***
//  *********************************/

// template <typename T>
// SinglyLinkedConstIter<T>::SinglyLinkedConstIter(const SinglyLinked<T> &sl, size_t pos) {
//     m_ptr = sl.m_front;
//     for (size_t i = 0; i < pos; ++i) {
//         m_ptr = m_ptr->next;
//     }
// }


// template <typename T>
// SinglyLinkedConstIter<T>::SinglyLinkedConstIter(const SinglyLinked<T> &sl, bool front) {
//     if (front) {
//         m_ptr = sl.m_front;
//     } else { // end
//         m_ptr = nullptr;
//     }
// }

// template <typename T>
// SinglyLinkedConstIter<T>& SinglyLinkedConstIter<T>::operator++ () {
//     this->m_ptr = this->m_ptr->next;
//     return *this;
// }

// template <typename T>
// SinglyLinkedConstIter<T>& SinglyLinkedConstIter<T>::operator++ (int) {
//     SinglyLinkedConstIter<T> *rtn = this->m_ptr;
//     this->m_ptr = this->m_ptr->next;
//     return *rtn;
// }

// template <typename T>
// bool SinglyLinkedConstIter<T>::operator== (const SinglyLinkedConstIter<T> &it) const {
//     return this->m_ptr == it.m_ptr;
// }


// template <typename T>
// bool SinglyLinkedConstIter<T>::operator!= (const SinglyLinkedConstIter<T> &it) const {
//     return this->m_ptr != it.m_ptr;
// }


// template <typename T>
// T&   SinglyLinkedConstIter<T>::operator* () {
//     return this->m_ptr->value;
// }


#endif  // SINGLYLINKED_H
