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
    assert(mpi.popPush(-1) == 0);
    assert(mpi.popPush(0) == -1);
    for (int i = 0; i < 10; ++i) {
        assert(mpi.peek() == i);
        assert(mpi.pop() == i);
        assert(mpi.size() == 9-i);
    }

    /*
     * randomized pop push test
     */
    MinHeap<int> mh(SIZE+10);
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
     * popPush test
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
     mh_other.popPush(arr_other[0]);
     sort(arr_other, arr_other+SIZE);
     for (int i = 0; i < SIZE; ++i) {
         assert(mh_other.pop() == arr_other[i]);
     }
}


int main() {
    test_minheap();

    cout << "all test passed" << endl;
    return 0;
}
