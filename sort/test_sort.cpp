#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "sort.h"
using namespace std;

const int SIZE = 100000;

void test_sort(void (*sort_fn)(int*, int*)) {
    int test_sorted[SIZE];
    int  lib_sorted[SIZE];

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

int main() {
    test_sort(&quicksort);
    test_sort(&mergesort);

    cout << "all tests passed" << endl;
    return 0;
}
