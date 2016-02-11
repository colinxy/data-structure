// queue.h

/*
 * fixed size circular integer queue, does not resize
 */


#ifndef QUEUE_H
#define QUEUE_H


class Queue {
public:
    Queue(size_t capacity=8);
    Queue(const Queue &);
    Queue &operator= (const Queue &);
    ~Queue();

      // accessor
    size_t capacity() const;
    bool empty() const;

      // mutator
    void push_back(int);
    int  pop_front();

      // override swap
    friend void swap(Queue &, Queue &);

private:
    size_t m_capacity;
    size_t m_size;

    int *m_queue;
    // the fisrt element is m_queue[m_front]
    size_t m_front;
    // the last  element is m_queue{m_back-1]
    size_t m_back;
};


#endif  // QUEUE_H
