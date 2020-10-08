#include "Shape2DTypes.h"

#include <ctime>
#include <sstream>
#include <iomanip>

namespace lab1 {

Date::Date()
{
    update();
}

void Date::update() {
    auto now = std::time(nullptr);

    // указатель на глобальный объект представления даты.
    // Данный способ не потокобезопасен!
    std::tm *ltm = std::localtime(&now);

    m_day = ltm->tm_mday;
    m_month = ltm->tm_mon + 1;
    m_year = ltm->tm_year + 1900;
}

std::string Date::getCurrentDate() {
    Date now;
    return now.getStr();
}

std::string Date::getStr() const {
    using namespace std;

    stringstream ss;
    char sep = ':';
    ss << setw(2) << setfill('0') << right
       << m_day << sep
       << setw(2) << setfill('0') << right << m_month << sep << setw(4) << m_year;

    return std::move(ss.str());
}

std::istream & operator>>(std::istream &ist, Date &date) {
    char sep;
    return ist >> date.m_day >> sep >> date.m_month >> sep >> date.m_year;
}

std::ostream & operator<<(std::ostream &ost, const Date &date) {
    return ost << date.getStr();
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


} // namespace lab1