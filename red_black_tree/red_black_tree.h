// red_black_tree.h


#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H


#include <cstddef>
#include <vector>

template <typename T>
class RedBlackTree {
public:
      // constructor
    RedBlackTree();
      // copy constructor
    RedBlackTree(const RedBlackTree<T> &);
      // assignment operator
    RedBlackTree &operator=(const RedBlackTree &);
      // destructor
    ~RedBlackTree();

      // accessor
    bool        empty()   const;
    std::size_t size()    const;
    bool        hasElem() const;
    const T&    max()     const;
    const T&    min()     const;

      // mutator
    bool insert (const T& elem);
    bool pop    (const T& elem);

      // traversal
    void toVector(std::vector<T> &) const;

private:
    struct Node {
        T    value;
        Node *left;
        Node *right;

        bool black;

        Node(const T& val, bool is_black = true)
            : value(val)
            , left(nullptr)
            , right(nullptr)
            , black(is_black) {}
    }

      // helper function
    void navigate(Node**, const T&) const;
    void delNodes(Node*);
    void traverse(Node*, std::vector<T> &) const;

    Node       *m_root;
    std::size_t m_size;
};


template <typename T>
RedBlackTree<T>::RedBlackTree()
    : m_root(nullptr)
    , msize(0) {
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
bool RedBlackTree<T>::hasElem(const T& elem) const {
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

    navigate(current, elem);
    if ((*current)->value == elem) {
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

    // element is a leaf
    if ((*toDel)->left == nullptr &&
        (*toDel)->right == nullptr) {

        delete *toDel;
        *toDel = nullptr;

        --m_size;
        return true;
    }

    // try to find its successor

    // successor does not exist
    if ((*toDel)->right == nullptr) {
        Node *leftChild ((*toDel)->left);
        delete *toDel;
        *toDel = leftChild;
    }

    else {
        Node **successor = (*toDel)->right;

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
void RedBlackTree::toVector(std::vector<T> &vec) const {
    traverse(m_root, vec);
}


/*
 * private helper function
 */

template <typename T>
void RedBlackTree<T>::navigate(Node** &current,
                               const T &elem) const {
    while (*current != nullptr) {
        if (elem == (*current)->value)
            break;
        else if (elem < (*current)->value)
            current = &((*current)->left);
        else /* elem > (*current)->value */
            current = &((*current)->right);
    }
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
void RedBlackTree<T>::traverse(Node* root,
                               std::vector<T> &vec) const {
    if (root == nullptr)
        return;

    traverse(root->left, vec);
    vec.push_back(root->value);
    traverse(root->right, vec);
}


#endif  // RED_BLACK_TREE_H
