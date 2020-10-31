#include "room.h"

Suite::Suite(const int &floor, const unsigned int &roomNumber ,const unsigned int &roomId, const unsigned int &capacity, const float &pricePerNight):Room(floor,roomNumber,roomId,capacity,pricePerNight){}

void Suite :: activateDeactivateDiscount(){
    this->discount = !(this->discount);
}

bool Suite::discount = false;

void Suite::print(){
    std::cout<< "to make virtual";
}