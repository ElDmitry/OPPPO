#include "Triangle.h"

#include <utility>

namespace lab1 {

Triangle::Triangle() : Shape2D() {  }

Triangle::Triangle(const Color &color, Triangle::Point x, Triangle::Point y, Triangle::Point z)
        : Shape2D(color), m_firstPoint(std::move(x))
        , m_secondPoint(std::move(y)), m_thirdPoint(std::move(z)) {

}

std::istream &Triangle::read(std::istream &ist) {
    // Считываем данные родительского класса
    Shape2D::read(ist);
    // Считываем собственные данные
    return deserialize(ist, m_firstPoint.first, m_firstPoint.second,
                       m_secondPoint.first, m_secondPoint.second,
                       m_thirdPoint.first, m_thirdPoint.second);
}

std::ostream &Triangle::write(std::ostream &ost) const {
    // Записываем данные родительского класса
    Shape2D::write(ost);
    // Записываем собственные данные
    return serialize(ost, m_firstPoint.first, m_firstPoint.second,
                       m_secondPoint.first, m_secondPoint.second,
                       m_thirdPoint.first, m_thirdPoint.second);
}

std::string Triangle::typeName() const {
    return std::move(std::string("Triangle"));
}

double Triangle::area() const {
    double a = distance(m_firstPoint.first, m_firstPoint.second, m_secondPoint.first, m_secondPoint.second);
    double b = distance(m_firstPoint.first, m_firstPoint.second, m_thirdPoint.first, m_thirdPoint.second);
    double c = distance(m_secondPoint.first, m_secondPoint.second, m_thirdPoint.first, m_thirdPoint.second);

    double p = 0.5 * (a + b + c);

    return sqrt(p * (p - a) * (p - b) * (p - c));
}

std::istream & operator>>(std::istream &ist, Triangle &triangle) {
    std::string typeName;
    if (ist >> typeName && typeName == triangle.typeName()) {
        triangle.read(ist);
    }
    return ist;
}

std::ostream & operator<<(std::ostream &ost, const Triangle &triangle) {
    ost << triangle.typeName();
    triangle.write(ost);
    return ost;
}


} // namespace lab1
