#include "MyHashTable.h"

#include <iostream>

template<class T>
bool MyHashTable<T>::insert(const T &value) {
    return m_hashTable.insert(value).second;
}

template<class T>
typename MyHashTable<T>::iterator MyHashTable<T>::find(const T &key) {
    return m_hashTable.find(key);
}

template<class T>
typename MyHashTable<T>::const_iterator MyHashTable<T>::find(const T &key) const {
    return m_hashTable.find(key);
}

template<class T>
void MyHashTable<T>::erase(const T &value) {
    m_hashTable.erase(value);
}

template<class T>
typename MyHashTable<T>::iterator MyHashTable<T>::begin() {
    return m_hashTable.begin();
}

template<class T>
typename MyHashTable<T>::const_iterator MyHashTable<T>::begin() const {
    return m_hashTable.begin();
}

template<class T>
typename MyHashTable<T>::iterator MyHashTable<T>::end() {
    return m_hashTable.end();
}

template<class T>
typename MyHashTable<T>::const_iterator MyHashTable<T>::end() const {
    return m_hashTable.end();
}

template<class T>
size_t MyHashTable<T>::size() const {
    return m_hashTable.size();
}

template<class T>
bool MyHashTable<T>::empty() const {
    return m_hashTable.empty();
}

template<class T>
void MyHashTable<T>::printOnScreen() const {
    for (size_t bucket = 0; bucket != m_hashTable.bucket_count(); ++bucket) {
        if (m_hashTable.bucket_size(bucket) != 0) {
            auto it = m_hashTable.begin(bucket);
            std::cout << "Bucket " << bucket << ":\n";
            for (size_t i = 0; i != m_hashTable.bucket_size(bucket); ++i) {
                std::cout << "\t" << bucket << "." << i << " " << *it++ << "\n";
            }
        }
    }
}
