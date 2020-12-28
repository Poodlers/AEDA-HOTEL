#include "vehicles.h"

Vehicle::Vehicle(std::string licensePlate, float kmsTravelled, unsigned int capacity, float price): licensePlate(licensePlate),
kmsTravelled(kmsTravelled), capacity(capacity), rented(false), price(price){

}

unsigned int Vehicle::getCapacity() const {
    return this->capacity;
}

float Vehicle::getKmsTravelled() const {
    return this->kmsTravelled;
}

std::string Vehicle::getPlate() const {
    return this->licensePlate;
}

bool Vehicle::getRented() const {
    return this->rented;
}

float Vehicle::getPrice() const {
    return this->price;
}

void Vehicle::setCapacity(const unsigned int &capacity) {
    this->capacity = capacity;
}
Vehicle::Vehicle() {}

void Vehicle::setKmsTravelled(const float &kmsTravalled) {
    this->kmsTravelled = kmsTravalled;
}

void Vehicle::setPlate(const std::string &licensePlate) {
    this->licensePlate = licensePlate;
}

void Vehicle::setRented(const bool &rented) {
    this->rented = rented;
}

void Vehicle::setPrice(const float &price) {
    this->price = price;
}

bool Vehicle::operator<(const Vehicle &v1) const{
    if(this->kmsTravelled == v1.getKmsTravelled()){
        return this->capacity < v1.getCapacity();
    }
    return this->kmsTravelled < v1.getKmsTravelled();
}

void Vehicle::addKms(const float &distance) {
    kmsTravelled += distance;
}

bool Vehicle::operator==(const Vehicle &v1) const {
    return this->licensePlate == v1.licensePlate;
}

void Vehicle::changeRented() {
    this->rented = !(this->rented);
}

std::ostream & operator << (std::ostream& o, const Vehicle& v1){
    return o << v1.licensePlate << " " << v1.kmsTravelled << " " << v1.capacity << " " << v1.price << std::endl;
}
