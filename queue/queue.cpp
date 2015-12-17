// queue.cpp

#include <iostream>
#include <stdexcept>
#include "queue.h"
using namespace std;

Queue::Queue(size_t capacity) {
    m_capacity = capacity;
    m_queue = new int[capacity];

    m_size  = 0;
    m_front = 0;
    m_back  = 0;
}

Queue::~Queue() {
    delete[] m_queue;
}

size_t Queue::capacity() const {
    return m_capacity;
}

bool Queue::empty() const {
    return m_size == 0;
}

void Queue::push_back(int elem) {
    if (m_size == m_capacity) throw overflow_error("cannot push to a full queue");

    m_queue[m_back] = elem;
    m_back = (m_back + 1) % m_capacity;
    ++m_size;
}

int Queue::pop_front() {
    if (m_size == 0) throw underflow_error("cannot pop from an empty queue");

    int front = m_queue[m_front];
    m_front = (m_front + 1) % m_capacity;
    --m_size;
    return front;
}
