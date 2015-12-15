#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include "linkedlist.h"
using namespace std;

// TODO: test all interface of linkedlist

int main() {
    // LinkedList();
    LinkedList<int> ints;
    assert(ints.empty());
    assert(ints.size() == 0);
    try {
        ints.get_front();
    } catch (out_of_range) {
        ;
    }
    try {
        ints.get_back();
    } catch (out_of_range) {
        ;
    }
    cout << "LinkedList()" << endl
         << "default constructor:\nok\n" << endl;

    /*
    // LinkedList(const LinkedList<T>& list);
    LinkedList<string> linked_strings1;
    for (size_t i = 0; i < 10; ++i) {
        string s("hello");
        s += i + '0';
        linked_strings1.push_back(s);
    }
    LinkedList<string> linked_strings2(linked_strings1);
    assert(linked_strings2.size() == 10);
    for (size_t i = 0; i < 10; ++i) {
        string s("hello");
        s += i + '0';
        assert(linked_strings2.get(i) == s);
    }
    cout << "LinkedList(const LinkedList<T>& list)" << endl
         << "constructor from another linked list:\nok\n" << endl;

    // LinkedList(const initializer_list<T>& elems);
    LinkedList<int> from_initlist({0, 1, 2, 3, 4});
    assert(!from_initlist.empty());
    assert(from_initlist.size() == 5);
    for (size_t i = 0; i < 5; ++i) {
        assert(from_initlist.pop_front() == i);
    }
    cout << "LinkedList(const initializer_list<T>& elems)" << endl
         << "constructor from another initializer list:\nok\n" << endl;
    */

    // for (int i = 0; i < 10; ++i) {
    //     ints.push_back(i);
    // }
    // assert(ints.size() == 10);
    // for (int i = 0; i < 10; ++i) {
    //     int current = ints.get(i);
    //     cout << current << endl;
    //     assert(current == i);
    // }
    // for (int i = 0; i < 10; ++i) {
    //     assert(ints.pop_front() == i);
    // }
    // assert(ints.size() == 0);
    // try {
    //     ints.get(3);
    // } catch(out_of_range) {
    //     cout << "throw out_of_range exception correctly" << endl;
    // }

    cout << "all test passed" << endl;

    return 0;
}
