#include "staff.h"

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