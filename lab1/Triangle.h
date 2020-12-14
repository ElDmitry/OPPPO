#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape2D.h"

#include <utility>

namespace lab1 {

class Triangle : public Shape2D {
public:
    using Point = std::pair<double, double>;

    Triangle();
    Triangle(const Color &color, Point x, Point y, Point z);

    double area() const override;

    std::istream & read(std::istream &ist) override;
    std::ostream &write(std::ostream &ost) const override;

    std::string typeName() const override;


private:
    Point m_firstPoint {0., 0.};
    Point m_secondPoint {0., 0.};
    Point m_thirdPoint {0., 0.};
};

std::istream & operator>>(std::istream &ist, Triangle &triangle);
std::ostream & operator<<(std::ostream &ost, const Triangle &triangle);

} // namespace lab1

#endif // TRIANGLE_H
