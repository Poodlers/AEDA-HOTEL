#ifndef CLIENT_H
#define CLIENT_H
#include "staff.h"

Staff::Staff(const std::string& name, const unsigned int & NIF, const float& wage){
    //if staff member already exists raise exception
    //if staff member of different name but with same NIF already exists raise exception

    this->name = name;
    this->NIF = NIF;
    this->wage = wage;
    this-> yearsOfService = 0;
}

std::string Staff::getName() const{
    return this->name;
}

unsigned int Staff::getNIF() const{
    return this->NIF;
}

float Staff::getWage() const{
    return this->wage;
}

int Staff::getyearsOfService() const{
    return this->yearsOfService;
}

void Staff::setName(const std::string name){
    this->name = name;
}

void Staff::setNIF(const unsigned int NIF){
    this->NIF = NIF;
}

void Staff::setwage(const float wage){
    this->wage = wage;
}

void Staff::setyearsOfService(const int yearsOfService){
    this->yearsOfService = yearsOfService;
}