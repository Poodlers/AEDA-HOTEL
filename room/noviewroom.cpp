#include "room.h"
#include <iomanip>

NoViewRoom :: NoViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight) : Room(floor,roomNumber,roomId,capacity,pricePerNight){
}

void NoViewRoom :: activateDeactivateDiscount(){
    this->discount = !(this->discount);
}

bool NoViewRoom::discount = false;

void NoViewRoom::print(){
    std::cout << std::left <<  std::setw(10) << std::setfill(' ') << this->getRoomId() << std::setw(15)
              << this->getRoomNumber() << std::setw(8)<< this->getFloor() << std::setw(10) << this->getCapacity() << std::setw(18)
              << this->getPricePerNight();
    if (this->getAvailability()){
        std::cout << std::setw(10)<<"Free"<<std::endl;
    }
    else{
        std::cout <<std::setw(10)<< "Occupied"<<std::endl;
    }
    std::cout <<std::setw(10)<< "No View Room"<<std::endl;
}