#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>


/// Represents a date structure
///
/// Is made up of a year, a month and a day
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
    /// \execption throws DateIsNotValid if date is not valid (day, month and/or year are negative numbers or the number of days is
    /// bigger then the number of days the month has
    Date(const int &day, const int &month, const int &year);

    /// Date's constructor from a string
    ///
    /// \param date - must have format dd(char)mm(char)yyyy
    /// \execption throws DateIsNotValid if date is not valid (day, month and/or year are negative numbers, not numbers or the number of days is
    /// bigger then the number of days the month has
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

    ///Returns the number of days in the month
    ///
    /// \param month - month to check
    /// \return number of days in this month
    /// \exception throws DateIsNotValid is the month is invalid
    int getDaysInMonth(const int& month) const;

    ///Checks if this year is leap year
    ///
    /// \return true if leap year, false otherwise
    bool isInLeapYear() const;

    ///Operator overload for ==
    ///
    /// \param date
    /// \return true if ==, false if not
    bool operator ==(Date date);

    ///Operator overload for <
    ///
    /// \param date
    /// \return true if <, false if not
    bool operator <(Date date);

    ///Operator overload for >
    ///
    /// \param date
    /// \return true if >, false if not
    bool operator >(Date date);

    ///Operator overload for - between to dates
    ///
    /// \param date
    /// \return this-> - date
    int operator -(Date date);

    ///Operator overload for + between a date and a number
    ///
    /// \param d
    /// \return this-> + d
    Date operator +(const int& d) const;

    ///operator overload for <=
    ///
    /// \param date
    /// \return true if <=, false if not
    bool operator <=(Date date);

};


/// Represents a reservation
///
/// Is made up of a reservation ID, a reservation size, do room ID of the reserved room, the check in date and the check out date
class Reservation{
public:
    ///Reservation constructor
    ///
    /// \param reservationSize - size of the reservation
    /// \param CheckIn - Check In date
    /// \param CheckOut - Check Out date
    /// \param roomId - Room ID
    /// \param reservationId - Reservation -> if -1 generates a new random ID
    /// \exception throws ReservationHasInvalidDates if Check Out date < Check In date
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
    /// \exception throws ReservationHasInvalidDates if Check Out date < Check In date
    /// \exception throws DateIsNotValid if Check Out date < Check In date or Check Out date are invalid
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

    /// Changes the reservations ID to reservationID
    ///
    /// \param reservationId - new reservation ID;
    void setReservationId(const int & reservationId);

    /// Changes the reservation size to reservationSize
    ///
    /// \param reservationSize - new reservation size
    void setReservationSize(const int & reservationSize);

    /// Changes the check in date
    ///
    /// \param checkIn - new check in date
    void setCheckIn(const Date& checkIn);

    /// Changes the RoomID
    ///
    /// \param roomId - new room ID
    void setRoomId(const int& roomId);

    /// Changes the check ou date
    ///
    /// \param checkOut - new check out date
    void setCheckOut(const Date& checkOut);

    void setRoomId(const int& roomId);
    /// Changes the ID
    ///
    /// used after initializing the hotel to make sure we don't repeat reservation IDs
    /// \param ID - new ID
    void setID(const int& ID) const;

    /// Prints the reservation
    void print();

private:
    /// Reservation ID
    int reservationId;
    /// Reservation size
    int reservationSize;
    ///Check in date
    Date checkIn ;
    ///Check out date
    Date checkOut;
    ///Room ID
    int roomId;
    ///variable to avoid repeating reservation IDs
    static int ID;
};


#endif
