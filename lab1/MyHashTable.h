#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#include <memory>

namespace lab1
{

/// Контейнер на основе хеш-таблицы с разрешением коллизий методом цепочек
template<class T>
class MyHashTable {
public:
    using const_value_type = T const;
    using const_pointer    = T const *;
    using const_reference  = T const &;

    static constexpr size_t defaultBucketsCount = 8;
    static constexpr double maxLoadFactor = 0.75;

    MyHashTable();
    MyHashTable(const MyHashTable<T> &other);
    MyHashTable<T> & operator=(const MyHashTable<T> other);

private: // Определяем внутренние структуры данных =====================================================================

    struct Bucket { // Вложенный контейнер, для хранения простого списка элементов

        Bucket() = default;
        ~Bucket();

        struct Node {
            Node() = delete;
            Node(const Node &) = delete;
            Node & operator=(const Node &) = delete;

            explicit Node(const T &value, Node *next = nullptr)
                        : value(value), next(next) {}

            const_value_type value {};
            Node *next;
        };

        // Итератор для вложенного контейнера
        struct const_iterator
                :  std::iterator<std::forward_iterator_tag,
                                 const_value_type,
                                 std::ptrdiff_t,
                                 const_pointer,
                                 const_reference> {
            const_iterator() = default;
            const_iterator(const const_iterator &) = default;
            const_iterator & operator=(const const_iterator &) = default;

            explicit const_iterator(const Node *ptr) : m_ptr(ptr) {}

            const_iterator & operator++() { m_ptr = m_ptr->next; return *this; }
            const_iterator operator++(int) { auto copy = *this; operator++(); return copy; }
            const_reference operator*() const { return m_ptr->value; }
            const_pointer operator->() const { return &(m_ptr->value); }
            bool operator==(const const_iterator &other) { return m_ptr == other.m_ptr; }
            bool operator!=(const const_iterator &other) { return m_ptr != other.m_ptr; }

        private:
            const Node *m_ptr {nullptr};
        };

        bool empty() const { return m_size == 0; }
        size_t size() const { return m_size; }
        void clear();

        const_iterator begin() const { return const_iterator(m_begin); }
        const_iterator end() const { return const_iterator(); }

        const_iterator find(const T& value) const;
        void push_front(const T& value);
        bool erase(const T &value);

    private:
        size_t m_size {0};
        Node *m_begin {nullptr};
    };

//======================================================================================================================

// Интерфейс для внутренних структур данных ============================================================================
public:
    using const_local_iterator = typename Bucket::const_iterator;

    // Возвращает локальный итератор для определенного bucket
    const_local_iterator begin(size_t n) const;
    const_local_iterator end(size_t n) const;

    size_t bucket_size(size_t n) const;
    size_t bucket_count() const;

    // Возвращает номер bucket-а, куда будет записано значение
    size_t bucket(const T &value) const;

private:
    size_t bucket(const T &value, size_t count) const;

//======================================================================================================================
// Интерфейс хеш-таблицы ===============================================================================================
public:
    // Итератор, обеспечивающий итерации в пределах всей хеш-таблицы
    struct const_iterator
            : std::iterator<std::forward_iterator_tag,
                            const_value_type,
                            std::ptrdiff_t,
                            const_pointer,
                            const_reference> {
        const_iterator() = default;
        const_iterator(const const_iterator &) = default;
        const_iterator & operator=(const const_iterator &) = default;

        friend MyHashTable;

        const_iterator & operator++();
        const_iterator operator++(int) { auto copy = *this; operator++(); return copy; }
        const_reference operator*() const { return *m_localIter; }
        const_local_iterator & operator->() const { return m_localIter; }
        bool operator==(const const_iterator &other);
        bool operator!=(const const_iterator &other) { return !operator==(other); }

    private:
        explicit const_iterator(const MyHashTable<T> *hashTable,
                                size_t bucketIndex,
                                const const_local_iterator &localIt = const_local_iterator());

        const MyHashTable<T> *m_hashTable{nullptr};
        size_t m_bucketIdx{0};
        const_local_iterator m_localIter{};// Bucket::end()
    };

    const_iterator begin() const;
    const_iterator end() const;

    void printOnScreen() const;

    size_t size() const;
    bool empty() const;
    double loadFactor() const;

    bool insert(const T &value);
    const_iterator find(const T &value) const;
    bool erase(const T &value);
    void clear();
    void rehash(size_t count);

//======================================================================================================================
// Приватные поля хеш-таблицы
private:
    size_t m_elementsCount{0};
    size_t m_bucketsCount{defaultBucketsCount};
    // Контейнеры для узлов хеш-таблицы хранятся в обычном массиве
    std::unique_ptr<Bucket[]> m_buckets;
};

#include "MyHashTable.cpp"

}
#endif // MYHASHTABLE_H
