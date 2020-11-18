#include "room.h"
#include <iostream>
#include "../GUI/utils.h"
#include <iomanip>

Room::Room(){
    this->roomId = 0;
    this->roomNumber = 0;
    this->floor = 0;
    this->capacity = 0;
    this->pricePerNight = 0;
}

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


std::vector<Reservation*> Room::getReservations() const{
    return reservations;
}
void Room::addReservation(Reservation* reservation){
    reservations.push_back(reservation);
}