#include "room.h"
#include <iomanip>

NoViewRoom :: NoViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight) : Room(floor,roomNumber,roomId,capacity,pricePerNight){
}

void NoViewRoom :: activateDeactivateDiscount(){
    this->discount = !(this->discount);
}

bool NoViewRoom::discount = false;
