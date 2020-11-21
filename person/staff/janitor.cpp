#include "staff.h"
#include "../../utils/utils.h"
#include <iostream>
#include <iomanip>
Janitor ::Janitor(const bool & shift,const std::string& name, const unsigned int & NIF, const float& wage) : Staff(name,NIF,wage){
    this->shift = shift;
}

bool Janitor:: getShift() const{
    return this->shift;
}

std::string Janitor::getType() {
    return "Janitor";
}
void Janitor::printConsole() {
    std::cout << std::left << std::setw(13) << "Janitor" <<  std::setw(22) << std::setfill(' ') << this->getName() <<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(16) << this->getYearsOfService()
              << std::setw(16) << " ";
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
