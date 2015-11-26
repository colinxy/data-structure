Linked List
===========

This project implements a generic doubly linked list using template.

This implementation of linked list tries to make itself usable and
at the same time learn from the philosophy of the STL container list.
Therefore, it tries to implement the interface of container list
specified in the standard template library as much as possible.

The following interfaces from the STL container list are implemented:
- bool empty() const;
- size_type size() const;
- reference front();
- reference back();
- void push_back (const value_type& val);
- void push_front (const value_type& val);
- void pop_back();
- void pop_front();
