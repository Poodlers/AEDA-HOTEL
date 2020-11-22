#include "staff.h"
#include <iostream>
#include <iomanip>

/*STAFF*/

Staff::Staff(const std::string& name, const unsigned int & NIF, const float& wage): Person(name,NIF){
    this->wage = wage;
    this-> yearsOfService = 0;
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

void Staff::print() {
    std::cout << std::left << std::setw(13) << this->getType() <<  std::setw(20) << std::setfill(' ') << this->getName()<<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(19) << this->getYearsOfService()
              << std::setw(19) << " " << std::setw(8) << " " << std::setw(12) << " ";
}

void Staff::printConsole() {
    std::cout << std::left << std::setw(13) << this->getType() <<  std::setw(22) << std::setfill(' ') << this->getName()<<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(14) << this->getYearsOfService()
              << std::setw(19) << " " << std::setw(8) << " " << std::setw(12) << " ";
}


std::string Staff::getType(){
    return "Staff";
}
/* ------- */

void Staff::modifyStaffMember(const std::string& name, const std::string& NIF, const std::string& wage){
    if (name != "."){
        this->name = name;
    }
    if(NIF != "."){
        this->NIF = stoi(NIF);
    }
    if(wage != "."){
        this->wage = stof(wage);
    }
}
