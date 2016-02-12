// minheap.h


/*
 * Generic Minimum Heap
 * Object has to be default constructable
 */


#ifndef MINHEAP_H
#define MINHEAP_H

#include <cstddef>  // for std::size_t
#include <utility>  // for std::swap


template <typename T>
class MinHeap {
public:
      // constructor
    MinHeap(std::size_t capacity = 8);
      // copy constructor
    MinHeap(const MinHeap<T> &, std::size_t capacity = 8);
      // assignment operator
    MinHeap<T> &operator= (const MinHeap<T> &);
      // destructor
    ~MinHeap();

      // accessor
    std::size_t   capacity() const;
    std::size_t   size()     const;
    const T&      peek()     const;

      // mutator
    void push(const T&);
    T    pop();
    T    pop_push(const T&);

    // overload swap
    template <typename J>
    friend void swap(MinHeap<J> &, MinHeap<J> &);

private:
    void siftdown(std::size_t);

    std::size_t m_capacity;
    std::size_t m_size;
    T          *m_array;
};


template <typename T>
MinHeap<T>::MinHeap(std::size_t capacity)
    : m_capacity(capacity)
    , m_size(0) {

    m_array = new T[m_capacity];
}


template <typename T>
MinHeap<T>::MinHeap(const MinHeap<T> &mh, std::size_t capacity) {
    if (capacity < mh.size())
        capacity = mh.size();

    m_capacity = capacity;
    m_size     = 0;

    for (std::size_t i = 0; i < mh.size(); ++i)
        m_array[m_size++];
}


template <typename T>
MinHeap<T> & MinHeap<T>::operator= (const MinHeap<T> &rhs) {
    if (this != &rhs) {
        MinHeap<T> temp(rhs);
        swap(*this, temp);
    }

    return *this;
}


template <typename T>
MinHeap<T>::~MinHeap() {
    delete[] m_array;
}


template <typename T>
void swap(MinHeap<T> &lhs, MinHeap<T> &rhs) {
    std::swap(lhs.m_capacity, rhs.m_capacity);
    std::swap(lhs.m_size,     rhs.m_size);
    std::swap(lhs.m_array,    rhs.m_array);
}


template <typename T>
inline std::size_t MinHeap<T>::capacity() const {
    return m_capacity;
}


template <typename T>
inline std::size_t MinHeap<T>::size() const {
    return m_size;
}


template <typename T>
inline const T& MinHeap<T>::peek() const {
    return m_array[0];
}


template <typename T>
void MinHeap<T>::push(const T& elem) {
    // TODO: resize the heap

    m_array[m_size++] = elem;

    std::size_t index = m_size - 1;

    while (index != 0 && m_array[index] < m_array[(index-1)/2]) {
        std::swap(m_array[index], m_array[(index-1)/2]);

        index = (index - 1) / 2;
    }
}


template <typename T>
T MinHeap<T>::pop() {
    T toReturn (m_array[0]);

    m_array[0] = m_array[--m_size];

    siftdown(0);

    return toReturn;
}


template <typename T>
T MinHeap<T>::pop_push(const T& elem) {
    T toReturn (m_array[0]);

    m_array[0] = elem;

    siftdown(0);

    return toReturn;
}


template <typename T>
void MinHeap<T>::siftdown(std::size_t index) {
    while (index < m_size) {
        std::size_t left  = index * 2 + 1;
        std::size_t right = index * 2 + 2;

        // neither left or right is within index
        if (left >= m_size) return;

        // left is within range, right is not
        if (right == m_size) {
            if (m_array[index] > m_array[left]) {
                std::swap(m_array[index], m_array[left]);
            }
            return;
        }

        // both left and right are within range
        if (m_array[index] < m_array[left]) {
            if (m_array[index] < m_array[right]) {
                return;
            } else /* m_array[index] > m_array[right] */ {
                std::swap(m_array[index], m_array[right]);
                index = right;
            }
        } else /* m_array[index] > m_array[left] */ {
            if (m_array[left] < m_array[right]) {
                std::swap(m_array[index], m_array[left]);
                index = left;
            } else /* m_array[left] > m_array[right] */ {
                std::swap(m_array[index], m_array[right]);
                index = right;
            }
        }
    }
}


#endif  // MINHEAP_H
