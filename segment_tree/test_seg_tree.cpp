// test_seg_tree.cpp


#include <iostream>
#include <cassert>
#include "seg_tree.h"
using namespace std;


void test_seg_tree() {
      // constructor, sum, update
    SegTreeSum st(5);
    cout << st << endl;
    for (int i = 0; i < 5; ++i) {
        st.update(i, i);
        cout << st << endl;
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = i+1; j <= 5; ++i) {
            assert(st.sum(i, j) == (i + (j-1) * (j-i) / 2));
        }
    }

      // constructor, sum
    int arr[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    SegTreeSum st_other(arr, sizeof(arr)/sizeof(int));
    for (int i = 0; i < 10; ++i) {
        for (int j = i+1; j <= 10; ++i) {
            assert(st_other.sum(i, j) == (i + (j-1) * (j-i) / 2));
        }
    }
}


int main() {
    test_seg_tree();

    cout << "all tests passed" << endl;
    return 0;
}
