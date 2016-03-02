// test_sort.cpp


#include "sort.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;


const int SIZE = 1000000;
int test_sorted[SIZE];
int  lib_sorted[SIZE];


void test_sort(void (*sort_fn)(int*, int*)) {
    srand(time(NULL));

    for (int i = 0; i < SIZE; ++i) {
        test_sorted[i] = rand();
        lib_sorted[i]  = test_sorted[i];
    }

    sort_fn(test_sorted, test_sorted+SIZE);
    sort(lib_sorted, lib_sorted+SIZE);

    for (int i = 0; i < SIZE; ++i) {
        assert(test_sorted[i] == lib_sorted[i]);
        // cout << test_sorted[i] << endl;
    }
}


void test_select(int& (*select_fn)(int*, int*, int)) {
    int to_select[10]{1, 2, 3, 7, 4, 9, 6, 5, 8, 0};
    assert(select_fn(to_select, to_select+10, 5) == 5);

    srand(time(NULL));

    for (int i = 0; i < SIZE; ++i) {
        test_sorted[i] = rand();
        lib_sorted[i]  = test_sorted[i];
    }

    int nth = rand();
    while (nth >= SIZE) nth /= 2;
    // cout << nth << endl;

    sort(lib_sorted, lib_sorted+SIZE);
    // cout << lib_sorted[nth] << endl;
    assert(select_fn(test_sorted, test_sorted+SIZE, nth)
           == lib_sorted[nth]);
}


int main() {
    test_sort(quicksort);
    test_sort(mergesort);

    test_select(quickselect);

    cout << "all tests passed" << endl;
    return 0;
}
