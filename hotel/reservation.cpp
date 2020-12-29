#include "reservation.h"
#include <algorithm>
#include <iostream>
#include <iomanip>


Reservation::Reservation(const int &reservationSize,Date* checkIn,Date* checkOut, const int & roomId, const int& reservationId) {
    if (*checkOut < *checkIn) { throw ReservationHasInvalidDates(); }

    if (reservationId == -1){
        ID++;
        this->reservationId = this->ID;
    }
    else{
        ID = this->reservationId + 1;
        this->reservationId = reservationId;

    }

    this->reservationSize = reservationSize;
    this->checkIn = *checkIn;
    this->checkOut = *checkOut;
    this->roomId =  roomId;

}

void Reservation::setIsCurrent(bool isCurrent) {
    this->isCurrent = isCurrent;
}

void Reservation::setRoomId(int roomId) {
    this->roomId = roomId;
}

bool Reservation::getIsCurrent() const {
    return this->isCurrent;
}

void Reservation::setReservationSize(int reservationSize) {
    this->reservationSize = reservationSize;
}

Reservation::Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId){
    try{
        Date checkIn(dayIn,monthIn,yearIn), checkOut(dayOut,monthOut,yearOut);
        if (checkOut < checkIn) { throw ReservationHasInvalidDates(); }
        ID++;
        this->reservationId = this->ID;


        this->reservationSize = reservationSize;

        this->roomId = roomId;

        this->checkIn = checkIn;
        this->checkOut = checkOut;
    }
    catch(...){
        throw;
    }

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


void Reservation::setCheckIn(Date* checkIn){
    this->checkIn = *checkIn;
}
void Reservation::setCheckOut(Date* checkOut){
    this->checkOut = *checkOut;
}


void Reservation::setID(const int& ID) const{
    this->ID = ID;
}

int Reservation::ID = 0;