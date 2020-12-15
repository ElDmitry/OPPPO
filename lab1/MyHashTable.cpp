#include "MyHashTable.h"

#include <iostream>

template<class T>
MyHashTable<T>::MyHashTable()
        : m_bucketsCount(defaultBucketsCount)
        , m_buckets(new MyHashTable<T>::Bucket[m_bucketsCount]) {  }

template<class T>
MyHashTable<T>::MyHashTable(const MyHashTable<T> &other)
        : m_bucketsCount(other.m_bucketsCount)
        , m_buckets(new MyHashTable<T>::Bucket[other.m_bucketsCount]) {

    for (auto it = other.begin(); it != other.end(); ++it) {
        this->insert(*it);
    }
}

template<class T>
MyHashTable<T> &MyHashTable<T>::operator=(const MyHashTable<T> other) {
    m_elementsCount = other.m_elementsCount;
    m_bucketsCount  = other.m_bucketsCount;
    m_buckets = std::move(other.m_buckets);
}

template<class T>
bool MyHashTable<T>::insert(const T &value) {
    // Проверяем надо ли изменять размер хеш-таблицы
    ++m_elementsCount;
    if (loadFactor() > maxLoadFactor) {
        rehash(m_bucketsCount * 2);
    }
    --m_elementsCount;
    // Вычисляем bucket для нового элемента
    size_t bucketIdx = bucket(value);
    // Проверяем есть ли уже такой элемент
    auto it = m_buckets[bucketIdx].find(value);
    if (it == m_buckets[bucketIdx].end()) { // Если такого элемента еще нет
        m_buckets[bucketIdx].push_front(value);
        ++m_elementsCount;
        return true;
    }
    // Если элемент уже есть в хеш-таблице - возвращаем false.
    return false;
}

template<class T>
typename MyHashTable<T>::const_iterator MyHashTable<T>::find(const T &value) const {
    size_t bucketIdx = bucket(value);
    const_local_iterator localIt = m_buckets[bucketIdx].find(value);
    if (localIt != m_buckets[bucketIdx].end()) {
        return const_iterator(this, bucketIdx, localIt);
    }
    return end();
}

template<class T>
bool MyHashTable<T>::erase(const T &value) {
    size_t bucketIdx = bucket(value);
    if (m_buckets[bucketIdx].erase(value)) {
        --m_elementsCount;
        return true;
    }
    return false;
}

template<class T>
typename MyHashTable<T>::const_iterator MyHashTable<T>::begin() const {
    for (size_t bucket = 0; bucket < bucket_count(); ++bucket) {
        if (!m_buckets[bucket].empty()) {
            return const_iterator(this, bucket, begin(bucket));
        }
    }
    return end();
}

template<class T>
typename MyHashTable<T>::const_iterator MyHashTable<T>::end() const {
    return const_iterator(this, bucket_count());
}

template<class T>
size_t MyHashTable<T>::size() const {
    return m_elementsCount;
}

template<class T>
bool MyHashTable<T>::empty() const {
    return m_elementsCount == 0;
}

template<class T>
void MyHashTable<T>::printOnScreen() const {
    for (size_t bucket = 0; bucket != bucket_count(); ++bucket) {
        if (bucket_size(bucket) != 0) {
            auto it = begin(bucket);
            std::cout << "Bucket " << bucket << ":\n";
            for (size_t i = 0; i != bucket_size(bucket); ++i) {
                std::cout << "\t" << bucket << "." << i << " " << *it++ << "\n";
            }
        }
    }
}

template<class T>
typename MyHashTable<T>::const_local_iterator MyHashTable<T>::begin(size_t n) const {
    if (n < m_bucketsCount) {
        return m_buckets[n].begin();
    } else { // Если мы попытались обратиться к несуществующему bucket, то возвращаем итератор на end.
        return const_local_iterator();
    }
}

template<class T>
typename MyHashTable<T>::const_local_iterator MyHashTable<T>::end(size_t n) const {
    // Возвращаем итератор на конец списка элементов конкретного bucket.
    // В данныой реализации итераторы на конец разных списков неразличимы между собой.
    return const_local_iterator();
}

template<class T>
size_t MyHashTable<T>::bucket_size(size_t n) const {
    return (n < m_bucketsCount) ? m_buckets[n].size() : 0;
}

template<class T>
size_t MyHashTable<T>::bucket_count() const {
    return m_bucketsCount;
}

template<class T>
size_t MyHashTable<T>::bucket(const T &value) const {
    // Номер bucket-а определяем с помощью std::hash
    return std::hash<T>{}(value) % m_bucketsCount;
}

template<class T>
size_t MyHashTable<T>::bucket(const T &value, size_t count) const {
    return std::hash<T>{}(value) % count;
}

template<class T>
void MyHashTable<T>::clear() {
    m_buckets.reset(new MyHashTable<T>::Bucket[defaultBucketsCount]);
    m_buckets = defaultBucketsCount;
    m_elementsCount = 0;
}

template<class T>
void MyHashTable<T>::rehash(size_t count) {
    std::unique_ptr<MyHashTable<T>::Bucket[]> newBuckets(new MyHashTable<T>::Bucket[count]);
    for (auto it = begin(); it != end(); ++it) {
        newBuckets[bucket(*it, count)].push_front(*it);
    }
    m_buckets = std::move(newBuckets);
    m_bucketsCount = count;
}

template<class T>
double MyHashTable<T>::loadFactor() const {
    return static_cast<double>(m_elementsCount) / m_bucketsCount;
}

template<class T>
typename MyHashTable<T>::const_iterator
MyHashTable<T>::max_element(const std::function<bool(const_reference, const_reference)> &comp) const {
    auto max = begin();
    for (auto it = begin(); it != end(); ++it) {
        if (comp(*max, *it)) {
            max = it;
        }
    }
    return max;
}

template<class T>
const std::vector<typename MyHashTable<T>::const_iterator>
MyHashTable<T>::sort(const std::function<bool(const_reference, const_reference)> &comp) const {
    std::vector<const_iterator> vec(0);
    vec.reserve(m_elementsCount);

    for (auto it = begin(); it != end(); ++it) {
        vec.push_back(it);
    }

    size_t size = vec.size();
    bool sorted = (size == 0 || size == 1) ? true : false;
    while (!sorted) {
        sorted = true;
        for (size_t i = 1; i < size; ++i) {
            if (comp(*vec[i - 1], *vec[i])) {
                std::swap(vec[i - 1], vec[i]);
                sorted = false;
            }
        }
        --size;
    }

    return std::move(vec);
}

template<class T>
void MyHashTable<T>::erase_if(const std::function<bool(const_reference)> &pred) {
    for (auto it = begin(); it != end(); ) {
        if (pred(*it)) {
            auto tmp = it++;
            erase(*tmp);
        } else {
            ++it;
        }
    }
}


template<class T>
typename MyHashTable<T>::Bucket::const_iterator MyHashTable<T>::Bucket::find(const T &value) const {
    for (auto it = this->begin(); it != this->end(); ++it) {
        if (*it == value) return it;
    }
    return this->end();
}

template<class T>
void MyHashTable<T>::Bucket::push_front(const T &value) {
    m_begin = new Node(value, m_begin);
    ++m_size;
}

template<class T>
MyHashTable<T>::Bucket::~Bucket() {
    clear(); // удалем все узлы, созданные в динамической памяти
}

template<class T>
void MyHashTable<T>::Bucket::clear() {
    while (m_begin) {
        auto node = m_begin;
        m_begin = m_begin->next;
        delete node;
        --m_size;
    }
}

template<class T>
bool MyHashTable<T>::Bucket::erase(const T &value) {
    Node *node{m_begin}, *prev{nullptr};
    while (node) {
        if (node->value == value) {
            if (prev) { // Если у узла был предыдущий элемент
                prev->next = node->next;
            } else { // Иначе мы удаляем первый элемент
                m_begin = node->next;
            }
            delete node;
            --m_size;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

template<class T>
typename MyHashTable<T>::const_iterator & MyHashTable<T>::const_iterator::operator++() {
    // Имеет смысл инкрементировать только итераторы, привызанные к конкретному контейнеру, и не равные end.
    if ((m_hashTable != nullptr) && *this != m_hashTable->end()) {
        if (++m_localIter != m_hashTable->end(m_bucketIdx)) { // сначала смотрим этот же bucket
            return *this;
        } else { // иначе возвращаем первый реальный элемент другого bucket-а
            for (++m_bucketIdx; m_bucketIdx < m_hashTable->bucket_count(); ++m_bucketIdx) {
                if (!m_hashTable->m_buckets[m_bucketIdx].empty()) {
                    m_localIter = m_hashTable->begin(m_bucketIdx);
                    return *this;
                }
            }
        }
    }
    return *this = m_hashTable->end();
}

template<class T>
MyHashTable<T>::const_iterator::const_iterator(const MyHashTable<T> *hashTable, size_t bucketIndex,
                                               const MyHashTable::const_local_iterator &localIt)
    : m_hashTable(hashTable), m_bucketIdx(bucketIndex), m_localIter(localIt) {  }

template<class T>
bool MyHashTable<T>::const_iterator::operator==(const MyHashTable::const_iterator &other) {
    return (m_bucketIdx == other.m_bucketIdx) && (m_localIter == other.m_localIter);
}
