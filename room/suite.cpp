#include "room.h"
#include <iomanip>
#include <iostream>

Suite::Suite(const int &floor, const unsigned int &roomNumber ,const unsigned int &roomId, const unsigned int &capacity, const float &pricePerNight):Room(floor,roomNumber,roomId,capacity,pricePerNight){
    this->discount = false;
}

void Suite :: toggleDiscount(){
    this->discount = !this->discount;
}

bool Suite::getDiscountState() const{
    return discount;
}
float Suite::getDiscountValue() const{
    return discountValue;
}

std::string Suite::getType() {
    return "Suite";
}


void Suite::print() {
    std::cout << std::left << std::setw(14) << "Suite" <<  std::setw(10) << std::setfill(' ') << this->getRoomId() << std::setw(15)
              << this->getRoomNumber() << std::setw(8)<< this->getFloor() << std::setw(10) << this->getCapacity();

    if(!discount){
        std::cout<< std::setw(18)
                 << this->getPricePerNight() << " ";
    }
    else{
        std::cout << std::setw(10) << this->getPricePerNight() - this->getPricePerNight() * discountValue <<" " << std::setw(2) << discountValue*100 <<std::setw(5)<< "% Off ";
    }

    if (this->getAvailability()){
        std::cout << std::setw(9) << "Available"<<std::endl;
    }
    else{
        std::cout << std::setw(9) << "Occupied"<<std::endl;
    }
}

void Suite::setDiscountState(const bool &discount) {
    this->discount = discount;
}
