// test_seg_tree.cpp


#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <utility>
#include "seg_tree.h"
using namespace std;


const int SIZE = 1000000;
int arr_large[SIZE];
int arr_sums [SIZE+1];

void test_seg_tree() {
      // constructor, sum, update
    int size = 3;
    SegTreeSum st(size);
    for (int i = 0; i < size; ++i) {
        st.update(i, i);
    }
    for (int i = 0; i < size; ++i) {
        for (int j = i+1; j <= size; ++j) {
            int sum = st.sum(i, j);
            assert(sum == (i + (j-1)) * (j-i) / 2);
        }
    }

      // constructor, sum
    int arr[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size = sizeof(arr)/sizeof(int);
    SegTreeSum st_other(arr, size);
    for (int i = 0; i < size; ++i) {
        for (int j = i+1; j <= size; ++j) {
            int sum = st_other.sum(i, j);
            assert(sum == (i + (j-1)) * (j-i) / 2);
        }
    }

      // randomized test
    srand(time(nullptr));
    arr_sums[0] = 0;
    for (int i = 0; i < SIZE; ++i) {
        arr_large[i] = rand();
        arr_sums[i+1]  = arr_sums[i] + arr_large[i];
    }
    // construct the tree
    SegTreeSum st_large(arr_large, SIZE);
    // sum test
    for (int i = 1; i <= SIZE; ++i) {
        assert(st_large.sum(0, i) == arr_sums[i]);
    }
    // update test
    arr_large[SIZE / 347] = rand();
    st_large.update(arr_large[SIZE/347], SIZE/347);
    arr_large[SIZE / 56]  = rand();
    st_large.update(arr_large[SIZE/56], SIZE/56);
    for (int i = 0; i < SIZE; ++i) {
        arr_sums[i+1] = arr_sums[i] + arr_large[i];
    }
    for (int i = 1; i <= SIZE; ++i) {
        assert(st_large.sum(0, i) == arr_sums[i]);
    }
    for (int i = 0; i < 1000; ++i) {
        int rand1 = (int)(1.0 / rand() * SIZE);
        int rand2 = (int)(1.0 / rand() * SIZE);
        if (rand1 > rand2) swap(rand1, rand2);
        assert(st_large.sum(rand1, rand2) == arr_sums[rand2] - arr_sums[rand1]);
    }
}


int main() {
    test_seg_tree();

    cout << "all tests passed" << endl;
    return 0;
}
