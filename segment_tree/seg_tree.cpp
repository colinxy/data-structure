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
    if (begin >= m_size)
        throw 1;

    return sumHelper(0, begin, end, 0, m_size);
}


void SegTreeSum::update(int value, size_t index) {
    updateHelper(value, 0, index, 0, m_size);
}


inline size_t SegTreeSum::computeCapacity(size_t size) {
    size_t capacity = 1;
    while (capacity < size) {
        capacity *= 2;
    }
    return capacity * 2 - 1;
}


int SegTreeSum::construct(int* arr, size_t treeIndex, size_t begin, size_t end) {
    if (end - begin == 1) {
        m_sums[treeIndex] = arr[begin];
        return m_sums[treeIndex];

    } else {
        size_t mid = begin + (end - begin) / 2;
        size_t leftIndex  = left(treeIndex);
        size_t rightIndex = right(treeIndex);

        m_sums[treeIndex] = construct(arr, leftIndex , begin, mid) + \
                            construct(arr, rightIndex, mid  , end);

        return m_sums[treeIndex];
    }
}


/*
 * begin and end are the actual index of the array
 */

int SegTreeSum::sumHelper(size_t treeIndex,
                          size_t queryBegin, size_t queryEnd,
                          size_t begin,      size_t end) const {
      // empty query
    if (queryEnd <= queryBegin)
        return 0;

      // query exactly the range
    if (begin == queryBegin && end == queryEnd)
        return m_sums[treeIndex];

    size_t mid = begin + (end - begin) / 2;
    size_t leftIndex  = left(treeIndex);
    size_t rightIndex = right(treeIndex);

    if (queryEnd <= mid)
        return sumHelper(leftIndex, queryBegin, queryEnd, begin, mid);
    else if (queryBegin >= mid)
        return sumHelper(rightIndex, queryBegin, queryEnd, mid, end);

    return sumHelper(leftIndex , queryBegin, mid     , begin, mid) + \
           sumHelper(rightIndex, mid       , queryEnd, mid  , end);
}


/*
 * begin and end are the actual index of the array
 */

int SegTreeSum::updateHelper(int value, size_t treeIndex, size_t arrayIndex,
                                        size_t begin, size_t end) {
    int delta;

    if (begin == arrayIndex && end - begin == 1) {
        delta = value - m_sums[treeIndex];
        m_sums[treeIndex] += delta;
        return delta;
    }

    size_t mid = begin + (end - begin) / 2;
    if (arrayIndex < mid) {
        delta = updateHelper(value, left(treeIndex), arrayIndex, begin, mid);
    } else {
        delta = updateHelper(value, right(treeIndex), arrayIndex, mid, end);
    }

    m_sums[treeIndex] += delta;

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
