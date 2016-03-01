// red_black_tree.h


#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H


#include <cstddef>
#include <vector>
#include <utility>

template <typename T>
class RedBlackTree {
public:
      // constructor
    RedBlackTree();
      // copy constructor
    RedBlackTree(const RedBlackTree<T> &);
      // assignment operator
    RedBlackTree &operator=(const RedBlackTree<T> &);
      // destructor
    ~RedBlackTree();

      // accessor
    bool        empty()            const;
    std::size_t size()             const;
    bool        contains(const T&) const;
    const T&    max()              const;
    const T&    min()              const;

      // mutator
    bool insert (const T& elem);
    bool pop    (const T& elem);

      // traversal
    void toVector(std::vector<T> &) const;

private:
    enum Color {RED, BLACK};

    struct Node {
        const T value;
        Node   *left;
        Node   *right;

        Color color;

        Node(const T& val, Color c = BLACK)
            : value(val)
            , left(nullptr)
            , right(nullptr)
            , color(c) {}
    };

      // navigate to the node with given value
      // return whether the given node with given value exist
    bool navigate(Node** &, const T&) const;
      // copying subtree
    Node *copyNodes(const Node*);
      // deleting subtree
    void delNodes(Node*);
      // in-order traversal
    void traverse(const Node*, std::vector<T> &) const;

    Node       *m_root;
    std::size_t m_size;
};


template <typename T>
RedBlackTree<T>::RedBlackTree()
    : m_root(nullptr)
    , m_size(0) {
}


template <typename T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree<T> &rhs)
    : m_size(rhs.m_size) {

    m_root = copyNodes(rhs.m_root);
}


template <typename T>
RedBlackTree<T> & RedBlackTree<T>::operator= (const RedBlackTree<T> &rhs) {
    if (&rhs != this) {
        RedBlackTree tmp(rhs);
        std::swap(this->m_root, tmp.m_root);
        std::swap(this->m_size, tmp.m_size);
    }

    return *this;
}


template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    delNodes(m_root);
}


template <typename T>
bool RedBlackTree<T>::empty() const {
    return m_root == nullptr;
}


template <typename T>
std::size_t RedBlackTree<T>::size() const {
    return m_size;
}


template <typename T>
bool RedBlackTree<T>::contains(const T& elem) const {
    Node *current = m_root;

    while (current != nullptr) {
        if (elem == current->value) {
            return true;
        } else if (elem < current->value) {
            current = current->left;
        } else /* elem > current->value */ {
            current = current->right;
        }
    }

    return false;
}


/*
 * Both min and max functions
 * crashes when applied to an empty tree.
 *
 * It is also meaningless to return a value
 * of type T, so it is decided to let the
 * program produce the error
 */

template <typename T>
const T& RedBlackTree<T>::min() const {
    Node *minimum = m_root;

    while (minimum->left != nullptr) {
        minimum = minimum->left;
    }

    return minimum->value;
}


template <typename T>
const T& RedBlackTree<T>::max() const {
    Node *maximum = m_root;

    while (maximum->right != nullptr) {
        maximum = maximum->right;
    }

    return maximum->value;
}


template <typename T>
bool RedBlackTree<T>::insert(const T& elem) {
    Node **current = &m_root;

    if (navigate(current, elem)) {
        return false;
    }

    *current = new Node(elem);
    ++m_size;

    // TODO: maintain red_black_tree invariant

    return true;
}


template <typename T>
bool RedBlackTree<T>::pop(const T& elem) {

    Node **toDel = &m_root;

    navigate(toDel, elem);

    // pop unsuccessful, element not found
    if (*toDel == nullptr)
        return false;

    // try to find its successor

    // successor does not exist
    if ((*toDel)->right == nullptr) {
        Node *leftChild ((*toDel)->left);
        delete *toDel;
        *toDel = leftChild;
    }

    else {
        Node **successor = &((*toDel)->right);

        while ((*successor)->left != nullptr) {
            successor = &((*successor)->left);
        }

        // connect right child of successor to
        // successor's parent
        Node *suc = *successor;
        *successor = suc->right;

        suc->left = (*toDel)->left;
        suc->right = (*toDel)->right;

        delete *toDel;
        *toDel = suc;
    }

    // TODO: maintain red_black_tree invariant

    --m_size;
    return true;
}


/*
 * The content of the tree is only copied once
 *
 * Content of the tree will be appended to the
 * back of the vector
 */

template <typename T>
void RedBlackTree<T>::toVector(std::vector<T> &vec) const {
    traverse(m_root, vec);
}


/*
 * private helper functions
 */

// navigate to the node that contains elem
template <typename T>
bool RedBlackTree<T>::navigate(Node** &current,
                               const T &elem) const {
    while (*current != nullptr) {
        if (elem == (*current)->value)
            return true;
        else if (elem < (*current)->value)
            current = &((*current)->left);
        else /* elem > (*current)->value */
            current = &((*current)->right);
    }

    return false;
}


template <typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::copyNodes(const Node* src) {
    if (src == nullptr)
        return nullptr;

    Node *copied  = new Node(src->value, src->color);
    copied->left  = copyNodes(src->left);
    copied->right = copyNodes(src->right);

    return copied;
}


template <typename T>
void RedBlackTree<T>::delNodes(Node *root) {
    if (root == nullptr)
        return;

    delNodes(root->left);
    delNodes(root->right);

    delete root;
}


// in-order traversal
template <typename T>
void RedBlackTree<T>::traverse(const Node* root,
                               std::vector<T> &vec) const {
    if (root == nullptr)
        return;

    traverse(root->left, vec);
    vec.push_back(root->value);
    traverse(root->right, vec);
}


#endif  // RED_BLACK_TREE_H
