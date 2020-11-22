#include "room.h"
#include <iostream>
#include <iomanip>
Room::Room(const int &floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight ){

    this->floor=floor;
    this->roomNumber = roomNumber;
    this->roomId = roomId;
    this->capacity = capacity;
    this->pricePerNight = pricePerNight;
}

bool Room::getAvailability() const{
    return free;
}

int Room::getFloor() const{
    return this->floor;
}
int Room::getRoomNumber() const{
    return this->roomNumber;
}
int Room::getCapacity() const{
    return this->capacity;
}
unsigned int Room::getRoomId() const{
    return this->roomId;
}
float Room::getPricePerNight() const{
    return this->pricePerNight;
}

void Room::changeAvailability(const bool& availability){
    free = availability;
}
void Room::print() {
    std::cout << std::left <<  std::setw(10) << std::setfill(' ') << this->roomId << std::setw(15)
              << this->roomNumber << std::setw(8)<< this->floor << std::setw(10) << this->capacity << std::setw(18)
              << this->pricePerNight << std::endl;
}


void Room::setAvailability(const bool& free){
    this->free = free;
}

void Room::modify(const std::string& capacity, const std::string& pricePerNight){
    if (capacity != "."){
        this->capacity = stoi(capacity);
    }
    if (pricePerNight != "."){
        this->pricePerNight = stof(pricePerNight);
    }
}

void Room::setFloor(const int &floor) {
    this->floor = floor;
}

void Room::setRoomNumber(const unsigned int &roomNumber) {
    this->roomNumber = roomNumber;
}

void Room::setRoomId(const unsigned int &roomId) {
    this->roomId = roomId;
}

void Room::setCapacity(const unsigned int &capacity) {
    this->capacity = capacity;
}

void Room::setPricePerNight(const float &pricePerNight) {
    this->pricePerNight = pricePerNight;
}
