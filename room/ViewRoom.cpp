#include "room.h"
ViewRoom :: ViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight) : Room(floor,roomNumber,roomId,capacity,pricePerNight){
}


void ViewRoom :: activateDeactivateDiscount(){
    this->discount = !(this->discount);
}

bool ViewRoom::discount = false;

void ViewRoom::print(){
    std::cout<< "to make virtual";
}