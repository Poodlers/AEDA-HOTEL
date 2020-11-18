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
    ///Reservation constructor
    ///
    /// \param reservationSize - size of the reservation
    /// \param CheckIn - Check In date
    /// \param CheckOut - Check Out date
    /// \param roomId - Room ID
    /// \param reservationId - Reservation -> if -1 generates a new random ID
    /// \exception throws <ReservationHasInvalidDates> if Check Out data < Check In data
    Reservation(const int &reservationSize,Date* CheckIn,Date* CheckOut, const int & roomId, const int& reservationId);

    ///Returns the reservation ID
    ///
    /// \return reservationId
    int getReservationId() const;

    ///Reservation constructor
    ///
    /// \param reservationSize - size of the reservation
    /// \param dayIn - Day of the check In
    /// \param monthIn - Month of the check In
    /// \param yearIn - Year of the check In
    /// \param dayOut - Day of the check Out
    /// \param monthOut - Month of the check Out
    /// \param yearOut - Year of the check Out
    /// \param roomId - Id of the reserved room
    Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId);

    ///Default constructor
    Reservation();

    ///Return reservation size
    ///
    /// \return reservation size
    int getReservationSize() const;

    ///Returns the check In date
    ///
    /// \return check in date
    Date getCheckIn() const;

    ///Returns the check Out date
    ///
    /// \return check out date
    Date getCheckOut() const;

    ///Returns the room ID
    ///
    /// \return room ID
    int getRoomId() const;

    void setReservationId(const int & reservationId);
    void setReservationSize(const int & reservationSize);
    void setCheckIn(const Date& checkIn);
    void setCheckOut(const Date& checkOut);
    void setRoomId(const int& roomId);
    void setID(const int& ID) const;
    void print();

private:
    int reservationId;
    int reservationSize;
    Date checkIn ;
    Date checkOut;
    int roomId;
    static int ID;
};


#endif
