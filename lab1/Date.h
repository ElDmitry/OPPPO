#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

namespace lab1 {

/// Представление даты в формате ДД:ММ:ГГГГ
// в текущей реализации работает только с текущей датой
class Date {
public:
    // Создаем объект текущей даты
    Date();

    std::string getStr() const;

    static std::string getCurrentDate();

private:
    void update();

    friend std::istream &operator>>(std::istream &ist, Date &date);

    friend std::ostream &operator<<(std::ostream &ost, const Date &date);

    unsigned m_day{};
    unsigned m_month{};
    unsigned m_year{};
};

std::istream &operator>>(std::istream &ist, Date &date);

std::ostream &operator<<(std::ostream &ost, const Date &date);

} // namespace lab1


#endif //DATE_H
