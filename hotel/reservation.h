#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>



class Date{
private:
    ///year
    int year;
    ///month
    int month;
    ///day
    int day;
public:
    /// Date's constructor
    ///
    /// \param day
    /// \param month
    /// \param year
    Date(const int &day, const int &month, const int &year);

    /// Date's constructor from a string
    ///
    /// \param date - must have format dd(char)mm(char)yyyy
    Date(const std::string& date);

    /// Default date constructor
    Date();

    /// Operator overload for <<
    ///
    /// \param o
    /// \param date
    /// \return o
    friend std::ostream & operator<<(std::ostream &o,const Date& date);

    ///Returns the day
    ///
    /// \return this->day
    int getDay() const;

    ///Returns the month
    ///
    /// \return this->month
    int getMonth() const;

    ///Returns the year
    ///
    /// \return this->year
    int getYear() const;

    ///Returns the number of days in this month
    ///
    /// \return number of days in this month
    int getDaysInMonth() const;

    ///Checks if this year is leap year
    ///
    /// \return true if leap year, false otherwise
    bool isInLeapYear() const;

    ///Operator overload for ==
    ///
    /// \param date
    /// \return true if ==, false if not
    bool operator ==(const Date& date);

    ///Operator overload for <
    ///
    /// \param date
    /// \return true if <, false if not
    bool operator <(const Date& date);

    ///Operator overload for >
    ///
    /// \param date
    /// \return true if >, false if not
    bool operator >(const Date& date);

    ///Operator overload for - between to dates
    ///
    /// \param date
    /// \return this-> - date
    int operator -(const Date& date);

    ///Operator overload for + between a date and a number
    ///
    /// \param d
    /// \return this-> + d
    Date operator +(int d) const;

    ///operator overload for <=
    ///
    /// \param date
    /// \return true if <=, false if not
    bool operator <=(const Date& date);

};

class Reservation{
public:
    Reservation(const int &reservationSize,Date* CheckIn,Date* CheckOut, const int & roomId, const int& reservationId);

    int getReservationId() const;
    Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId);
    Reservation(const std::string & reservation);
    Reservation();
    int getReservationNumber() const;
    int getReservationSize() const;
    Date getCheckIn() const;
    Date getCheckOut() const;
    int getRoomId() const;

    void setReservationId(const int & reservationId);
    void setReservationSize(const int & reservationSize);
    void setCheckIn(const Date& checkIn);
    void setCheckOut(const Date& checkOut);
    void setRoomId(const int& roomId);
    void edit();
    void print();

private:
    int reservationId;
    int reservationSize;
    Date checkIn ;
    Date checkOut;
    int roomId;
};


#endif
