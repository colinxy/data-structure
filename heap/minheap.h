// minheap.h


#include <iostream>
#include <utility>
using namespace std;


template <class T>
class MinHeap {
public:
      // constructor
    MinHeap(size_t capacity = 8);
    MinHeap(const MinHeap<T> &, size_t capacity = 8);
      // destructor
    ~MinHeap();

      // accessor
    size_t   capacity() const;
    size_t   size()     const;
    const T& peek()     const;

      // mutator
    void push(const T&);
    T    pop();
    T    popPush(const T&);

private:
    void siftdown(size_t);

    size_t m_capacity;
    size_t m_size;
    T      *m_array;
};


template <class T>
MinHeap<T>::MinHeap(size_t capacity) : m_capacity(capacity)
                                     , m_size(0) {
    m_array = new T[m_capacity];
}


template <class T>
MinHeap<T>::MinHeap(const MinHeap<T> &mh, size_t capacity) {
    if (capacity < mh.size()) capacity = mh.size();

    m_capacity = capacity;
    m_size     = 0;

    for (size_t i = 0; i < mh.size(); ++i)
        m_array[m_size++];
}


template <class T>
MinHeap<T>::~MinHeap() {
    delete[] m_array;
}


template <class T>
size_t MinHeap<T>::capacity() const {
    return m_capacity;
}


template <class T>
size_t MinHeap<T>::size() const {
    return m_size;
}


template <class T>
const T& MinHeap<T>::peek() const {
    return m_array[0];
}


template <class T>
void MinHeap<T>::push(const T& elem) {
    m_array[m_size++] = elem;

    size_t index = m_size - 1;

    while (index != 0 && m_array[index] < m_array[(index-1)/2]) {
        swap(m_array[index], m_array[(index-1)/2]);

        index = (index - 1) / 2;
    }
}


template <class T>
T MinHeap<T>::pop() {
    T toReturn (m_array[0]);

    m_array[0] = m_array[--m_size];

    siftdown(0);

    return toReturn;
}


template <class T>
T MinHeap<T>::popPush(const T& elem) {
    T toReturn (m_array[0]);

    m_array[0] = elem;

    siftdown(0);

    return toReturn;
}


template <class T>
void MinHeap<T>::siftdown(size_t index) {
    while (index < m_size) {
        size_t left  = index * 2 + 1;
        size_t right = index * 2 + 2;

        // neither left or right is within index
        if (left >= m_size) return;

        // left is within range, right is not
        if (right == m_size) {
            if (m_array[index] > m_array[left]) {
                swap(m_array[index], m_array[left]);
            }
            return;
        }

        // both left and right are within range
        if (m_array[index] <= m_array[left]) {
            if (m_array[index] <= m_array[right]) {
                return;
            } else /* m_array[index] > m_array[right] */ {
                swap(m_array[index], m_array[right]);
                index = right;
            }
        } else /* m_array[index] > m_array[left] */ {
            if (m_array[left] < m_array[right]) {
                swap(m_array[index], m_array[left]);
                index = left;
            } else /* m_array[left] >= m_array[right] */ {
                swap(m_array[index], m_array[right]);
                index = right;
            }
        }
    }
}
