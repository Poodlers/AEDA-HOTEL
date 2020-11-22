#include "staff.h"
#include <iostream>
#include <iomanip>
#include "../../GUI/utils.h"

Responsible::Responsible(const std::string& name, const unsigned int & NIF, const float& wage) : Receptionist(name,NIF,wage){
    numberOfFloorsBeingMonitored = 0;
}

void Responsible::assignFloor(const unsigned int & floor){
    this->numberOfFloorsBeingMonitored ++;
    this->floorsAssigned.push_back(floor);
}

std::vector<int> Responsible::getFloorsAssigned() const {
    return this->floorsAssigned;
}

int Responsible::getNumFloorsAssigned() const {
    return this->numberOfFloorsBeingMonitored;
}

void Responsible::setFloorsAssigned(const std::vector<int> &floorsAssigned) {
    this->floorsAssigned = floorsAssigned;
    this->numberOfFloorsBeingMonitored = floorsAssigned.size();
}

void Responsible::clearAssignedFloors(){
    this->numberOfFloorsBeingMonitored = 0;
    this->floorsAssigned.clear();
}

std::string Responsible::getType() {
    return "Responsible";
}

void Responsible::print() {
    std::cout << std::left << std::setw(13) << "Responsible" <<  std::setw(20) << std::setfill(' ') << this->getName() <<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(19) << this->getYearsOfService()
              << "  " << this->getFloorsAssigned() << std::setw(8) << " " << std::setw(12) << " ";
}

void Responsible::printConsole() {
    std::cout << std::left << std::setw(13) << "Responsible" <<  std::setw(22) << std::setfill(' ') << this->getName() <<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(14) << this->getYearsOfService()
              << "  ";
    for (int floor :floorsAssigned){
        std::cout << floor << ", ";
    }
}