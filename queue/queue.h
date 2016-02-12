// queue.h

/*
 * fixed size circular integer queue, does not resize
 */


#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>  // for std::size_t


class Queue {
public:
    Queue(std::size_t capacity=8);
    Queue(const Queue &);
    Queue &operator= (const Queue &);
    ~Queue();

      // accessor
    std::size_t capacity() const;
    bool        empty() const;

      // mutator
    void push_back(int);
    int  pop_front();

      // overload swap
    friend void swap(Queue &, Queue &);

private:
    std::size_t m_capacity;
    std::size_t m_size;

    int        *m_queue;
    // the fisrt element is m_queue[m_front]
    std::size_t m_front;
    // the last  element is m_queue{m_back-1]
    std::size_t m_back;
};


#endif  // QUEUE_H
