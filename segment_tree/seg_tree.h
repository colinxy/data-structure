// seg_tree.h


#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H


#include <iostream>
#include <vector>


class SegTreeSum {
public:
    SegTreeSum(size_t);
    SegTreeSum(int*, size_t);

      // override output stream for inspection purposes
    friend std::ostream& operator<< (std::ostream&, SegTreeSum &);

    size_t size() const;

    int  sum(size_t, size_t) const;
    void update(int, size_t);

private:
      // helper function for constructor
    static size_t computeCapacity(size_t);
    int construct(int*, size_t, size_t, size_t);

      // helper function for sum
    int sumHelper(size_t, size_t, size_t, size_t, size_t) const;

      // helper function for update
    int updateHelper(int, size_t, size_t, size_t, size_t);

      // helper function for navigation
    static size_t left(size_t);
    static size_t right(size_t);
    static size_t parent(size_t);

    size_t           m_size;
    std::vector<int> m_sums;
};


#endif  // SEGMENT_TREE_H
