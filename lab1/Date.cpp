#include "Date.h"

#include <ctime>
#include <sstream>
#include <iomanip>

namespace lab1 {

Date::Date() {
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

std::istream &operator>>(std::istream &ist, Date &date) {
    char sep;
    return ist >> date.m_day >> sep >> date.m_month >> sep >> date.m_year;
}

std::ostream &operator<<(std::ostream &ost, const Date &date) {
    return ost << date.getStr();
}

} // namespace lab1
