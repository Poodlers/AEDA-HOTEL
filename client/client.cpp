#include "client.h"

Client:: Client(const std::string &name, const unsigned int &NIF){
    //search for client if client exists raise ClientAlreadyExists exception
    //if client of a different name but with same NIF already exists raise exception

    this->name = name;
    this->NIF = NIF;
}

std::string Client::getName() const {
    return this->name;
}

unsigned int Client::getNIF() const {
    return this->NIF;
}

std::vector<Reservation*> Client::getHistory() const{
    return this->history;
}


Date Client::buildDate(const int &year, const int &month, const int &day){
    Date date;

    date.day = day;
    date.month = month;
    date.year = year;

    return date;
}

Reservation Client::buildReservation(const int &reservationSize, const Date & checkIn, const Date & checkOut, const int & roomId){
    Reservation reservation;
    reservation.checkIn = checkIn;
    reservation.checkOut = checkOut;
    reservation.roomId = roomId;
    reservation.reservationSize = reservationSize;
    return reservation;
}

void Client::setName(const std::string &name){
    this->name = name;
}

void Client::setNIF(const unsigned int &NIF){
    this->NIF = NIF;
}

void Client::addToHistory(Reservation &reservation){
    this->history.push_back(&reservation);
}

