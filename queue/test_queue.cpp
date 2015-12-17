#include <iostream>
#include <cassert>
#include "queue.h"
using namespace std;

void queue_test() {
    Queue q(10);

    // push_back
    for (int i = 0; i < 10; ++i) {
        q.push_back(i);
    }
    // pop_front
    for (int i = 0; i < 10; ++i) {
        assert(q.pop_front() == i);
    }
    // empty
    assert(q.empty());
    // underflow exception
    try {
        q.pop_front();
    } catch (underflow_error ex) {
        cout << ex.what() << endl;
        cout << "correctly throw underflow error" << endl;
    }
    // overflow exception
    Queue queue(5);
    for (int i = 0; i < 5; ++i) {
        queue.push_back(i);
    }
    try {
        queue.push_back(10);
    } catch(overflow_error ex) {
        cout << ex.what() << endl;
        cout << "correctly throw overflow error" << endl;
    }
}

int main() {
    queue_test();
    cout << "all tests passed" << endl;

    return 0;
}
