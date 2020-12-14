#include "Shape2D.h"
#include "MyHashTable.h"

#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>

int main() {

    using namespace lab1;

    std::string simpleTest[] = {
            "Circle GREEN 01:01:2000 SOLID 5 10 7\n",
            "Rectangle PURPLE 20:20:2020 BLANK 0 0 1.41 3.14\n", // нет проверки корректности даты
            "Circle RED 02:02:2020 DASHED 1 2 3",
            "Triangle ORANGE 12:12:2020 DOTTED 0.1 1.5 4.8 3.2 0.1 5"
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
    std::cout << "The number of elements in the hash table: " << container.size() << "\n";
    container.printOnScreen();

    // Выводим фигуру с максимальной площадью
    auto maxIt = container.max_element([](const pShape2D &a, const pShape2D &b) {
                                            return a->area() < b->area(); });
    std::cout << "Max element: " << *maxIt << "\nMax area: " << (*maxIt)->area() << "\n";

    return 0;
}
