#include "staff.h"


string Staff::getName() const{
    return this->name;
}

string Staff::getNIF() const{
    return this->NIF;
}

float Staff::getWage() const{
    return this->wage;
}

int Staff::getyearsOfService() const{
    return this->yearsOfService;
}

void Staff::setName(const string name){
    this->name = name;
}

void Staff::setNIF(const string NIF){
    this->NIF = NIF;
}

void Staff::setwage(const float wage){
    this->wage = wage;
}

void Staff::setyearsOfService(const int yearsOfService){
    this->yearsOfService = yearsOfService;
}