#ifndef SHAPE2D_H
#define SHAPE2D_H

#include "Date.h"

#include <iostream>
#include <memory>
#include <string>

namespace lab1
{

enum class Color {
    RED = 0,
    ORANGE,
    YELLOW,
    GREEN,
    LIGHT_BLUE,
    BLUE,
    PURPLE
};

std::istream & operator>>(std::istream &ist, Color &color);
std::ostream & operator<<(std::ostream &ost, const Color &color);


/// Родительский класс для плоских геометрических фигур
class Shape2D {
public:
    Shape2D() = default;
    explicit Shape2D(Color color);

    virtual ~Shape2D() = default;

    /// Считывает данные полей класса
    virtual std::istream & read(std::istream &ist);
    /// Записывает данные полей  класса
    virtual std::ostream & write(std::ostream &ost) const;

    virtual std::string typeName() const;

    /// Создает объект класса-наследника и возвращает указатель на родительский класс
    static Shape2D * createShape(const std::string &typeName);

private:
    Color m_color { Color::RED };
    Date m_lastEdit {};
};

std::istream & operator>>(std::istream &ist, std::shared_ptr<Shape2D> &shape);
std::ostream & operator<<(std::ostream &ost, const std::shared_ptr<Shape2D> &shape);

// Ввод-вывод полей объектов реализуем шаблонными функциями с переменным числом аргументов.
// Таким образом, получаем подержку ввода-вывода всех типов, для которых переопределены стандартные операторы ввода-вывода.
// Также теоретически можем написать специализацию для встроенных типов. Например: считать, что строки имеют вид "text".
//======================================================================================================================
// база рекурсии
inline std::ostream & serialize(std::ostream &ost) { return ost; }

/// Записывает параметры в выходной поток
template<typename T, typename... Args>
std::ostream & serialize(std::ostream &ost, const T &t, const Args&... args) {
    ost << " " << t;
    return serialize(ost, args...);
}

// база рекурсии
inline std::istream & deserialize(std::istream &ist) { return ist; }

/// Читаем параметры из входного потока
template<typename T, typename... Args>
std::istream & deserialize(std::istream &ist, T &t, Args&... args) {
    // возможно надо добавить обработку ошибок
    ist >> t;
    return deserialize(ist, args...);
}

} // namespace lab1

#endif // SHAPE2D_H
