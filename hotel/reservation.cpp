#include "reservation.h"
#include <sstream>
#include <algorithm>
int Reservation::reservationId = 0;

std::ostream & Date::operator<<(std::ostream &o) {
    o << this->day << "/" << this->month << "/" << this->year;
    return o;
}
Date::Date(const int &day, const int &month, const int &year){
    this->day = day;
    this->month = month;
    this->year = year;
}
Date::Date(const std::string& date){
    std::stringstream ss;
    char ignore;
    ss<<date;
    ss>>this->day>>ignore>>this->month>>ignore>>this->year;

}

Reservation::Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId){
    Date checkIn(dayIn,monthIn,yearIn), checkOut(dayOut,monthOut,yearOut);
    reservationId++;
    this->reservationNumber = reservationId;
    this->reservationSize = reservationSize;
    this->roomId = roomId;
    this->checkIn = checkIn;
    this->checkOut = checkOut;

}
Reservation :: Reservation(const std::string & reservation){
    //receives reservationSize,dayIn-monthIn-yearIn,dayOut-monthOut-yearOut,roomId
    std::stringstream ss(reservation);
    std::string dates;
    int day, month, year;
    char ignore;
    reservationId++;
    this->reservationNumber = reservationId;
    ss>>this->reservationSize>> ignore >>  day >> ignore >> month   >> ignore >>  year;
    Date dateIn(day,month,year);
    ss>> ignore >>  day  >> ignore >>  month >> ignore >> year >>ignore >>  this->roomId;
    Date dateOut(day,month,year);
    this->checkIn = dateIn;
    this->checkOut = dateOut;
}


Date Reservation::getCheckIn() const{
    return this->checkIn;
}

Date Reservation::getCheckOut() const{
    return this->checkOut;
}

int Reservation::getReservationSize() const {
    return this->reservationSize;
}

int Reservation::getRoomId() const {
    return this->roomId;
}

int Reservation::getReservationNumber() const {
    return this->reservationNumber;
}

void Reservation::setReservationNumber(const int & reservationNumber){
    this->reservationNumber =reservationNumber;
}
void Reservation::setReservationSize(const int & reservationSize){
    this->reservationSize =reservationSize;
}
void Reservation::setCheckIn(const Date& checkIn){
    this->checkIn =checkIn;
}
void Reservation::setCheckOut(const Date& checkOut){
    this->checkOut =checkOut;
}
void Reservation::setRoomId(const int& roomId){
    this->roomId =roomId;
}