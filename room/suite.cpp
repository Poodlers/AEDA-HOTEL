#include "room.h"

Suite::Suite(const int &floor, const unsigned int &roomNumber ,const unsigned int &roomId, const unsigned int &capacity, const float &pricePerNight):Room(floor,roomNumber,roomId,capacity,pricePerNight){}

void Suite :: activateDeactivateDiscount(){
    this->discount = !(this->discount);
}

bool Suite::discount = false;

void Suite::print(){
    std::cout << std::left <<  std::setw(10) << std::setfill(' ') << this->getRoomId() << std::setw(15)
              << this->getRoomNumber() << std::setw(8)<< this->getFloor() << std::setw(10) << this->getCapacity() << std::setw(18)
              << this->getPricePerNight();
    if (this->getAvailability()){
        std::cout << std::setw(10)<<"Free"<<std::endl;
    }
    else{
        std::cout <<std::setw(10)<< "Occupied"<<std::endl;
    }
    std::cout <<std::setw(10)<< "Suite"<<std::endl;
}