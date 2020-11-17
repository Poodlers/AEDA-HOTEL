#include "room.h"
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

void ViewRoom::print(){
    std::cout << std::left <<  std::setw(10) << std::setfill(' ') << this->getRoomId() << std::setw(15)
              << this->getRoomNumber() << std::setw(8)<< this->getFloor() << std::setw(10) << this->getCapacity();
    if(this->discount){
        std::cout << this->getPricePerNight() * this->discountValue << "  " << this->discountValue *100 << "% Off!  ";
    }
    else std::cout << std::setw(20)
                   << this->getPricePerNight();

    if (this->getAvailability()){
        std::cout << std::setw(10)<<"Free";
    }
    else{
        std::cout <<std::setw(10)<< "Occupied";
    }
    std::cout <<std::setw(10)<< "View Room"<<std::endl;
}