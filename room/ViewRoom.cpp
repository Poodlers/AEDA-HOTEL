#include "room.h"
#include <iomanip>
#include <iostream>

ViewRoom :: ViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight) : Room(floor,roomNumber,roomId,capacity,pricePerNight){
}


void ViewRoom :: activateDiscount(){
    this->discount = true;
}

void ViewRoom :: deactivateDiscount(){
    this->discount = false;
}

bool ViewRoom::getDiscountState() const{
    return discount;
}
float ViewRoom::getDiscountValue() const{
    return discountValue;
}

bool ViewRoom::discount = false;

void ViewRoom::print() {
    std::cout << std::left << std::setw(14) << "View Room" <<  std::setw(10) << std::setfill(' ') << this->getRoomId() << std::setw(15)
              << this->getRoomNumber() << std::setw(8)<< this->getFloor() << std::setw(10) << this->getCapacity();

    if(!discount){
        std::cout<< std::setw(18)
                 << this->getPricePerNight() << " ";
    }
    else{
        std::cout << this->getPricePerNight() + this->getPricePerNight() * discountValue <<" " << discountValue*100 <<std::setw(11)<< "% Off ";
    }

    if (this->getAvailability()){
        std::cout << "Available"<<std::endl;
    }
    else{
        std::cout << "Occupied"<<std::endl;
    }
}