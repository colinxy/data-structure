// seg_tree.h


#include <iostream>
#include <vector>
using namespace std;


class SegTreeSum {
public:
    SegTreeSum(size_t size);
    SegTreeSum(int* arr, size_t size);

      // override output stream for inspection purposes
    friend ostream& operator<< (ostream&, SegTreeSum);

    size_t size() const;

    int  sum(size_t begin, size_t end) const;
    void update(int value, size_t index);

private:
      // helper function for constructor
    static size_t computeCapacity(size_t size);
    int construct(int* arr, size_t index, size_t begin, size_t end);

      // helper function for sum
    int sumHelper(size_t, size_t, size_t, size_t, size_t) const;

      // helper function for update
    int updateHelper(int, size_t, size_t, size_t, size_t);

      // helper function for navigation
    static size_t left(size_t);
    static size_t right(size_t);
    static size_t parent(size_t);

    size_t      m_size;
    vector<int> m_sums;
};
