#include "client.h"
#include <iostream>
#include "../../GUI/utils.h"
#include <iomanip>

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

void Client::checkIn( Date date) {
    int numberOfFutureReservations = this->futureReservations.size();
    for (int i = 0; i < futureReservations.size(); i++) {
        if (futureReservations[i]->getCheckIn() == date) {
            this->currentReservations.push_back(futureReservations[i]);
            this->futureReservations.erase(futureReservations.begin()+i);
            std::cout << "The checkIn for room " << futureReservations[i]->getRoomId() << " was completed."<<std::endl;
        }
        else if ((futureReservations[i]->getCheckIn() < date) && (futureReservations[i]->getCheckOut() > date)) {
            std::cout << "The checkIn for room " << futureReservations[i]->getRoomId() << " was "
                      << date - futureReservations[i]->getCheckIn() << " days late." << std::endl;
            futureReservations[i]->setCheckIn(date);
            this->currentReservations.push_back(futureReservations[i]);
            this->futureReservations.erase(futureReservations.begin()+i);
        }
    }
    if (numberOfFutureReservations == this->futureReservations.size()) throw NoReservationsToCheckIn(this->getName(),this->getNIF());
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

void Client::checkOut( Date date){
    if (this->currentReservations.size()==0) throw NoReservationsToCheckOut(this->getName(),this->getNIF());
    for (int i = 0; i < currentReservations.size(); i++) {
        if (currentReservations[i]->getCheckOut() == date) {
            this->history.push_back(currentReservations[i]);
            this->currentReservations.erase(currentReservations.begin()+i);
            std::cout << "The checkOut for room " << currentReservations[i]->getRoomId() << " was completed."<<std::endl;
        }
        if (currentReservations[i]->getCheckOut() > date) {
            std::cout << "The checkOut for room " << currentReservations[i]->getRoomId() << " was "
                      << currentReservations[i]->getCheckOut() - date << " days early." << std::endl;
            currentReservations[i]->setCheckOut(date);
            this->history.push_back(currentReservations[i]);
            this->currentReservations.erase(currentReservations.begin()+i);
        }
    }
}

/*
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

}*/
