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
            this->futureReservations.push_back(reservation);
        }
        if (reservation->getCheckOut() < *date){
            this->history.push_back(reservation);
            std::cout << "The checkIn for room " << reservation->getRoomId() <<" was "<< reservation->getCheckIn() - *date <<" days late."<<std::endl;
        }
    }
    if (currentResev == this->futureReservations.size()) return true;
    return false;
}

void Client::printConsole(){
    std::cout << "NIF: " << this->getNIF() << " Name: " << this->getName() << std::endl;
    std::cout<<"Client History:"<<std::endl;
    for (Reservation* reservation: this->history){
        reservation->print();
        std::cout<<std::endl;
    }
    std::cout << std::endl<<"Current Reservations:"<<std::endl;
    for (Reservation* reservation: this->currentReservations){
        reservation->print();
        std::cout<<std::endl;
    }
    std::cout << std::endl<<"Future Reservations:"<<std::endl;
    for (Reservation* reservation: this->futureReservations){
        reservation->print();
        std::cout<<std::endl;
    }
}

bool Client::operator==(Client* client){
    return ((this->getName() == client->getName()) && (this->getNIF() == client->getNIF()));
}

void Client::edit() {
    std::string edit;
    std::cout << "Edit the client's information as follows: " << std::endl;
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