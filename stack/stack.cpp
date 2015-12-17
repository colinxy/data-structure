#include <iostream>
#include <stdexcept>
#include "stack.h"
using namespace std;

Stack::Stack(size_t capacity) {
    m_capacity = capacity;
    m_stack = new int[capacity];
    m_top = 0;
}

size_t Stack::capacity() const {
    return m_capacity;
}

bool Stack::empty() const {
    return m_top == 0;
}

void Stack::push(const int &elem) {
    if (m_top >= m_capacity) throw overflow_error("cannot push to a full stack");

    m_stack[m_top++] = elem;
}

int Stack::pop() {
    if (m_top == 0) throw underflow_error("cannot pop from an empty stack");

    --m_top;
    return m_stack[m_top];
}
