#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape2D.h"

#include <utility>

namespace lab1 {

class Circle : public Shape2D {
public:
    using Point = std::pair<int, int>;

    Circle();
    explicit Circle(const Color &color, Point center = Point(0, 0), int radius = 0);

    double area() const override;

    std::istream & read(std::istream &ist) override;
    std::ostream & write(std::ostream &ost) const override;

    std::string typeName() const override;

private:
    Point m_center { 0, 0 };
    int m_radius { 0 };
};

std::istream & operator>>(std::istream &ist, Circle &circle);
std::ostream & operator<<(std::ostream &ost, const Circle &circle);

} // namespace lab1

#endif // CIRCLE_H
