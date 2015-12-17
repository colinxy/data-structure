#include <iostream>
#include <cassert>
#include "stack.h"
using namespace std;

void stack_test() {
    Stack s;
    // push
    for (int i = 0; i < 10; ++i) {
        s.push(i);
    }
    // pop
    for (int i = 0; i < 10; ++i) {
        assert(s.pop() == 9-i);
    }
    // test exception
    Stack st(5);
    for (int i = 0; i < 5; ++i) {
        st.push(i);
    }
    try {
        st.push(5);
    } catch (overflow_error ex) {
        cout << ex.what() << endl;
        cout << "correctly throw overflow error" << endl;
    }
    for (int i = 0; i < 5; ++i) {
        st.pop();
    }
    try {
        st.pop();
    } catch (underflow_error ex) {
        cout << ex.what() << endl;
        cout << "correctly throw underflow error" << endl;
    }
}

int main() {
    stack_test();
    cout << "all test passed" << endl;

    return 0;
}