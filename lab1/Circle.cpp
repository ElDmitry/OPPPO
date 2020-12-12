#include "Circle.h"

#include <utility>

namespace lab1 {

lab1::Circle::Circle() : Shape2D()
{
}

Circle::Circle(const Color &color, Point center, int radius)
    : Shape2D(color), m_center(std::move(center)), m_radius(radius)
{
}

std::istream & Circle::read(std::istream &ist) {
    // Считываем данные родительского класса
    Shape2D::read(ist);
    // Считываем собственные данные
    return deserialize(ist, m_center.first, m_center.second, m_radius);
}

std::ostream & Circle::write(std::ostream &ost) const {
    // Записываем данные родительского класса
    Shape2D::write(ost);
    // Записываем собственные данные
    return serialize(ost, m_center.first, m_center.second, m_radius);
}

std::string Circle::typeName() const {
    return std::move(std::string("Circle"));
}


std::istream & operator>>(std::istream &ist, Circle &circle) {
    std::string typeName;
    if (ist >> typeName && typeName == circle.typeName()) {
        circle.read(ist);
    }
    return ist;
}

std::ostream & operator<<(std::ostream &ost, const Circle &circle) {
    ost << circle.typeName();
    circle.write(ost);
    return ost;
}

} // namespace lab1