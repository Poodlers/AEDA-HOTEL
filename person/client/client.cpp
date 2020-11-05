#include "client.h"
#include <iostream>

Client:: Client(const std::string &name, const unsigned int &NIF) : Person(name,NIF){}

std::vector<Reservation*> Client::getHistory() const{
    return this->history;
}

void Client::addToHistory(Reservation &reservation){
    this->history.push_back(&reservation);
}
void Client::printClient(){
    std::cout << "NIF: " << this->getNIF() << " Name: " << this->getName() << std::endl;
}