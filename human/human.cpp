#include "human.h"

Human::Human(const std::string& name, const unsigned int & NIF){
    this->name = name;
    this->NIF = NIF;
}

std::string Human::getName() const {
    return this->name;
}

unsigned int Human::getNIF() const {
    return this->NIF;
}


void Human::setName(const std::string &name){
    this->name = name;
}

void Human::setNIF(const unsigned int &NIF){
    this->NIF = NIF;
}
