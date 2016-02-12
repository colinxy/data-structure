// stack.h


#ifndef STACK_H
#define STACK_H

#include <cstddef>  // for std::size_t


class Stack {
public:
    Stack(std::size_t=8);
    Stack(const Stack &);
    Stack &operator= (const Stack &);
    ~Stack();

    std::size_t capacity() const;
    bool empty() const;
    void push(const int&);
    int  pop();

    // override swap
    friend void swap(Stack &, Stack &);

private:
    std::size_t m_capacity;
    int        *m_stack;
    // the elem at the top of the stack is
    // m_stack[m_top-1]
    std::size_t m_top;
};


#endif  // STACK_H
