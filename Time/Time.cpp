#include <iostream>
#include <ctime>
#include <iomanip>

/*
        ДОМАШНЕЕ ЗАДАНИЕ:

        Задание 1: Реализуйте класс Time (формат времени - часы:минуты)
        + реализуйте конструктор через который можно установить начальное время
        + перегрузите постфиксные и префиксные операторы инкремента и декремента
        + операторы инкремента и декремента увеличивают и уменьшают минуты соответственно.
        + при достижении 60 минут (в результате инкремента),минуты должны обнуляться а часы должны быть увеличены на 1
        + при достижении 00 минут (в результате декремента),минуты должны быть равны 59 а часы должны быть уменьшены на 1
        + инкремент для 23:59 устанавливает время в 00:00
        + декремент для 00:00 устанавливает время в 23:59
        + реализуйте сравнение двух объеков типа Time (<,>,<=,>=, !=, ==)
        + перегрузите оператор ввода и вывода для типа Time


        ДОМАШНЕЕ ЗАДАНИЕ:

        Задание 2: Реализуйте следующие методы для IntArray
        + конструктор копирования
        + конструктор перемещения
        + оператор присваивания перемещением
        + оператор присваивания копированием
        + деструктор
    */
class Time
{
public:
    Time()
    {
        Now();
    };

    Time(int hour, int minute)
    {
        chekTime(hour, minute);
    }

    void Now()
    {
        int b = time(nullptr);
        int today = b % (60 * 60 * 24);

        m_hours = today / 3600 + 4;// 4 eto vremennaya razmetka baku 
        m_minutes = (today % 3600 - today % 60) / 60;
    }


    bool operator>(const Time& right)
    {
        int timeOne = m_hours * 60 + m_minutes;
        int timeTwo = right.m_hours * 60 + right.m_minutes;

        return (timeOne > timeTwo);
    }

    bool operator<(const Time& right)
    {
        int timeOne = m_hours * 60 + m_minutes;
        int timeTwo = right.m_hours * 60 + right.m_minutes;

        return (timeOne < timeTwo);
    }

    bool operator>=(const Time& right)
    {
        int timeOne = m_hours * 60 + m_minutes;
        int timeTwo = right.m_hours * 60 + right.m_minutes;

        return (timeOne >= timeTwo);
    }

    bool operator<=(const Time& right)
    {
        int timeOne = m_hours * 60 + m_minutes;
        int timeTwo = right.m_hours * 60 + right.m_minutes;

        return (timeOne <= timeTwo);
    }

    bool operator==(const Time& right)
    {
        int timeOne = m_hours * 60 + m_minutes;
        int timeTwo = right.m_hours * 60 + right.m_minutes;

        return (timeOne == timeTwo);
    }

    bool operator!=(const Time& right)
    {
        int timeOne = m_hours * 60 + m_minutes;
        int timeTwo = right.m_hours * 60 + right.m_minutes;

        return (timeOne != timeTwo);
    }

    Time& operator++()
    {
        int minute = 1;
        chekMinute(minute);
        return *this;
    }

    Time& operator--()
    {
        int minute = -1;
        if (m_minutes == 0) {
            if (m_hours == 0) {
                m_hours = 23;
                m_minutes = 60;
            }
            else {
                m_hours--;
                m_minutes = 60;
            }
        }
        chekMinute(minute);
        return *this;
    }

    Time operator++(int)
    {
        Time result(m_hours, m_minutes);
        int minute = 1;
        chekMinute(minute);
        return result;
    }

    Time operator--(int)
    {

        Time result(m_hours, m_minutes);
        int minute = -1;
        if (m_minutes == 0) {
            if (m_hours == 0) {
                m_hours = 23;
                m_minutes = 60;
            }
            else {
                m_hours--;
                m_minutes = 60;
            }
        }
        chekMinute(minute);
        return result;
    }


    void setAddMinute(int minute)
    {
        chekMinute(minute);
    }

    void setAddHour(int hour)
    {
        chekHour(hour);
    }


    void setMinute(int minute)
    {
        m_hours += minute / 60;
        m_minutes = (minute) % 60;
        m_hours = m_hours % 24;;
    }

    void setHour(int hour)
    {
        m_hours = (hour) % 24;
    }



    int getMinute()const
    {
        return m_minutes;
    }

    int getHour()const
    {
        return m_hours;
    }

private:
    void chekHour(int hour) {
        m_hours = (hour + m_hours) % 24;
    }

    void chekMinute(int minute) {
        m_hours += (m_minutes + minute) / 60;
        m_minutes = ((m_minutes + minute) % 60);
        m_hours = m_hours % 24;
    }

    void chekTime(int hour, int minute) {
        chekMinute(minute);
        chekHour(hour);
    }

    unsigned int m_hours = 0;
    unsigned int m_minutes = 0;
};

std::ostream& operator<<(std::ostream& os, const Time& n)
{
    os << "  _______________\n |               |\n |  "
        << std::right << std::setw(2) << std::setfill('0') << n.getHour() << " : "
        << std::right << std::setw(2) << std::setfill('0') << n.getMinute();

    (n.getHour() >= 0 && n.getHour() <= 11) ? os << " A.M. " : os << " P.M. ";
    os << "|\n |_______________|";
    return os;
}

std::istream& operator>>(std::istream& is, Time& n)
{
    int time;
    std::cout << "\nEnter hour   : ";
    is >> time;
    n.setAddHour(time);
    std::cout << "Enter minute : ";
    is >> time;
    n.setAddMinute(time);
    return is;
}

int main()
{
    Time now;
    std::cout << "Now time\n" << now << '\n';
    //  std::cout << "\n\n==============================================\n\n";

    Time a(12, 0);
    Time b(12, 54);

    a.setAddHour(12);   //Add to time sentiment => Dobavit k suwestvuewimu vremeni
    a.setAddMinute(2);

    a.setHour(18);      //set a new time  =>   zadat novoe vremya
    a.setMinute(59);


   // std::cout << a << '\n';
   // std::cout << b;



    std::cout << "\n\n==============================================\n\n";

    std::cout << " \n\na =\n" << a << '\n';
    std::cout << " \n\nb = \n" << b << '\n';

    std::cout << std::boolalpha;
    std::cout << "\n1) (a > b)  = " << (a > b) << '\n';
    std::cout << "\n2) (a >= b) = " << (a >= b) << '\n';
    std::cout << "\n3) (a < b)  = " << (a < b) << '\n';
    std::cout << "\n4) (a <= b) = " << (a <= b) << '\n';
    std::cout << "\n5) (a == b  = " << (a == b) << '\n';
    std::cout << "\n6) (a != b) = " << (a != b) << '\n';


    std::cout << "\n\n==============================================\n\n";

    std::cout << "\na = \n" << a << '\n';
    std::cout << "\n(a++) = \n" << (a++) << '\n';
    std::cout << "\na = \n" << a << '\n';
    std::cout << "\n(++a) = \n" << (++a) << '\n';
    std::cout << "\na = \n" << a << '\n';
    std::cout << "\n(a--) = \n" << (a--);
    std::cout << "\na = \n" << a << '\n';
    std::cout << "\n(--a) = \n" << (--a);
    std::cout << "\na = \n" << a << '\n';
}