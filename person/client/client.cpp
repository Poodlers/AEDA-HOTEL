#include "client.h"
#include <iostream>
#include "../../GUI/utils.h"
#include <iomanip>
#include <algorithm>

Client::Client():Person() {
}

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

std::vector<int> Client::checkIn(Date* date) {
    std::vector<int> roomIds;
    int numberOfFutureReservations = this->futureReservations.size();
    for (int i = 0; i < futureReservations.size(); i++) {
        if (futureReservations[i]->getCheckIn() == *date) {
            this->currentReservations.push_back(futureReservations[i]);
            roomIds.push_back(futureReservations[i]->getRoomId());
            this->futureReservations.erase(futureReservations.begin()+i);
            std::cout << "The checkIn for room " << futureReservations[i]->getRoomId() << " was completed."<<std::endl;
        }
        else if ((futureReservations[i]->getCheckIn() < *date) && (futureReservations[i]->getCheckOut() > *date)) {
            std::cout << "The checkIn for room " << futureReservations[i]->getRoomId() << " was "
                      << *date - futureReservations[i]->getCheckIn() << " days late." << std::endl;
            futureReservations[i]->setCheckIn(*date);
            this->currentReservations.push_back(futureReservations[i]);
            roomIds.push_back(futureReservations[i]->getRoomId());
            this->futureReservations.erase(futureReservations.begin()+i);
        }
    }
    if (numberOfFutureReservations == this->futureReservations.size()) throw NoReservationsToCheckIn(this->getName(),this->getNIF());
    return roomIds;
}

void Client::archiveExpiredReservations(Date date){
    for (int i = 0; i < futureReservations.size(); i++){
        if (futureReservations[i]->getCheckOut() < date){
            this->history.push_back(futureReservations[i]);
            this->futureReservations.erase(futureReservations.begin()+i);
            std::cout << "Reservation " << futureReservations[i]->getReservationId() <<" for client: " << this->name << " with NIF: " << this->NIF << " has expired."<<std::endl;
            i--;
        }
    }
}

void Client::printConsole(){

    std::cout << std::endl <<"NIF: " << this->getNIF() << " Name: " << this->getName() << std::endl;

    if(!this->history.empty()){
        std::cout<<"Client History:"<<std::endl;
    }
    for (Reservation* reservation: this->history){
        reservation->print();
        std::cout<<std::endl;
    }
    if(!this->currentReservations.empty()) {
        std::cout << std::endl << "Current Reservations:" << std::endl;
    }
    for (Reservation* reservation: this->currentReservations){
        reservation->print();
        std::cout<<std::endl;
    }
    if(!this->futureReservations.empty()) {
        std::cout << std::endl << "Future Reservations:" << std::endl;
    }
    for (Reservation* reservation: this->futureReservations){
        reservation->print();
        std::cout<<std::endl;
    }
}

bool Client::operator==(Client* client){
    return ((this->getName() == client->getName()) && (this->getNIF() == client->getNIF()));
}

std::vector<Reservation*> Client::getCurrentReservations() const{
    return this->currentReservations;
}

void Client::addCurrentReservation(Reservation *reservation){
    currentReservations.push_back(reservation);
}

std::vector<int> Client::checkOut( Date* date){
    std::vector<int> roomIds;
    if (this->currentReservations.size()==0) throw NoReservationsToCheckOut(this->getName(),this->getNIF());
    for (int i = 0; i < currentReservations.size(); i++) {
        if (currentReservations[i]->getCheckOut() == *date) {
            this->history.push_back(currentReservations[i]);
            roomIds.push_back(currentReservations[i]->getRoomId());
            this->currentReservations.erase(currentReservations.begin()+i);
            std::cout << "The checkOut for room " << currentReservations[i]->getRoomId() << " was completed."<<std::endl;
        }
        if (currentReservations[i]->getCheckOut() > *date) {
            std::cout << "The checkOut for room " << currentReservations[i]->getRoomId() << " was "
                      << currentReservations[i]->getCheckOut() - *date << " days early." << std::endl;
            currentReservations[i]->setCheckOut(*date);
            this->history.push_back(currentReservations[i]);
            roomIds.push_back(currentReservations[i]->getRoomId());
            this->currentReservations.erase(currentReservations.begin()+i);
        }
    }
    return roomIds;
}

void Client::removeReservation(Reservation *reservation) {
    this->history.erase(std::find(this->history.begin(),this->history.end(),reservation));
    delete reservation;
}

