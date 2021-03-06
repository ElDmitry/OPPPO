#include "Shape2D.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

namespace lab1
{

std::string Shape2D::typeName() const {
    return std::move(std::string("Shape2D"));
}

Shape2D * Shape2D::createShape(const std::string &typeName) {
    Shape2D *shape = nullptr;
    if (typeName == "Circle") {
        shape = new Circle();
    }
    else if (typeName == "Rectangle") {
        shape = new Rectangle();
    }
    else if (typeName == "Triangle") {
        shape = new Triangle();
    }

    return shape;
}

std::istream &Shape2D::read(std::istream &ist) {
    return deserialize(ist, m_color, m_lastEdit, m_lineType);
}

std::ostream &Shape2D::write(std::ostream &ost) const {
    return serialize(ost, m_color, m_lastEdit, m_lineType);
}

std::istream & operator>>(std::istream &ist, std::shared_ptr<Shape2D> &shape) {
    // Предполагаем, что классы-наследники класса Shape2D имеют стандартное текстовое представление
    // $typeName = {/ (A-Z) | (a-z) /}.
    // $readableType = тип, для которого перегружены операторы <<>>.
    // $space = " " | "\t".
    // $end = "\n" | EOF.
    // $type = space readableType.
    // $ShapeObject = typeName {/ type /} end.

    std::string typeName;
    if (ist >> typeName) {
        shape.reset(Shape2D::createShape(typeName));
        if (shape) {
            shape->read(ist);
        }
    }
    // TODO: обработать неправильный ввод из файла

    return ist;
}

std::ostream & operator<<(std::ostream &ost, const std::shared_ptr<Shape2D> &shape) {
    if (shape) {
        ost << shape->typeName();
        shape->write(ost);
    }
    return ost;
}

Shape2D::Shape2D(const Color &color) : m_color(color)
{
}

std::istream & operator>>(std::istream &ist, Color &color) {
    std::string colorName;
    ist >> colorName;
    if (colorName == "RED") color = Color::RED;
    else if (colorName == "ORANGE") color = Color::ORANGE;
    else if (colorName == "YELLOW") color = Color::YELLOW;
    else if (colorName == "GREEN") color = Color::GREEN;
    else if (colorName == "LIGHT_BLUE") color = Color::LIGHT_BLUE;
    else if (colorName == "BLUE") color = Color::BLUE;
    else if (colorName == "PURPLE") color = Color::PURPLE;
    return ist;
}

std::ostream & operator<<(std::ostream &ost, const Color &color) {
    std::string colorName;
    switch (color) {
        case Color::RED: colorName = "RED"; break;
        case Color::ORANGE: colorName = "ORANGE"; break;
        case Color::YELLOW: colorName = "YELLOW"; break;
        case Color::GREEN: colorName = "GREEN"; break;
        case Color::LIGHT_BLUE: colorName = "LIGHT_BLUE"; break;
        case Color::BLUE: colorName = "BLUE"; break;
        case Color::PURPLE: colorName = "PURPLE"; break;
    }
    return ost << colorName;
}

std::istream & operator>>(std::istream &ist, LineType &type) {
    std::string typeName;
    ist >> typeName;
    if (typeName == "SOLID") type = LineType::SOLID;
    else if (typeName == "BLANK") type = LineType::BLANK;
    else if (typeName == "DASHED") type = LineType::DASHED;
    else if (typeName == "DOTTED") type = LineType::DOTTED;
    return ist;
}

std::ostream & operator<<(std::ostream &ost, const LineType &type) {
    std::string typeName;
    switch (type) {
        case LineType::SOLID: typeName = "SOLID"; break;
        case LineType::BLANK: typeName = "BLANK"; break;
        case LineType::DASHED: typeName = "DASHED"; break;
        case LineType::DOTTED: typeName = "DOTTED"; break;
    }
    return ost << typeName;
}

} // namespace lab1