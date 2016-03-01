// test_tree.cpp


#include "red_black_tree.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>
using namespace std;


// test accessor, mutator
void test_acc_mut() {
    RedBlackTree<int> rbt;

    /*
     * insertion
     */
    assert(rbt.empty());
    assert(rbt.size() == 0);

    for (int i = 0; i < 10; i += 2) {
        assert(rbt.insert(i));
    }
    assert(rbt.size() == 5);
    for (int i = 1; i < 10; i += 2) {
        assert(rbt.insert(i));
    }
    assert(rbt.size() == 10);

    assert(rbt.min() == 0);
    assert(rbt.max() == 9);
    for (int i = 0; i < 10; ++i) {
        assert(rbt.contains(i));
    }
    vector<int> vec;
    rbt.toVector(vec);
    assert(vec.size() == 10);
    for (int i = 0; i < 10; ++i) {
        assert(vec[i] == i);
    }

    /*
     * deletion
     */
    for (int i = 0; i < 10; ++i) {
        assert(rbt.erase(i));
    }
    assert(rbt.empty());
    assert(!rbt.erase(0));
    // insertion and deletion
    assert(rbt.insert(10));  // 10
    assert(!rbt.erase(3));  // 10
    assert(rbt.insert(3));  // 3 10
    assert(!rbt.erase(7));  // 10 3
    assert(rbt.insert(5));  // 3 5 10
    assert(rbt.erase(3));  // 5 10
    assert(rbt.erase(10));  // 5
    assert(rbt.size() == 1);  // 5
    assert(rbt.erase(5));  //
    assert(rbt.empty());  //
}


// test copy constructor, assignment operator
void test_cons_copy() {
    // trivial copy test
    RedBlackTree<int> rbt;
    assert(rbt.empty());

    RedBlackTree<int> rbt_copied(rbt);
    assert(rbt_copied.empty());

    for (int i = 0; i < 10; ++i) {
        rbt.insert(i);
    }
    assert(rbt.size() == 10);
    assert(rbt_copied.size() == 0);

    // copy test
    RedBlackTree<int> rbtree_copied(rbt);
    assert(rbtree_copied.size() == 10);
    for (int i = 0; i < 10; ++i) {
        assert(rbtree_copied.contains(i));
    }
    assert(rbtree_copied.erase(9));
    for (int i = 0; i < 8; ++i) {
        assert(rbtree_copied.erase(i));
    }

    // assignment test
    RedBlackTree<int> rbtree_assigned;
    rbtree_assigned = rbt;
    assert(rbtree_assigned.size() == 10);
    for (int i = 0; i < 10; ++i) {
        assert(rbtree_assigned.contains(i));
    }
}


// randomized test
void test_random() {
    srand(time(NULL));

    const int SIZE = 300000;

    vector<int> nums_vec;
    RedBlackTree<int> nums_tree;

    for (int i = 0; i < SIZE; ++i) {
        nums_tree.insert(rand());
    }

    int size = nums_tree.size();

    nums_tree.toVector(nums_vec);
    assert(nums_tree.min() == nums_vec[0]);
    assert(nums_tree.max() == nums_vec[size-1]);
    for (int i = 1; i < size; ++i) {
        assert(nums_vec[i] >= nums_vec[i-1]);
    }

    // for (int i = 0; i < size; ++i) {
    //     assert(nums_tree.erase(nums_vec[i]));
    // }
    // assert(nums_tree.empty());

    // assignment
    RedBlackTree<int> nums_tree_assigned;
    nums_tree_assigned = nums_tree;
    vector<int> nums_vec_assigned;
    nums_tree_assigned.toVector(nums_vec_assigned);
    assert(nums_tree_assigned.min() == nums_vec_assigned[0]);
    assert(nums_tree_assigned.max() == nums_vec_assigned[size-1]);
    assert(nums_tree_assigned.size() == size);
    for (int i = 0; i < size; ++i) {
        assert(nums_vec[i] == nums_vec_assigned[i]);
    }
    for (int i = 0; i < size; ++i) {
        assert(nums_tree_assigned.erase(nums_vec_assigned[i]));
    }
    assert(nums_tree_assigned.empty());

    // copy construct
    RedBlackTree<int> nums_tree_copied(nums_tree);
    vector<int> nums_vec_copied;
    nums_tree_copied.toVector(nums_vec_copied);
    assert(nums_tree_copied.min() == nums_vec_copied[0]);
    assert(nums_tree_copied.max() == nums_vec_copied[size-1]);
    assert(nums_tree_copied.size() == size);
    for (int i = 0; i < size; ++i) {
        assert(nums_vec[i] == nums_vec_copied[i]);
    }

    for (int i = 0; i < size; ++i) {
        assert(nums_tree_copied.erase(nums_vec_copied[i]));
    }
    assert(nums_tree_copied.empty());
}


int main() {

    test_acc_mut();

    test_cons_copy();

    test_random();

    cout << "all tests passed" << endl;
    return 0;
}
