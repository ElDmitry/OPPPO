#ifndef SHAPE2D_H
#define SHAPE2D_H

#include "Shape2DTypes.h"

#include <iostream>
#include <memory>
#include <string>

namespace lab1
{

/// Интерфейс для плоских геометрических фигур
class Shape2D {
public:
    Shape2D();
    explicit Shape2D(Color color);

    virtual ~Shape2D();

    /// Считывает данные полей класса
    virtual std::istream & read(std::istream &ist);
    /// Записывает данные полей  класса
    virtual std::ostream & write(std::ostream &ost) const;

    virtual std::string typeName() const;

    /// Создает объект класса-наследника и возвращает указатель на родительский класс
    static Shape2D * createShape(const std::string &typeName);

private:
    Color m_color { Color::RED };
    Date m_lastEdit;
};

std::istream & operator>>(std::istream &ist, std::shared_ptr<Shape2D> &shape);
std::ostream & operator<<(std::ostream &ost, const std::shared_ptr<Shape2D> &shape);

} // namespace lab1

#endif // SHAPE2D_H
