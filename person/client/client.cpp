#include "client.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

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
    std::vector<int> reservationIds;
    int numberOfFutureReservations = this->futureReservations.size();
    for (int i = 0; i < futureReservations.size(); i++) {
        if (futureReservations[i]->getCheckIn() == *date) {
            this->currentReservations.push_back(futureReservations[i]);
            currentReservations[i]->setIsCurrent(true);
            reservationIds.push_back(futureReservations[i]->getReservationId());
            this->futureReservations.erase(futureReservations.begin()+i);
            std::cout << "The checkIn for room " << futureReservations[i]->getRoomId() << " was completed."<<std::endl;
        }
        else if ((futureReservations[i]->getCheckIn() < *date) && (futureReservations[i]->getCheckOut() > *date)) {
            std::cout << "The checkIn for room " << futureReservations[i]->getRoomId() << " was "
                      << *date - futureReservations[i]->getCheckIn() << " days late." << std::endl;
            futureReservations[i]->setCheckIn(date);
            this->currentReservations.push_back(futureReservations[i]);
            currentReservations[i]->setIsCurrent(true);
            reservationIds.push_back(futureReservations[i]->getReservationId());
            this->futureReservations.erase(futureReservations.begin()+i);
        }
    }
    if (numberOfFutureReservations == this->futureReservations.size()) throw NoReservationsToCheckIn(this->getName(),this->getNIF());
    return reservationIds;
}

void Client::archiveExpiredReservations(Date* date){
    for (int i = 0; i < futureReservations.size(); i++) {
        if (futureReservations[i]->getCheckOut() < *date) {
            this->history.push_back(futureReservations[i]);
            this->futureReservations.erase(futureReservations.begin() + i);
            i--;
        }
    }
    for (int i = 0; i < currentReservations.size(); i++){
        if (currentReservations[i]->getCheckOut() < *date){
            currentReservations[i]->setIsCurrent(false);
            this->history.push_back(currentReservations[i]);
            this->currentReservations.erase(currentReservations.begin()+i);
            //std::cout << "Reservation " << currentReservations[i]->getReservationId() <<" for client: " << this->name << " with NIF: " << this->NIF << " has expired."<<std::endl;
            i--;
        }
    }

}

void Client::printConsole(){

    std::cout << std::endl <<"NIF: " << this->getNIF() << " Name: " << this->getName() << std::endl;

    if(!this->history.empty()){
        std::cout<<"Client History:"<<std::endl;
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation ID"
                             << std::setw(25) << "Reservation Size" <<std::setw(16)<< "Check In"<< std::setw(16)
                             << "Check Out"
                             << std::setw(8) << "Room ID"<<std::endl;
    }
    for (Reservation* reservation: this->history){
        reservation->print();
        std::cout<<std::endl;
    }
    if(!this->currentReservations.empty()) {
        std::cout << std::endl << "Current Reservations:" << std::endl;
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation ID"
                  << std::setw(25) << "Reservation Size" <<std::setw(16)<< "Check In"<< std::setw(16)
                  << "Check Out"
                  << std::setw(8) << "Room ID"<<std::endl;
    }
    for (Reservation* reservation: this->currentReservations){
        reservation->print();
        std::cout<<std::endl;
    }
    if(!this->futureReservations.empty()) {
        std::cout << std::endl << "Future Reservations:" << std::endl;
        std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation ID"
                  << std::setw(25) << "Reservation Size" <<std::setw(16)<< "Check In"<< std::setw(16)
                  << "Check Out"
                  << std::setw(8) << "Room ID"<<std::endl;
    }
    for (Reservation* reservation: this->futureReservations){
        reservation->print();
        std::cout<<std::endl;
    }
}

std::vector<Reservation *> & Client::getAllReservations() {
    this->allReservations.clear();
    for(auto resev: this->currentReservations) this->allReservations.push_back(resev);
    for(auto resev: this->history) this->allReservations.push_back(resev);
    for(auto resev: this->futureReservations) this->allReservations.push_back(resev);
    return allReservations;
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

void Client::deleteReservation(Reservation *reservation) {
    auto find_history = std::find(this->history.begin(),this->history.end(),reservation);
    auto find_future = std::find(this->futureReservations.begin(),this->futureReservations.end(),reservation);
    if(find_history != this->history.end()){
        this->history.erase(find_history);
    }else if(find_future != this->futureReservations.end()){
        this->futureReservations.erase(find_future);
    }
}

std::vector<int> Client::checkOut( Date* date){
    std::vector<int> reservationIds;
    if (this->currentReservations.size()==0) throw NoReservationsToCheckOut(this->getName(),this->getNIF());
    for (int i = 0; i < currentReservations.size(); i++) {
        if (currentReservations[i]->getCheckOut() == *date) {
            currentReservations[i]->setIsCurrent(false);
            this->history.push_back(currentReservations[i]);
            reservationIds.push_back(currentReservations[i]->getReservationId());
            this->currentReservations.erase(currentReservations.begin()+i);
            std::cout << "The checkOut for room " << currentReservations[i]->getRoomId() << " was completed."<<std::endl;
        }
        if (currentReservations[i]->getCheckOut() > *date) {
            currentReservations[i]->setIsCurrent(false);
            std::cout << "The checkOut for room " << currentReservations[i]->getRoomId() << " was "
                      << currentReservations[i]->getCheckOut() - *date << " days early." << std::endl;
            currentReservations[i]->setCheckOut(date);
            this->history.push_back(currentReservations[i]);
            reservationIds.push_back(currentReservations[i]->getReservationId());
            this->currentReservations.erase(currentReservations.begin()+i);
        }
    }
    return reservationIds;
}

void Client::setHistory(const std::vector<Reservation *> &history) {
    this->history = history;
}

void Client::setFutureReservations(const std::vector<Reservation *> &futureReservations) {
    this->futureReservations = futureReservations;
}

void Client::setCurrentReservations(const std::vector<Reservation *> &currentReservations) {
    this->currentReservations = currentReservations;
}

void Client::setAllReservations(const std::vector<Reservation *> &allReservations) {
    this->allReservations = allReservations;
}

