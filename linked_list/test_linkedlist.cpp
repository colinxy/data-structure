// test_linkedlist.cpp


#include "linkedlist.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;


void test_cons() {
    // default construct
    LinkedList<string> linked_strings1;
    for (size_t i = 0; i < 10; ++i) {
        string s("hello");
        s += i + '0';
        linked_strings1.push_back(s);
    }

    // copy constructor
    LinkedList<string> linked_strings2(linked_strings1);
    assert(linked_strings2.size() == 10);
    for (size_t i = 0; i < 10; ++i) {
        string s("hello");
        s += i + '0';
        assert(linked_strings2[i] == s);
    }

    // assignment operator
    LinkedList<string> list_assigned;
    list_assigned = linked_strings1;
    assert(!list_assigned.empty());
    assert(list_assigned.size() == 10);
    cout << list_assigned << endl;
    for (size_t i = 0; i < 10; ++i) {
        string s("hello");
        s += i + '0';
        assert(list_assigned.pop_front() == s);
    }
    assert(list_assigned.empty());
    cout << list_assigned << endl;
}


void test_accessor() {
    // empty, size
    LinkedList<int> ints;
    assert(ints.empty());
    assert(ints.size() == 0);

    // push_back
    for (int i = 0; i < 10; ++i) {
        ints.push_back(i);
        assert(ints.size() == i+1);
    }
    assert(ints.size() == 10);
    // front, back
    assert(ints.front() == 0);
    assert(ints.back()  == 9);

    // operator[]
    for (int i = 0; i < 10; ++i) {
        int current = ints[i];
        assert(current == i);
    }

    // pop_front, pop_back
    for (int i = 0; i < 5; ++i) {
        assert(ints.pop_front() == i);
        assert(ints.pop_back() == 9-i);
    }
    assert(ints.size() == 0);
    cout << ints << endl;
    // should be []

    LinkedList<int> integers;
    for (int i = 0; i < 10; ++i) {
        integers.push_back(i*i);
        assert(integers[integers.size()-1] == i*i);
        assert(integers.back() == i*i);
    }

    cout << integers << endl;
    // should be 0 1 4 9 16 25 36 49 64 81

    assert(integers[3] == 9);
    integers[3] = 34;
    assert(integers[3] == 34);

    integers.front() = 62;
    assert(integers.front() == 62);
    integers.back() = 38;
    assert(integers.back() == 38);
}


void test_mutator() {
    LinkedList<int> ints;
    assert(ints.size() == 0);
    assert(ints.empty());

    // push_back
    for (int i = 0; i < 10; ++i) {
        ints.push_back(i);
        assert(ints.size() == i+1);
        assert(ints.back() == i);
        assert(ints[ints.size()-1] == i);
    }
    assert(!ints.empty());

    // pop_front, pop_back
    for (int i = 0; i < 5; ++i) {
        assert(ints.pop_front() == i);
        assert(ints.pop_back() == 9-i);
        assert(ints.size() == 8-2*i);
    }

    LinkedList<int> ints2(ints);
    assert(ints2.empty());
    assert(ints2.size() == 0);

    // insert
    for (int i = 0; i < 10; ++i) {
        ints2.insert(i*i, i);
        assert(ints2.back() == i*i);
        assert(ints2[ints2.size()-1] == i*i);
    }

    // pop
    // ints2: 0 1 4 9 16 25 36 49 64 81
    assert(ints2.pop(1) == 1);
    assert(ints2.pop(2) == 9);
    assert(ints2.pop(3) == 25);
    assert(ints2.pop(4) == 49);
    assert(ints2.pop(5) == 81);

    assert(ints2.size() == 5);
    // ints2: 0 4 16 36 64
    for (int i = 0; i < 5; ++i) {
        assert(ints2.pop(0) == 4*i*i);
    }
    assert(ints2.empty());
}


int main() {
    // LinkedList();
    LinkedList<int> ints;
    assert(ints.empty());
    assert(ints.size() == 0);

    for (int i = 0; i < 10; ++i) {
        ints.push_back(i);
        assert(ints.back() == i);
    }
    cout << ints << endl;
    // should be 0 1 2 3 4 5 6 7 8 9

    test_cons();
    test_accessor();
    test_mutator();

    return 0;
}
