#include <iostream>
using namespace std;


template <class T>
void exchange(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// TODO: implement different
// ways of choosing piovt

// end is the last element past 1
template <class T>
void quicksort(T *begin, T *end) {
    if (end - begin <= 1) {
        return;
    }

    T &pivot  = *begin;
    T *divide = end;

    for (T* elem = begin+1; elem < divide; ++elem) {
        if (*elem > pivot) {
            exchange(*(elem--), *(--divide));
        }
    }

    exchange(*begin, *(divide-1));

    quicksort(begin, divide);
    quicksort(divide, end);
}
