#include "reservation.h"
#include "../utils/utils.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>


Reservation::Reservation(const int &reservationSize,Date* checkIn,Date* checkOut, const int & roomId, const int& reservationId) {
    if (*checkOut < *checkIn) { throw ReservationHasInvalidDates(); }

    if (reservationId == -1){
        this->reservationId = this->ID;
        ID++;
    }
    else this->reservationId = reservationId;

    this->reservationSize = reservationSize;
    this->checkIn = *checkIn;
    this->checkOut = *checkOut;
    this->roomId =  roomId;

}

Reservation::Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId){
    try{
        Date checkIn(dayIn,monthIn,yearIn), checkOut(dayOut,monthOut,yearOut);
        if (checkOut < checkIn) { throw ReservationHasInvalidDates(); }
        this->reservationId = this->ID;
        ID++;

        this->reservationSize = reservationSize;

        this->roomId = roomId;

        this->checkIn = checkIn;
        this->checkOut = checkOut;
    }
    catch(...){
        throw;
    }

}


bool Date::operator <=(Date date){
    if(this->year == date.getYear()){
        if(this->month == date.getMonth()){
            if (this->day <= date.getDay()) return true;
            else return false;
        }
        if(this->month < date.getMonth()) return true;
        else return false;
    }
    else if (this->year < date.getYear()) return true;
    else return false;
}

Date Reservation::getCheckIn() const{
    return this->checkIn;
}

Date Reservation::getCheckOut() const{
    return this->checkOut;
}

int Reservation::getReservationId() const {
    return this->reservationId;
}

int Reservation::getReservationSize() const {
    return this->reservationSize;
}

int Reservation::getRoomId() const {
    return this->roomId;
}

void Reservation::print() {
    std::cout << std::left <<  std::setw(20) << std::setfill(' ') << this->getReservationId()
              << std::setw(25) << this->getReservationSize()
              << std::setw(15) << this->getCheckIn() << std::setw(15) << this->checkOut << std::setw(8) << this->getRoomId();
}

void Reservation::setReservationId(const int & reservationId){
    this->reservationId =reservationId;
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


void Reservation::setID(const int& ID) const{
    this->ID = ID;
}

void Reservation::setRoomId(const int& roomId){
    this->roomId = roomId;
}

int Reservation::ID = 0;