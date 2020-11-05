#include "client.h"

Client:: Client(const std::string &name, const unsigned int &NIF) : Human(name,NIF){}

std::vector<Reservation*>& Client::getHistory() const{
    return this->history;
}

void Client::addToHistory(Reservation &reservation){
    this->history.push_back(&reservation);
}
