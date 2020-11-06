#include "staff.h"
#include "../../GUI/utils.h"
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
    std::cout << std::left << std::setw(13) << this->getType() <<  std::setw(20) << std::setfill(' ') << this->getName() <<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(16) << this->getYearsOfService();

}
/*
void Staff::edit() {
    std::string edit;
    std::cout << "Edit the Staff's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    std::cout << "Name: " << std::endl;
    getStringInput(edit,6,3);
    if (edit != ".") this->setName(edit);
    gotoxy(0,5);
    std::cout << "NIF: " << std::endl;
    edit = GetNumberInput(5,5,CheckIfInteger);
    if (edit != ".") this->setNIF(std::stoi(edit));
    gotoxy(0,7);
    std::cout << "Wage: " << std::endl;
    edit = GetNumberInput(12,7,CheckIfFloat);
    if (edit != ".") this->setWage(std::stof(edit));
    gotoxy(0,9);
    std::cout << "Years of Service: " << std::endl;
    edit = GetNumberInput(20,9,CheckIfInteger);
    if (edit != ".") this->setYearsOfService(std::stoi(edit));
}

/* ------- */

