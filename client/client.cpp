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

void Client::setName(const std::string &name){
    this->name = name;
}

void Client::setNIF(const unsigned int &NIF){
    this->NIF = NIF;
}

void Client::addToHistory(Reservation &reservation){
    this->history.push_back(&reservation);
}

