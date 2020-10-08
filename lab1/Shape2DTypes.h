#ifndef SHAPE2DTYPES_H
#define SHAPE2DTYPES_H

#include <string>
#include <iostream>

namespace lab1
{

enum class Color {
    RED = 0,
    ORANGE,
    YELLOW,
    GREEN,
    LIGHT_BLUE,
    BLUE,
    PURPLE
};

std::istream & operator>>(std::istream &ist, Color &color);
std::ostream & operator<<(std::ostream &ost, const Color &color);

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

    friend std::istream & operator>>(std::istream &ist, Date &date);
    friend std::ostream & operator<<(std::ostream &ost, const Date &date);

    unsigned m_day;
    unsigned m_month;
    unsigned m_year;
};

std::istream & operator>>(std::istream &ist, Date &date);
std::ostream & operator<<(std::ostream &ost, const Date &date);


// Ввод-вывод полей объектов реализуем шаблонными функциями с переменным числом аргументов.
// Таким образом, получаем подержку ввода-вывода всех типов для которых переопределены стандартные операторы,
// в том числе вложенные пользовательские типы.
// Также теоретически можем написать специализацию для встроенных типов. Например: считать, что строки имеют вид "...".
//======================================================================================================================
// база рекурсии
inline std::ostream & serialize(std::ostream &ost) { return ost; }

/// Записывает параметры в выходной поток
template<typename T, typename... Args>
std::ostream & serialize(std::ostream &ost, const T &t, const Args&... args) {
    ost << " " << t;
    return serialize(ost, args...);
}

// база рекурсии
inline std::istream & deserialize(std::istream &ist) { return ist; }

/// Читаем параметры из входного потока
template<typename T, typename... Args>
std::istream & deserialize(std::istream &ist, T &t, Args&... args) {
    // возможно надо добавить обработку ошибок
    ist >> t;
    return deserialize(ist, args...);
}

} // namespace lab1


#endif // SHAPE2DTYPES_H
