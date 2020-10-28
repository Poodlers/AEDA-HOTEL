#include "room.h"
ViewRoom :: ViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight) : Room(floor,roomNumber,roomId,capacity,pricePerNight){
}


void Suite :: activateDeactivateDiscount(){
    this->discount = !(this->discount);
}

bool ViewRoom::discount = false;