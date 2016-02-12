// queue.cpp


#include "queue.h"
#include <iostream>
#include <utility>
#include <stdexcept>
using namespace std;


Queue::Queue(size_t capacity)
    : m_capacity(capacity)
    , m_size(0)
    , m_front(0)
    , m_back(0) {

    m_queue = new int[capacity];
}


Queue::Queue(const Queue &rhs)
    : m_capacity(rhs.m_capacity)
    , m_size    (rhs.m_size)
    , m_front   (rhs.m_front)
    , m_back    (rhs.m_back) {

    m_queue = new int[m_capacity];

    if (m_back >= m_front) {
        for (size_t i = m_front; i < m_back; ++i)
            m_queue[i] = rhs.m_queue[i];

    } else {
        for (size_t i = m_front; i < m_size; ++i)
            m_queue[i] = rhs.m_queue[i];

        for (size_t i = 0; i < m_back; ++i)
            m_queue[i] = rhs.m_queue[i];
    }
}


Queue & Queue::operator= (const Queue &rhs) {
    if (this != &rhs) {
        Queue temp(rhs);
        swap(*this, temp);
    }

    return *this;
}


Queue::~Queue() {
    delete[] m_queue;
}


// actually unneeded
void swap(Queue &lhs, Queue &rhs) {
    swap(lhs.m_capacity, rhs.m_capacity);
    swap(lhs.m_size,     rhs.m_size);
    swap(lhs.m_queue,    rhs.m_queue);
    swap(lhs.m_front,    rhs.m_front);
    swap(lhs.m_back,     rhs.m_back);
}


size_t Queue::capacity() const {
    return m_capacity;
}


bool Queue::empty() const {
    return m_size == 0;
}


void Queue::push_back(int elem) {
    if (m_size == m_capacity)
        throw overflow_error("cannot push to a full queue");

    m_queue[m_back] = elem;
    m_back = (m_back + 1) % m_capacity;
    ++m_size;
}


int Queue::pop_front() {
    if (m_size == 0)
        throw underflow_error("cannot pop from an empty queue");

    int front = m_queue[m_front];
    m_front = (m_front + 1) % m_capacity;
    --m_size;
    return front;
}
