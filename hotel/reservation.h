#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>

class Date{
private:
    int year;
    int month;
    int day;
public:
    Date(const int &day, const int &month, const int &year);
    Date(const std::string& date);
    Date();
    std::ostream & operator<<(std::ostream &o);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getDaysInMonth() const;
    bool isInLeapYear() const;
    bool operator ==(const Date& date);
    bool operator <(const Date& date);
    bool operator >(const Date& date);
    int operator - (const Date& date);
    Date operator+(int d) const;
    friend Date operator+(int daysToAdd, const Date& date);
};

class Reservation{
public:
    Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId);
    Reservation(const std::string & reservation);

    int getReservationNumber() const;
    int getReservationSize() const;
    Date getCheckIn() const;
    Date getCheckOut() const;
    int getRoomId() const;

    void setReservationNumber(const int & reservationNumber);
    void setReservationSize(const int & reservationSize);
    void setCheckIn(const Date& checkIn);
    void setCheckOut(const Date& checkOut);
    void setRoomId(const int& roomId);

    void print();

private:
    static int reservationId;
    int reservationNumber;
    int reservationSize;
    Date checkIn ;
    Date checkOut;
    int roomId;
};


#endif
