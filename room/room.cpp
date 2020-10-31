#include "room.h"


Room::Room(const int &floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight ){
    this->floor=floor;
    this->roomNumber = roomNumber;
    this->roomId = roomId;
    this->capacity = capacity;
    this->pricePerNight = pricePerNight;
}

int Room::getFloor() const{
    return this->floor;
}
int Room::getroomNumber() const{
    return this->roomNumber;
}
int Room::getCapacity() const{
    return this->capacity;
}
float Room::getPricePerNight() const{
    return this->pricePerNight;
}
void Room::setFloor(const int floor) {
    this->floor = floor;
}
void Room::setRoomNumber(const unsigned int roomNumber) {
    this->roomNumber = roomNumber;
}
void Room::setCapacity(const unsigned int capacity){
    this->capacity = capacity;
}
void Room::setPricePerNight(const float pricePerNight){
    this->pricePerNight = pricePerNight;
}
void Room::print(){
    std::cout<< "to make virtual";
}