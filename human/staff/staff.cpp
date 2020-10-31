#include "staff.h"
#include "iostream"
/*STAFF*/

unsigned int Staff:: staffNumber = 0;

Staff::Staff(const std::string& name, const unsigned int & NIF, const float& wage): Human(name,NIF){
    this->wage = wage;
    this-> yearsOfService = 0;
    staffNumber ++;
}

float Staff::getWage() const{
    return this->wage;
}

int Staff::getYearsOfService() const {
    return this->yearsOfService;
}

void Staff::setWage(const float wage){
    this->wage = wage;
}

void Staff::setYearsOfService(const int yearsOfService){
    this->yearsOfService = yearsOfService;
}
/* ------- */

