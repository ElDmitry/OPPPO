#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape2D.h"

#include <utility>

namespace lab1
{

class Rectangle : public Shape2D {
public:
    using Point = std::pair<double, double>;

    Rectangle();
    explicit Rectangle(const Color &color, Point topLeft = Point(0., 0.),
                       Point bottomRight = Point(0., 0.));

    double area() const override;

    std::istream & read(std::istream &ist) override;
    std::ostream & write(std::ostream &ost) const override;

    std::string typeName() const override;

private:
    Point m_topLeft { 0., 0. };
    Point m_bottomRight { 0., 0. };
};

std::istream & operator>>(std::istream &ist, Rectangle &rectangle);
std::ostream & operator<<(std::ostream &ost, const Rectangle &rectangle);

} // namespace lab1

#endif // RECTANGLE_H
