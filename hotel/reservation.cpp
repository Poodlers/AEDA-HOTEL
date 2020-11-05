#include "reservation.h"
#include <sstream>
#include <algorithm>
int Reservation::reservationId = 0;



std::ostream & Date::operator<<(std::ostream &o) {
    o << this->day << "/" << this->month << "/" << this->year;
    return o;
}

Reservation::Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId){
    Date dateIn, dateOut;
    reservationId++;
    this->reservationNumber = reservationId;
    this->reservationSize = reservationSize;
    this->roomId = roomId;
    this->checkIn = buildDate(dayIn,monthIn,yearIn);
    this->checkOut = buildDate(dayOut,monthOut,yearOut);

}
Reservation :: Reservation(const std::string & reservation){
    //receives reservationSize,dayIn-monthIn-yearIn,dayOut-monthOut-yearOut,roomId
    std::stringstream ss(reservation);
    std::string dates;
    Date dateIn, dateOut;
    char ignore;
    reservationId++;
    this->reservationNumber = reservationId;
    ss>>this->reservationSize>> ignore >>  dateIn.day >> ignore >> dateIn.month   >> ignore >>  dateIn.year
    >> ignore >>  dateOut.day  >> ignore >>  dateOut.month >> ignore >> dateOut.year >>ignore >>  this->roomId;
    this->checkIn = dateIn;
    this->checkOut = dateOut;
}

Date Reservation::buildDate(const int& day, const int& month, const int& year){
    Date date;

    date.day = day;
    date.month = month;
    date.year = year;
    return  date;

}

Date Reservation::getCheckIn() {
    return this->checkIn;
}

Date Reservation::getCheckOut() {
    return this->checkOut;
}

int Reservation::getReservationSize() {
    return this->reservationSize;
}

int Reservation::getRoomId() {
    return this->roomId;
}

int Reservation::getreservationNumber() {
    return this->reservationNumber;
}