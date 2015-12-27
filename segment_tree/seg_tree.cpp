// seg_tree.cpp


#include "seg_tree.h"

/*
 * `end' is always the last element past 1
 */


SegTreeSum::SegTreeSum(size_t size) : m_size(size)
                                    , m_sums(computeCapacity(size)) {
}


SegTreeSum::SegTreeSum(int* arr, size_t size) : m_size(size)
                                              , m_sums(computeCapacity(size)) {
    construct(arr, 0, 0, size);
}


ostream& operator<< (ostream& output, SegTreeSum sts) {
    output << '[';
    for (size_t i = 0; i < sts.m_sums.size(); ++i) {
        output << sts.m_sums[i] << ", ";
    }
    output << ']';

    return output;
}


size_t SegTreeSum::size() const {
    return m_size;
}


int SegTreeSum::sum(size_t begin, size_t end) const {
    if (begin == end)
        return 0;

    return sumHelper(0, begin, end, 0, m_size);
}


void SegTreeSum::update(int value, size_t index) {
    updateHelper(value, index, 0, 0, m_size);
}


inline size_t SegTreeSum::computeCapacity(size_t size) {
    size_t capacity = 1;
    while (capacity < size) {
        capacity *= 2;
    }
    return capacity * 2 - 1;
}


int SegTreeSum::construct(int* arr, size_t index, size_t begin, size_t end) {
    if (end - begin == 1) {
        m_sums[index] = arr[begin];
        return m_sums[index];

    } else {
        size_t mid = begin + (end - begin) / 2;
        size_t leftChild  = left(index);
        size_t rightChild = right(index);

        m_sums[index] = construct(arr, leftChild , begin, mid) + \
                        construct(arr, rightChild, mid  , end);

        return m_sums[index];
    }
}


int SegTreeSum::sumHelper(size_t index,
                          size_t queryBegin, size_t queryEnd,
                          size_t begin,      size_t end) const {

    if (queryEnd <= begin && end <= queryEnd) {
        return m_sums[index];
    }

    size_t mid = begin + (end - begin) / 2;
    size_t leftChild  = left(index);
    size_t rightChild = right(index);

    return sumHelper(leftChild , queryBegin, mid     , begin, mid) + \
           sumHelper(rightChild, mid       , queryEnd, mid  , end);
}


int SegTreeSum::updateHelper(int value, size_t index, size_t currentIndex,
                                        size_t begin, size_t end) {
    int delta;

    if (begin == index && end - begin == 1) {
        delta = value - m_sums[begin];
        m_sums[begin] += delta;
        return delta;
    }

    size_t mid = begin + (end - begin) / 2;
    if (index < mid) {
        delta = updateHelper(value, index, left(index), begin, mid);
    } else {
        delta = updateHelper(value, index, right(index), mid, end);
    }

    m_sums[currentIndex] += delta;

    return delta;
}


inline size_t SegTreeSum::left(size_t index) {
    return index * 2 + 1;
}


inline size_t SegTreeSum::right(size_t index) {
    return index * 2 + 2;
}


inline size_t SegTreeSum::parent(size_t index) {
    return (index - 1) / 2;
}
