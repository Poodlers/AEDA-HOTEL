#include "staff.h"
#include <iostream>
#include <iomanip>

Janitor ::Janitor(const bool & shift,const std::string& name, const unsigned int & NIF, const float& wage) : Staff(name,NIF,wage){
    this->shift = shift;
}

bool Janitor:: getShift() const{
    return this->shift;
}

void Janitor::setShift(const bool &shift) {
    this->shift = shift;
}

std::string Janitor::getType() {
    return "Janitor";
}
void Janitor::print() {
    std::cout << std::left << std::setw(13) << "Janitor" <<  std::setw(20) << std::setfill(' ') << this->getName() <<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(19) << this->getYearsOfService()
              << std::setw(19) << " ";
    if (shift){
        std::cout << std::setw(8) << "day";
    }
    else{
        std::cout << std::setw(8) << "night";
    }
}

void Janitor::printConsole() {
    std::cout << std::left << std::setw(13) << "Janitor" <<  std::setw(22) << std::setfill(' ') << this->getName() <<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(14) << this->getYearsOfService()
              << std::setw(19) << " ";
    if (shift){
        std::cout << std::setw(8) << "day";
    }
    else{
        std::cout << std::setw(8) << "night";
    }
}

void Janitor::janitorModify(const std::string& name, const std::string& NIF, const std::string& wage, const std::string& shift){
    if (name != "."){
        this->name = name;
    }
    if(NIF != "."){
        this->NIF =stoi(NIF);
    }
    if(shift != "."){
        if (shift == "day"){
            this->shift = true;
        }
        else if (shift == "night"){
            this->shift = false;
        }
        else throw InvalidShift();
    }
    if (wage != "."){
        this->wage = stof(wage);
    }
}
