// sort.h


// WARNING: sorting method here assumes
//          random access capabilities

#ifndef SORT_H_
#define SORT_H_

#include <utility>  // for std::swap

// end is the last element past 1


template <typename T>
inline T *medianof3(T *a, T *b, T *c) {
    if (*a < *b)
        if (*b < *c)            // a < b < c
            return b;
        else if (*a < *c)       // a < c < b
            return c;
        else                    // c < a < b
            return a;
    else
        if (*c < *b)            // c < b < a
            return b;
        else if (*a < *c)       // b < a < c
            return a;
        else                    // b < c < a
            return c;
}


// choice of pivot: median of first middle, last
template <typename T>
void quicksort(T *begin, T *end) {
    if (end - begin <= 1)
        return;

    T *mid = begin + (end - begin) / 2;
    T *pivot = medianof3(begin, mid, end-1);
    std::swap(*begin, *pivot);
    pivot = begin;

    T *divide = end;
    for (T* elem = begin+1; elem < divide; ++elem)
        if (*elem > *pivot)
            std::swap(*(elem--), *(--divide));

    std::swap(*begin, *(divide-1));

    // IMPORTANT: has to use divide-1 for worse case to reduce problem size
    quicksort(begin, divide-1);
    quicksort(divide, end);
}


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
    std::size_t size = end - begin;
    T *mid = begin + size / 2;
    mergesort(begin, mid);
    mergesort(mid, end);

    // merge
    T *left  = begin;
    T *right = mid;
    T *sorted = new T[size];
    std::size_t index = 0;

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


template <typename T>
void siftdown(T *heap, std::size_t index, const std::size_t size) {
    std::size_t curr = index;

    while (curr < size) {
        std::size_t left = curr * 2 + 1;
        std::size_t right = curr * 2 + 2;

        if (right < size) {         // both children exist
            if (heap[curr] < heap[left])
                if (heap[left] < heap[right]) {
                    std::swap(heap[curr], heap[right]);
                    curr = right;
                    continue;
                } else {
                    std::swap(heap[curr], heap[left]);
                    curr = left;
                    continue;
                }
            else if (heap[curr] < heap[right]) {
                std::swap(heap[curr], heap[right]);
                curr = right;
                continue;
            }

        } else if (left < size) {   // only left child exist
            if (heap[curr] < heap[left]) {
                std::swap(heap[curr], heap[left]);
                curr = left;
                continue;
            }
        }

        break;
    }
}


template <typename T>
void heapsort(T *begin, T *end) {
    std::size_t size = end - begin;

    // start with the element in the middle
    for (long index = size/2; index >= 0; --index)
        siftdown(begin, index, size);

    for (long index = size-1; index >= 0; --index) {
        std::swap(begin[index], begin[0]);

        siftdown(begin, 0, index /* size */);
    }
}


// quick-selection returns the n th order
// statistic of the array and runs in O(n) time in average
// n th order statistic begins with 0.

// NOTE: quick-selection will change the
// order of the original array.
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


#endif  // SORT_H_
