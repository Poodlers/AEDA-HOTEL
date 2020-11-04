#include "staff.h"
#include "../../GUI/utils.h"
#include <iostream>
#include <iomanip>

Responsible::Responsible(const std::string& name, const unsigned int & NIF, const float& wage) : Receptionist(name,NIF,wage){numberOfFloorsBeingMonitored = 0;}

void Responsible::assignFloor(const unsigned int & floor){
    //check if floor exists and throw exception if it doesn't

    this->numberOfFloorsBeingMonitored ++;
    this->floorsAssigned.push_back(floor);
}

 int Responsible::getNumberOfFloorsBringMonitored() const{
    return this->numberOfFloorsBeingMonitored;
};

std::vector<int> Responsible :: getFloorsAssigned() const{
    return this->floorsAssigned;
};

std::string Responsible::getType() {
    return "Responsible";
}


void Responsible::print() {
    std::cout << std::left << std::setw(12) << this->getType() <<  std::setw(20) << std::setfill(' ') << this->getName() <<
    std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(16) << this->getYearsOfService()
    << std::setw(16) << this->floorsAssigned << std::setw(7) << "";
}

void Responsible::edit() {
    std::string edit;
    std::cout << "Edit the Responsible's information as follows: " << std::endl;
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
    std::vector<int> new_floors;
    edit = " ";
    while(edit != "."){
        std::cout << "Insira um floor para monitorizar: (type '.' para parar)";
        edit = GetNumberInput(2,12,CheckIfInteger);
        this->assignFloor(std::stoi(edit));
        gotoxy(2,12);
        std::cout << "                            ";
    }

}

