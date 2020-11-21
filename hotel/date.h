#ifndef DATE_H
#define DATE_H
#include "../exceptions/exceptions.h"

/// \class Date
/// Class which represents a Date.
///
/// Defined by a year, a month and a day.
class Date{
private:
    ///year.
    int year;
    ///month.
    int month;
    ///day.
    int day;
public:
    /// Date's constructor.
    ///
    /// \param day
    /// \param month
    /// \param year
    /// \exception throws DateIsNotValid if date is not valid (day, month and/or year are negative numbers or the number of days is
    /// bigger than the total number of days in the month).
    Date(const int &day, const int &month, const int &year);

    /// Date's constructor from a string.
    ///
    /// \param date  must have format dd(char)mm(char)yyyy.
    /// \exception throws DateIsNotValid if date is not valid (day, month and/or year are negative numbers, not numbers or the number of days is
    ///  bigger than the total number of days in the month).
    Date(const std::string& date);

    /// Default date constructor.
    Date();

    /// Operator overload for <<.
    ///
    /// Format 'dd-mm-yyyy         '
    /// \param o
    /// \param date
    /// \return o
    friend std::ostream & operator<<(std::ostream &o,const Date& date);

    /// Returns day.
    ///
    /// \return this->day.
    int getDay() const;

    /// Returns month.
    ///
    /// \return this->month.
    int getMonth() const;

    ///Returns year.
    ///
    /// \return this->year.
    int getYear() const;

    /// Returns number of days in the month.
    ///
    /// \param month  month to check.
    /// \return number of days in this month.
    /// \exception throws DateIsNotValid is the month is invalid.
    int getDaysInMonth(const int& month) const;

    /// Checks if this year is leap year.
    ///
    /// \return true if leap year, false otherwise.
    bool isInLeapYear() const;

    /// Operator overload for ==.
    ///
    /// \param date
    /// \return true if ==, false if not.
    bool operator ==(Date date);

    /// Operator overload for <.
    ///
    /// \param date
    /// \return true if <, false if not.
    bool operator <(Date date);

    /// Operator overload for >.
    ///
    /// \param date
    /// \return true if >, false if not.
    bool operator >(Date date);

    /// Operator overload for - between two dates.
    ///
    /// \param date
    /// \return this->date.
    int operator -(Date date);

    /// Operator overload for + between a date and a number.
    ///
    /// \param d
    /// \return this-> + d
    Date operator +(const int& d) const;

    /// Operator overload for <=.
    ///
    /// \param date
    /// \return true if <=, false if not.
    bool operator <=(Date date);

};



#endif