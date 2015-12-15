#include <iostream>
#include <cassert>
#include "singly_linked.h"


int main() {
    SinglyLinked<int> singly_linked;
    for (size_t i = 0; i < 10; i++) {
        singly_linked.push_back(i);
        assert(singly_linked.size() == i+1);
    }
    cout << singly_linked << endl;

    return 0;
}
