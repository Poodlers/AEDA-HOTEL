#include "staff.h"
#include "../../GUI/utils.h"
#include <iostream>
#include <iomanip>
Janitor ::Janitor(const bool & shift,const std::string& name, const unsigned int & NIF, const float& wage) : Staff(name,NIF,wage){
    this->shift = shift;
}

bool Janitor:: getShift() const{
    return this->shift;
}
void Janitor:: setShift(const bool& shift){
    this->shift = shift;
}

std::string Janitor::getType() {
    return "Janitor";
}
void Janitor::print() {
    std::cout << std::left << std::setw(13) << this->getType() <<  std::setw(20) << std::setfill(' ') << this->getName() <<
    std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(19) << this->getYearsOfService()
    << std::setw(19) << "" << std::setw(8) << (this->getShift()) ? "day" : "night";
}
/*
void Janitor::edit() {
    std::string edit;
    std::cout << "Edit the Janitor's information as follows: " << std::endl;
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
    gotoxy(0,11);
    std::cout << "Shift: " << std::endl;
    getStringInput(edit,7,11);
    if(edit == "day"){
        this->setShift(true);
    }else if(edit == "night"){
        this->setShift(false);
    }


}*/