#include "Rectangle.h"

#include <utility>

namespace lab1
{

Rectangle::Rectangle() : Shape2D()
{
}

Rectangle::Rectangle(const Color &color, Point topLeft, Point bottomRight)
    : Shape2D(color), m_topLeft(std::move(topLeft)), m_bottomRight(std::move(bottomRight))
{
}

std::istream &Rectangle::read(std::istream &ist) {
    // Считываем данные родительского класса
    Shape2D::read(ist);
    // Считываем собственные данные
    return deserialize(ist, m_topLeft.first, m_topLeft.second,
                       m_bottomRight.first, m_bottomRight.second);
}

std::ostream &Rectangle::write(std::ostream &ost) const {
    // Записываем данные родительского класса
    Shape2D::write(ost);
    // Записываем собственные данные
    return serialize(ost, m_topLeft.first, m_topLeft.second,
                     m_bottomRight.first, m_bottomRight.second);
}

std::string Rectangle::typeName() const {
    return std::move(std::string("Rectangle"));
}

double Rectangle::area() const {
    return abs(m_bottomRight.first - m_topLeft.first) * abs(m_topLeft.second - m_bottomRight.second);
}


std::istream & operator>>(std::istream &ist, Rectangle &rectangle) {
    std::string typeName;
    if (ist >> typeName && typeName == rectangle.typeName()) {
        rectangle.read(ist);
    }
    return ist;
}

std::ostream & operator<<(std::ostream &ost, const Rectangle &rectangle) {
    ost << rectangle.typeName();
    rectangle.write(ost);
    return ost;
}

} // namespace lab1
