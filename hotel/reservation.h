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
    friend std::ostream & operator<<(std::ostream &o,const Date& date);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getDaysInMonth() const;
    bool isInLeapYear() const;
    bool operator ==(const Date& date);
    bool operator <(const Date& date);
    bool operator >(const Date& date);
    int operator -(const Date& date);
    Date operator +(int d) const;
    bool operator <=(const Date& date);

    friend Date operator+(int daysToAdd, const Date& date);
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
