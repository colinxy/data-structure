// test_linked.cpp


#include "singly_linked.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;


void test_cons() {
    /*
     * test constructor
     *      destructor
     *      assignment operator
     *      destructor
     */

    SinglyLinked<int> list_int1;

    for (size_t i = 0; i < 5; ++i)
        list_int1.push_front(i);

    SinglyLinked<int> list_int2(list_int1);
    SinglyLinked<int> list_int3;
    list_int3 = list_int1;

    // self assign should work
    list_int1 = list_int1;

    cout << list_int1 << endl;
    cout << list_int2 << endl;
    cout << list_int3 << endl;
    // should be the same
    // 4 3 2 1 0
}


void test_accessor() {
    /*******************
     ** accessor test **
     *******************/

    SinglyLinked<int> singly_linked;

    assert(singly_linked.empty());
    assert(singly_linked.size() == 0);

    for (size_t i = 0; i < 10; i++) {
        singly_linked.push_front(i);
        assert(singly_linked.size() == i+1);
    }

    // empty
    assert(!singly_linked.empty());
    // size
    assert(singly_linked.size() == 10);
    // front
    assert(singly_linked.front() == 9);
    singly_linked.front() = 100;
    assert(singly_linked.front() == 100);
    // operator[]
    assert(singly_linked[0] == 100);
    assert(singly_linked[5] == 4);
    singly_linked[5] = 1000;
    assert(singly_linked[5] == 1000);
    cout << singly_linked << endl;
    // should be 100 8 7 6 5 1000 3 2 1 0
}


void test_mutator() {
    /******************
     ** mutator test **
     ******************/

    // push_front
    SinglyLinked<string> linked_str;
    linked_str.push_front("world");
    assert(linked_str[0] == "world");
    assert(linked_str.size() == 1);
    linked_str.push_front("hello ");
    assert(linked_str[0] == "hello ");
    assert(linked_str[1] == "world");
    assert(linked_str.size() == 2);

    // insert
    for (int i = 0; i < 3; ++i) {
        linked_str.insert(i+2, "foo");
        assert(linked_str[i+2] == "foo");
    }
    linked_str.insert(0, "bar");
    assert(linked_str[0] == "bar");
    assert(linked_str.size() == 6);
    cout << linked_str << endl;
    // should be "bar" "hello " "world" "foo" "foo" "foo"

    // pop_front
    SinglyLinked<int> singly_linked;
    for (size_t i = 0; i < 10; i++) {
        singly_linked.push_front(i);
        assert(singly_linked.size() == i+1);
    }
    assert(singly_linked.front() == 9);
    assert(singly_linked.pop_front() == 9);
    assert(singly_linked.front() == 8);
    assert(singly_linked.size() == 9);
    assert(singly_linked.pop_front() == 8);
    assert(singly_linked.size() == 8);

    // pop
    // singly_linked is now 7 6 5 4 3 2 1 0
    assert(singly_linked.pop(1) == 6);
    assert(singly_linked.size() == 7);
    assert(singly_linked.pop(0) == 7);
    assert(singly_linked.size() == 6);
    assert(singly_linked.pop(singly_linked.size()-1) == 0);
    // singly_linked is now 5 4 3 2 1
    assert(singly_linked.pop(4));
    assert(singly_linked.pop(2));
    cout << singly_linked << endl;
    // should output [5, 4, 2]
}


int main() {
    SinglyLinked<int> singly_linked;
    for (size_t i = 0; i < 10; i++) {
        singly_linked.push_front(i);
        assert(singly_linked.size() == i+1);
    }
    cout << singly_linked << endl;
    // should be 9 8 7 6 5 4 3 2 1

    test_cons();

    test_accessor();

    test_mutator();

    /*******************
     ** iterator test **
     *******************/
    // SinglyLinked<int> other(singly_linked);
    // cout << other << endl;

    return 0;
}
