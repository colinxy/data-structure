// hashmap.h


#ifndef HASHMAP_H_
#define HASHMAP_H_


#include <cstddef>

template <typename Key, typename Val>
class Map {
public:
      // constructor
    Map(int hash_func(const Key&));
      // copy constructor
    Map(const Map&);
      // assignment operator
    Map &operator= (const Map&);
      // destructor
    ~Map();

      // accessor
    bool        empty() const;
    std::size_t size() const;
    bool        contains(const Key&);
    const Val  &operator[] (const Key&) const;
    Val        &operator[] (const Key&);

      // mutator
    bool insert(const Key&, const Val&);
    bool erase(const Key&);

private:
    // map objects (T) to hash values (int)
    int m_hash_func(const Key&);
    // map hash values (int) to indexes (std::size_t)
    std::size_t m_slot_hash(int);

    /*  member variables  */
    std::size_t m_slots;
    std::size_t m_size;
};


template <typename Key, typename Val>
Map<Key,Val>::Map(int hash_func(const Key&) )
    : m_hash_func(hash_func) {
}


template <typename Key, typename Val>
Map<Key,Val>::Map(const Map &rhs) {
    // TODO : implement this
}


template <typename Key, typename Val>
Map<Key,Val> & Map<Key,Val>::operator= (const Map& rhs) {
    // TODO : implement this
    if (&rhs != this) {

    }

    return *this;
}


template <typename Key, typename Val>
Map<Key,Val>::~Map() {
    // TODO : implement this
}


#endif  // HASHMAP_H_
