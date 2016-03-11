// test_sort.cpp


#include <iostream>
#include "sort.h"
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>
using namespace std;


void test_sort(const int *arr, const int size, void (*sort_fn)(int*, int*)) {
    int *test_sorted = new int[size];
    int *lib_sorted  = new int[size];

    std::copy(arr, arr+size, test_sorted);
    std::copy(arr, arr+size, lib_sorted);

    sort_fn(test_sorted, test_sorted+size);
    sort(lib_sorted, lib_sorted+size);

    for (int i = 0; i < size; ++i)
        assert(test_sorted[i] == lib_sorted[i]);

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


const unsigned int SIZE = 120000;

int main() {
    srand(time(NULL));
    int *arr_rand = new int[SIZE];
    for (int i = 0; i < SIZE; ++i)
        arr_rand[i] = rand();

    int *arr_sorted = new int[SIZE];
    std::copy(arr_rand, arr_rand+SIZE, arr_sorted);
    std::sort(arr_sorted, arr_sorted+SIZE);

    int *arr_reverse = new int[SIZE];
    std::copy(arr_rand, arr_rand+SIZE, arr_reverse);
    std::sort(arr_reverse, arr_reverse+SIZE, std::greater<int>());

    // arrays goes here
    const int *arrays[] = {arr_rand, arr_sorted, arr_reverse};
    const char *tags[] = {"random", "sorted", "reversely sorted"};
    const int num_arr = sizeof(arrays) / sizeof(int*);

    // sorting algorithm goes here
    typedef void (*SORT_FN)(int*, int*);
    SORT_FN sort_algos[] = {quicksort, mergesort, heapsort};
    const char *sort_tags[] = {"quicksort", "mergesort", "heapsort"};
    const int num_algo = sizeof(sort_algos) / sizeof(SORT_FN);

    for (int i = 0; i < num_arr; ++i) {
        std::printf("sorting a %s array\n", tags[i]);

        for (int j = 0; j < num_algo; ++j) {
            auto start = clock();

            std::printf("%-10s: ", sort_tags[j]);
            test_sort(arrays[i], SIZE, sort_algos[j]);

            std::printf("%f s\n", (double)(clock() - start) / CLOCKS_PER_SEC);
        }

        std::printf("\n");
    }

    // quick selection
    test_select(arr_rand, SIZE, quickselect);

    delete arr_rand;
    delete arr_sorted;
    delete arr_reverse;

    cout << "all tests passed" << endl;
    return 0;
}
