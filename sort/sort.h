#include <iostream>
using namespace std;

// WARNING: sorting method here assumes
//          consecutive data field

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


// end is the last element past 1
template <class T>
void mergesort(T *begin, T *end) {
    // <= 1 element
    if (end - begin <= 1) return;
    // 2 elements
    if (end - begin == 2) {
        if (*begin > *(begin+1))
            exchange(*begin, *(begin+1));
        return;
    }

    // sort first half and second half
    size_t size = end - begin;
    T *mid = begin + size / 2;
    mergesort(begin, mid);
    mergesort(mid, end);

    // merge
    T *left  = begin;
    T *right = mid;
    T *sorted = new T[size];
    size_t index = 0;

    while (left < mid && right < end)
        sorted[index++] = (*left < *right) ? *left++ : *right++;

    if (left == mid)
        for (; right < end; ++right)
            sorted[index++] = *right;

    else if (right == end)
        for (; left < mid; ++left)
            sorted[index++] = *left;

    index = 0;
    for (; begin < end; ++begin)
        *begin = sorted[index++];
}
