// sort.h


// WARNING: sorting method here assumes
//          random access capabilities

#ifndef SORT_H
#define SORT_H

#include <utility>  // for std::swap


// TODO: implement different
// ways of choosing piovt

// end is the last element past 1
template <typename T>
void quicksort(T *begin, T *end) {
    if (end - begin <= 1) {
        return;
    }

    T &pivot  = *begin;
    T *divide = end;

    for (T* elem = begin+1; elem < divide; ++elem)
        if (*elem > pivot)
            std::swap(*(elem--), *(--divide));

    std::swap(*begin, *(divide-1));

    quicksort(begin, divide);
    quicksort(divide, end);
}


// end is the last element past 1
template <typename T>
void mergesort(T *begin, T *end) {
    // <= 1 element
    if (end - begin <= 1) return;
    // 2 elements
    if (end - begin == 2) {
        if (*begin > *(begin+1))
            std::swap(*begin, *(begin+1));
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

    for (index = 0; begin < end; ++begin)
        *begin = sorted[index++];

    delete[] sorted;
}


// quick-selection returns the n th order
// statistic of the array and runs in O(n) time in average
// n th order statistic begins with 0.

// NOTE: quick-selection will change the
// order of the original array.

// end is the last element past 1

template <typename T>
T& quickselect(T *begin, T *end, int n) {
    // if (n < 0 || end - begin <= n) throw "unable to find n th element";

    T &pivot  = *begin;
    T *divide = end;

    for (T *elem = begin+1; elem < divide; ++elem)
        if (pivot < *elem)
            std::swap(*elem--, *--divide);

    int pivot_stat = divide - begin - 1;

    if (pivot_stat == n) return *begin;
    else if (pivot_stat > n)
        return quickselect(begin+1, divide, n);
    else // pivot_stat < n
        return quickselect(divide, end, n-pivot_stat-1);
}


#endif  // SORT_H
