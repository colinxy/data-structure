// test_heap.cpp


#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "minheap.h"
#include "maxheap.h"
using namespace std;


const int SIZE = 1006395;

void test_minheap() {
    MinHeap<int> mpi(100);

    /*
     * accessor and mutator test
     */
    assert(mpi.capacity() == 100);

    for (int i = 0; i < 10; ++i) {
        mpi.push(i);
        assert(mpi.size() == i+1);
        assert(mpi.peek() == 0);
    }
    assert(mpi.pop_push(-1) == 0);
    assert(mpi.pop_push(0) == -1);
    for (int i = 0; i < 10; ++i) {
        assert(mpi.peek() == i);
        assert(mpi.pop() == i);
        assert(mpi.size() == 9-i);
    }

    /*
     * randomized pop push test
     */
    MinHeap<int> mh(SIZE);
    int arr[SIZE];

    srand(time(nullptr));
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = rand();
        mh.push(arr[i]);
    }
    sort(arr, arr+SIZE);
    for (int i = 0; i < SIZE; ++i) {
        assert(mh.pop() == arr[i]);
    }

    /*
     * pop_push test
     */
     MinHeap<int> mh_other(SIZE);
     int arr_other[SIZE];

     srand(time(nullptr));
     for (int i = 0; i < SIZE; ++i) {
         arr_other[i] = rand();
         mh_other.push(arr_other[i]);
     }
     sort(arr_other, arr_other+SIZE);
     arr_other[0] = rand();
     mh_other.pop_push(arr_other[0]);
     sort(arr_other, arr_other+SIZE);
     for (int i = 0; i < SIZE; ++i) {
         assert(mh_other.pop() == arr_other[i]);
     }
}


void test_maxheap() {
    MaxHeap<int> mpi(100);

    /*
     * accessor and mutator test
     */
    assert(mpi.capacity() == 100);

    for (int i = 0; i < 10; ++i) {
        mpi.push(i);
        assert(mpi.size() == i+1);
        assert(mpi.peek() == i);
    }
    assert(mpi.pop_push(10) == 9);
    assert(mpi.pop_push(9) == 10);
    for (int i = 0; i < 10; ++i) {
        assert(mpi.peek() == 9-i);
        assert(mpi.pop() == 9-i);
        assert(mpi.size() == 9-i);
    }

    /*
     * randomized pop push test
     */
    MaxHeap<int> mh(SIZE);
    int arr[SIZE];

    srand(time(nullptr));
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = rand();
        mh.push(arr[i]);
    }
    sort(arr, arr+SIZE);
    for (int i = 0; i < SIZE; ++i) {
        assert(mh.pop() == arr[SIZE-i-1]);
    }

    /*
     * pop_push test
     */
     MaxHeap<int> mh_other(SIZE);
     int arr_other[SIZE];

     srand(time(nullptr));
     for (int i = 0; i < SIZE; ++i) {
         arr_other[i] = rand();
         mh_other.push(arr_other[i]);
     }
     sort(arr_other, arr_other+SIZE);
     arr_other[SIZE-1] = rand();
     mh_other.pop_push(arr_other[SIZE-1]);
     sort(arr_other, arr_other+SIZE);
     for (int i = 0; i < SIZE; ++i) {
         assert(mh_other.pop() == arr_other[SIZE-i-1]);
     }
}


int main() {
    test_minheap();
    test_maxheap();

    cout << "all test passed" << endl;
    return 0;
}
