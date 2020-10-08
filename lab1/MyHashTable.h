#ifndef MYHASHTABLE_H
#define MYHASHTABLE_H

#include <unordered_set>

namespace lab1
{

/// Контейнер на основе хеш-таблицы с разрешением коллизий методом цепочек
// В данной реализации MyHashTable - это шаблонный класс-обертка над std::unordered_set.
// Возможно, не самое удачное решение, поскольку в простейшем случае мы всего-лишь определяем
// прокси-интерфейс к интерфейсу стандартного контейнера.
// С другой стороны, подобное решение избавляет нас от внешней зависимости к реализации контейнера.
// Такой подход позволит добавлять контейнеру новый функционал в виде шаблонных методов класса.
//
// Также задачу можно было решить с помощью внешних шаблонных функций, но ввиду специфичного интерфейса
// std::unordered_set все равно пришлось бы писать специализацию функции. Например: функция печати на экран
// была бы должна выводить содержимое контейнера в виде иерархии.
template<class T>
class MyHashTable {
public:
    using iterator = typename std::unordered_set<T>::iterator;
    using const_iterator = typename std::unordered_set<T>::const_iterator;

    void printOnScreen() const;

    bool insert(const T &value);
    iterator find(const T &key);
    const_iterator find(const T &key) const;
    void erase(const T &value);

    size_t size() const;
    bool empty() const;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

private:
    std::unordered_set<T> m_hashTable;
};

#include "MyHashTable.cpp"

}
#endif // MYHASHTABLE_H
