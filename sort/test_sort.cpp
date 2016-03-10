// test_sort.cpp


#include "sort.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;


void test_sort(const int *arr, int size, void (*sort_fn)(int*, int*)) {
    int *test_sorted = new int[size];
    int *lib_sorted  = new int[size];

    std::copy(arr, arr+size, test_sorted);
    std::copy(arr, arr+size, lib_sorted);

    sort_fn(test_sorted, test_sorted+size);
    sort(lib_sorted, lib_sorted+size);

    for (int i = 0; i < size; ++i) {
        assert(test_sorted[i] == lib_sorted[i]);
        // cout << test_sorted[i] << endl;
    }

    delete test_sorted;
    delete lib_sorted;
}


void test_select(const int *arr, int size,
                 int& (*select_fn)(int*, int*, int)) {
    // small test
    int to_select[10]{1, 2, 3, 7, 4, 9, 6, 5, 8, 0};
    assert(select_fn(to_select, to_select+10, 5) == 5);

    int *test_sorted = new int[size];
    int *lib_sorted  = new int[size];

    std::copy(arr, arr+size, test_sorted);
    std::copy(arr, arr+size, lib_sorted);

    int nth = rand();
    while (nth >= size) nth /= 2;
    // cout << nth << endl;

    sort(lib_sorted, lib_sorted+size);
    // cout << lib_sorted[nth] << endl;
    assert(select_fn(test_sorted, test_sorted+size, nth) ==
           lib_sorted[nth]);

    delete test_sorted;
    delete lib_sorted;
}


int main() {
    srand(time(NULL));

    const int SIZE = 1000000;
    int arr[SIZE];

    for (int i = 0; i < SIZE; ++i)
        arr[i] = rand();

    {
        auto start = clock();
        cout << "quicksort : ";
        test_sort(arr, SIZE, quicksort);
        cout << (double)(clock() - start) / CLOCKS_PER_SEC << 's' << endl;
    }

    {
        auto start = clock();
        cout << "mergesort : ";
        test_sort(arr, SIZE, mergesort);
        cout << (double)(clock() - start) / CLOCKS_PER_SEC << 's' << endl;
    }

    {
        auto start = clock();
        cout << "heapsort  : ";
        test_sort(arr, SIZE, heapsort);
        cout << (double)(clock() - start) / CLOCKS_PER_SEC << 's' << endl;
    }

    test_select(arr, SIZE, quickselect);

    cout << endl << "all tests passed" << endl;
    return 0;
}
