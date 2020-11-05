#include "client.h"
#include <iostream>
#include "../../GUI/utils.h"

Client:: Client(const std::string &name, const unsigned int &NIF) : Person(name,NIF){}

std::vector<Reservation*>& Client::getHistory(){
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

bool Client::checkIn( Date *date) {
    int currentResev = this->futureReservations.size();
    for (Reservation *reservation: this->futureReservations) {
        if (reservation->getCheckIn() == *date) {
            this->futureReservations.push_back(reservation);
        }
        if ((reservation->getCheckIn() > *date) && (reservation->getCheckOut() < *date)) {
            std::cout << "The checkIn for room " << reservation->getRoomId() << " was "
                      << reservation->getCheckIn() - *date << " days late." << std::endl;
            reservation->setCheckIn(*date);
            if (reservation->getCheckOut() < *date) {
                this->history.push_back(reservation);
                std::cout << "The checkIn for room " << reservation->getRoomId() << " was "
                          << reservation->getCheckIn() - *date << " days late." << std::endl;
            }
        }
        if (currentResev == this->futureReservations.size()) return true;
        return false;
    }
}

void Client::edit() {
    std::string edit;
    std::cout << "Edit the Client's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    std::cout << "Name: " << std::endl;
    getStringInput(edit, 6, 3);
    if (edit != ".") this->setName(edit);
    gotoxy(0, 5);
    edit = "";
    std::cout << "NIF: " << std::endl;
    edit = GetNumberInput(5,5,CheckIfInteger);
    if(edit != ".") this->setNIF(std::stoi(edit));
}