#include "client.h"
#include <iostream>

Client:: Client(const std::string &name, const unsigned int &NIF) : Person(name,NIF){}

std::vector<Reservation*> Client::getHistory() const{
    return this->history;
}

void Client::addToHistory(Reservation *reservation){
    this->history.push_back(reservation);
}

std::vector<Reservation*> Client::getFutureReservations() const{
    return this->futureReservations;
}

void Client::addNewReservation(Reservation *reservation){
    this->futureReservations.push_back(reservation);
}

bool Client::checkIn( Date *date){
    int currentResev = this->futureReservations.size();
    for(Reservation* reservation: this->futureReservations){
        if (reservation->getCheckIn() == *date){
            this->futureReservations.push_back(reservation);
        }
        if ((reservation->getCheckIn() > *date)&&(reservation->getCheckOut() < *date)){
            reservation->setCheckIn(*date);
            this->futureReservations.push_back(reservation);
        }
        if (reservation->getCheckOut() < *date){
            this->history.push_back(reservation);
        }
    }
    if (currentResev == this->futureReservations.size()) return true;
    return false;
}

void Client::printClient(){
    std::cout << "NIF: " << this->getNIF() << " Name: " << this->getName() << std::endl;
}