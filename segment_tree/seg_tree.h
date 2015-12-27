// seg_tree.h


#include <iostream>
#include <vector>
using namespace std;


class SegTreeSum {
public:
    SegTreeSum(const int* &arr, size_t size);

    int  sum(size_t begin, size_t end);
    void update(int value, size_t index);

private:
      // helper function for constructor
    static int computeCapacity(const size_t &size);
    int construct(const int* &arr, size_t index, size_t begin, size_t end);

      // helper function for sum
    int sumHelper(size_t, size_t, size_t, size_t, size_t);

      // helper function for update
    int updateHelper(const int&, size_t, size_t, size_t, size_t);

    static size_t left(size_t);
    static size_t right(size_t);
    static size_t parent(size_t);

    size_t      m_size;
    vector<int> m_arr;
};
