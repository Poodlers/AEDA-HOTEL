#include "room.h"

int Room::getFloor() const{
    return this->floor;
}
int Room::getroomNumber() const{
    return this->roomNumber;
}
int Room::getCapacity() const{
    return this->capacity;
}
int Room::getPricePerNight() const{
    return this->pricePerNight;
}
void Room::setFloor(const int floor) {
    this->floor = floor;
}
void Room::setRoomNumber(const int roomNumber) {
    this->roomNumber = roomNumber;
}
void Room::setCapacity(const int capacity){
    this->capacity = capacity;
}
void Room::setPricePerNight(const int pricePerNight){
    this->pricePerNight = pricePerNight;
}