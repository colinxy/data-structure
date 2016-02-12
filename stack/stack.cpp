// stack.cpp


#include "stack.h"
#include <iostream>
#include <utility>
#include <stdexcept>
using namespace std;


Stack::Stack(size_t capacity)
    : m_capacity(capacity)
    , m_top(0) {

    m_stack = new int[capacity];
}


Stack::Stack(const Stack &rhs)
    : m_capacity(rhs.m_capacity)
    , m_top(rhs.m_top) {

    m_stack = new int [m_capacity];

    for (size_t i = 0; i < m_top; ++i)
        m_stack[i] = rhs.m_stack[i];
}


Stack & Stack::operator= (const Stack &rhs) {
    if (this != &rhs) {
        Stack temp(rhs);
        swap(*this, temp);
    }

    return *this;
}


Stack::~Stack() {
    delete[] m_stack;
}


void swap(Stack &lhs, Stack &rhs) {
    swap(lhs.m_capacity, rhs.m_capacity);
    swap(lhs.m_stack,    rhs.m_stack);
    swap(lhs.m_top,      rhs.m_top);
}


size_t Stack::capacity() const {
    return m_capacity;
}


bool Stack::empty() const {
    return m_top == 0;
}


void Stack::push(const int &elem) {
    if (m_top >= m_capacity)
        throw overflow_error("cannot push to a full stack");

    m_stack[m_top++] = elem;
}


int Stack::pop() {
    if (m_top == 0)
        throw underflow_error("cannot pop from an empty stack");

    --m_top;
    return m_stack[m_top];
}
