// red_black_tree.h


#include <iostream>
using namespace std;


template <class T>
class RedBlackTree {
public:
      // constructor
    RedBlackTree();
      // copy constructor
    RedBlackTree(const RedBlackTree<T> &);
      // destructor
    ~RedBlackTree();

      // accessor
    bool     empty()   const;
    size_t   size()    const;
    bool     hasElem() const;
    const T& max()     const;
    const T& min()     const;

      // mutator
    bool insert (const T& elem);
    bool pop    (const T& elem);

private:
    struct Node {
        T    value;
        Node *left;
        Node *right;

        Node(const T& val) : value(val)
                           , left(nullptr)
                           , right(nullptr) {}
    }

      // helper function
    void navigate(Node**, const T&) const;
    void delNodes(Node*);

    Node   *m_root;
    size_t m_size;
};


template <class T>
RedBlackTree<T>::RedBlackTree() : m_root(nullptr) {
}


template <class T>
RedBlackTree<T>::~RedBlackTree() {
    delNodes(m_root);
}


template <class T>
bool RedBlackTree<T>::empty() const {
    return m_root == nullptr;
}


template <class T>
size_t RedBlackTree<T>::size() const {
    return m_size;
}


template <class T>
bool RedBlackTree<T>::hasElem(const T& elem) const {
    Node *current (m_root);

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


template <class T>
bool RedBlackTree<T>::insert(const T& elem) {
    Node *node = new Node(elem);
    if (node == nullptr) return false;

    Node **current (&m_root);

    while (*current != nullptr) {
        if (elem < (*current)->value) {
            current = &((*current)->left);
        } else /* elem >= (*current)->value */ {
            current = &((*current)->right);
        }
    }

    *current = node;
    ++m_size;

    return true;
}


template <class T>
bool RedBlackTree<T>::pop(const T& elem) {

    Node **toDel (&m_root);

    navigate(toDel, elem);

    // pop unsuccessful, element not found
    if (*toDel == nullptr)
        return false;

    Node **toSwap (toDel);

    if ((*toSwap)->left != nullptr) {
        // first find biggest element in left node, if possible
        while ((*toSwap)->right != nullptr) {
            toSwap = &((*toSwap)->right);
        }
    } else if ((*toSwap)->right != nullptr) {
        // then find smallest element in right node, if possible
        while ((*toSwap)->left != nullptr) {
            toSwap = &((*toSwap)->left);
        }
    } else /* element is a leaf */ {
        delete *toDel;
        *toDel = nullptr;
        return true;
    }

    *toSwap->left  = (*toDel)->left;
    *toSwap->right = (*toDel)->right;

    delete *toDel;
    *toDel = *toSwap;
    *toSwap = nullptr;

    return true;
}


template <class T>
void RedBlackTree<T>::navigate(Node** &current, const T& elem) const {
    while (*current != nullptr) {
        if (elem == (*current)->value) {
            break;
        } else if (elem < (*current)->value) {
            current = &((*current)->left);
        } else /* elem > (*toDel)->value */ {
            current = &((*current)->right);
        }
    }
}


template <class T>
void RedBlackTree<T>::delNodes(Node *root) {
    if (root == nullptr)
        return;

    delNodes(root->left);
    delNodes(root->right);

    delete root;
}
