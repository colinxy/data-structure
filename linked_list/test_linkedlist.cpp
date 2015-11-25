#include <iostream>
#include <string>
#include <cassert>
#include "linkedlist.h"
using namespace std;

int main() {
    // test 1: linked list of ints
    LinkedList<int> ints;
    cout << sizeof(ints) << endl;
    assert(ints.empty());
    assert(ints.size() == 0);
    for (int i = 0; i < 10; ++i) {
        ints.push_back(i);
    }
    assert(ints.size() == 10);
    for (int i = 0; i < 10; ++i) {
        int current = ints.get(i);
        cout << current << endl;
        assert(current == i);
    }
    for (int i = 0; i < 10; ++i) {
        assert(ints.pop_front() == i);
    }
    assert(ints.size() == 0);

    return 0;
}
