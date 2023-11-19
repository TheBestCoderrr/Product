#include "Date.h"

Date::Date(const Date& date)
{
    *this = date;
}

Date::Date(const int num)
{
    *this = num;
}

Date::Date(const int d, const int m, const int y) : days(d), months(m), years(y) {}

size_t Date::getDays()
{
    const size_t nmonths[] = { 31, 28, 31,30,31,30,31,31,30,31,30,31 };
    size_t ndays = days;
    for (size_t i = 0; i < months; i++)
        ndays += nmonths[i];
    for (int i = 0; i < years; i++) {
        if (i % 4 == 0)
            ndays += 366;
        else
            ndays += 365;
    }
    return ndays;
}

Date& Date::operator=(const Date& date)
{
    days = date.days;
    months = date.months;
    years = date.years;
    return *this;
}

Date& Date::operator=(const int num)
{
    days = num;
    months = num;
    years = num;
    return *this;
}

ostream& operator<<(ostream& out, const Date& date) {
    out  << date.days << "." << date.months << "." << date.years << endl;
    return out;
}

istream& operator>>(istream& in, Date& date) {
    in >> date.days >> date.months  >> date.years;
    return in;
}
