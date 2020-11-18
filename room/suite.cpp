#include "room.h"
#include <iomanip>
#include <iostream>

Suite::Suite(const int &floor, const unsigned int &roomNumber ,const unsigned int &roomId, const unsigned int &capacity, const float &pricePerNight):Room(floor,roomNumber,roomId,capacity,pricePerNight){}

void Suite :: activateDiscount(){
    this->discount = true;
}

void Suite :: deactivateDiscount(){
    this->discount = false;
}

bool Suite::getDiscountState() const{
    return discount;
}
float Suite::getDiscountValue() const{
    return discountValue;
}

bool Suite::discount = false;

void Suite::print() {
    std::cout << std::left << std::setw(12) << "Suite" <<  std::setw(10) << std::setfill(' ') << this->getRoomId() << std::setw(15)
              << this->getRoomNumber() << std::setw(8)<< this->getFloor() << std::setw(10) << this->getCapacity() << std::setw(18)
              << this->getPricePerNight() << std::endl;
}