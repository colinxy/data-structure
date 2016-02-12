// maxheap.h


#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <cstddef>  // for std::size_t
#include <utility>  // for std::swap


template <class T>
class MaxHeap {
public:
      // constructor
    MaxHeap(std::size_t capacity = 8);
      // copy constructor
    MaxHeap(const MaxHeap<T> &, std::size_t capacity = 8);
      // assignment operator
    MaxHeap<T> &operator= (const MaxHeap<T> &);
      // destructor
    ~MaxHeap();

      // accessor
    std::size_t   capacity() const;
    std::size_t   size()     const;
    const T&      peek()     const;

      // mutator
    void push(const T&);
    T    pop();
    T    pop_push(const T&);

      // override swap
    friend void swap(MaxHeap<T> &, MaxHeap<T> &);

private:
    void siftdown(std::size_t);

    std::size_t m_capacity;
    std::size_t m_size;
    T          *m_array;
};


template <class T>
MaxHeap<T>::MaxHeap(std::size_t capacity)
    : m_capacity(capacity)
    , m_size(0) {

    m_array = new T[m_capacity];
}


template <class T>
MaxHeap<T>::MaxHeap(const MaxHeap<T> &mh, std::size_t capacity) {
    if (capacity < mh.size())
        capacity = mh.size();

    m_capacity = capacity;
    m_size     = 0;

    for (std::size_t i = 0; i < mh.size(); ++i)
        m_array[m_size++];
}


template <typename T>
MaxHeap<T> & MaxHeap<T>::operator= (const MaxHeap<T> &rhs) {
    if (this != &rhs) {
        MaxHeap<T> temp(rhs);
        swap(*this, temp);
    }

    return *this;
}


template <class T>
MaxHeap<T>::~MaxHeap() {
    delete[] m_array;
}


template <typename T>
void swap(MaxHeap<T> &lhs, MaxHeap<T> &rhs) {
    std::swap(lhs.m_capacity, rhs.m_capacity);
    std::swap(lhs.m_size,     rhs.m_size);
    std::swap(lhs.m_array,    rhs.m_array);
}


template <class T>
std::size_t MaxHeap<T>::capacity() const {
    return m_capacity;
}


template <class T>
std::size_t MaxHeap<T>::size() const {
    return m_size;
}


template <class T>
const T& MaxHeap<T>::peek() const {
    return m_array[0];
}


template <class T>
void MaxHeap<T>::push(const T& elem) {
    // TODO: resize the heap

    m_array[m_size++] = elem;

    std::size_t index = m_size - 1;

    while (index != 0 && m_array[index] > m_array[(index-1)/2]) {
        std::swap(m_array[index], m_array[(index-1)/2]);

        index = (index - 1) / 2;
    }
}


template <class T>
T MaxHeap<T>::pop() {
    T toReturn (m_array[0]);

    m_array[0] = m_array[--m_size];

    siftdown(0);

    return toReturn;
}


template <class T>
T MaxHeap<T>::pop_push(const T& elem) {
    T toReturn (m_array[0]);

    m_array[0] = elem;

    siftdown(0);

    return toReturn;
}


template <class T>
void MaxHeap<T>::siftdown(std::size_t index) {
    while (index < m_size) {
        std::size_t left  = index * 2 + 1;
        std::size_t right = index * 2 + 2;

        // neither left or right is within index
        if (left >= m_size) return;

        // left is within range, right is not
        if (right == m_size) {
            if (m_array[index] < m_array[left]) {
                std::swap(m_array[index], m_array[left]);
            }
            return;
        }

        // both left and right are within range
        if (m_array[index] > m_array[left]) {
            if (m_array[index] > m_array[right]) {
                return;
            } else /* m_array[index] < m_array[right] */ {
                std::swap(m_array[index], m_array[right]);
                index = right;
            }
        } else /* m_array[index] < m_array[left] */ {
            if (m_array[left] > m_array[right]) {
                std::swap(m_array[index], m_array[left]);
                index = left;
            } else /* m_array[left] < m_array[right] */ {
                std::swap(m_array[index], m_array[right]);
                index = right;
            }
        }
    }
}


#endif  // MAXHEAP_H
