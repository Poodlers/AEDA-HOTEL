#include "staff.h"
#include "../../GUI/utils.h"
#include <iostream>
#include <iomanip>

Responsible::Responsible(const std::string& name, const unsigned int & NIF, const float& wage) : Receptionist(name,NIF,wage){numberOfFloorsBeingMonitored = 0;}

Responsible::Responsible(): Receptionist() {
    this->numberOfFloorsBeingMonitored = 0;
}

void Responsible::assignFloor(const unsigned int & floor){
    //check if floor exists and throw exception if it doesn't

    this->numberOfFloorsBeingMonitored ++;
    this->floorsAssigned.push_back(floor);
}

void Responsible::clearAssignedFloors(){
    this->numberOfFloorsBeingMonitored ++;
    this->floorsAssigned.clear();
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
    std::cout << std::left << std::setw(13) << this->getType() <<  std::setw(22) << std::setfill(' ') << this->getName() <<
    std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(16) << this->getYearsOfService()
    << std::setw(16) << this->floorsAssigned << std::setw(7) << "";
}


