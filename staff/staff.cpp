#include "staff.h"
#include "iostream"
/*STAFF*/

unsigned int Staff:: staffNumber = 0;

Staff::Staff(const std::string& name, const unsigned int & NIF, const float& wage){
    //if staff member already exists raise exception
    //if staff member of different name but with same NIF already exists raise exception

    this->name = name;
    this->NIF = NIF;
    this->wage = wage;
    this-> yearsOfService = 0;
    staffNumber ++;
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

int Staff::getYearsOfService() const {
    return this->yearsOfService;
}

void Staff::setName(const std::string name){
    this->name = name;
}

void Staff::setNIF(const unsigned int NIF){
    this->NIF = NIF;
}

void Staff::setWage(const float wage){
    this->wage = wage;
}

void Staff::setYearsOfService(const int yearsOfService){
    this->yearsOfService = yearsOfService;
}

void Staff::print() const{
    std::cout<< "to use dynamic casts";
}
/* ------- */

