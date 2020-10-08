#include "Shape2D.h"
#include "MyHashTable.h"

#include <iostream>
#include <sstream>
#include <memory>

int main() {

    using namespace lab1;

    std::string simpleTest[] = {
            "Circle GREEN 01:01:2000 5 10 7\n",
            "Rectangle PURPLE 20:20:2020 0 0 1.41 3.14\n", // нет проверки корректности даты
            "Circle RED 02:02:2020 1 2 3"
    };

    std::stringstream ss;
    for (auto &s : simpleTest) {
        ss << s;
    }

    using pShape2D = std::shared_ptr<Shape2D>;
    MyHashTable<pShape2D> container;
    // Ввод
    for (pShape2D shape; ss >> shape; container.insert(shape));

    // Вывод на экран
    // Поскольку хеш считается от указателя, разные объекты, пусть и эквивалентные, могут попасть в разные bucket-ы
    container.printOnScreen();

    return 0;
}
