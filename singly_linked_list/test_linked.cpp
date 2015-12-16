#include <iostream>
#include <string>
#include <cassert>
#include "singly_linked.h"


int main() {
    SinglyLinked<int> singly_linked;
    for (size_t i = 0; i < 10; i++) {
        singly_linked.push_front(i);
        assert(singly_linked.size() == i+1);
    }
    cout << singly_linked << endl;

    /*******************
     ** accessor test **
     *******************/
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

    return 0;
}
