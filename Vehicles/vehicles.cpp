#include "vehicles.h"

Vehicle::Vehicle(std::string licensePlate, float kmsTravelled, unsigned int capacity): licensePlate(licensePlate),
kmsTravelled(kmsTravelled), capacity(capacity){

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

bool Vehicle::operator<(const Vehicle &v1) {
    if(this->kmsTravelled == v1.getKmsTravelled()){
        return this->capacity < v1.getCapacity();
    }
    return this->kmsTravelled < v1.getKmsTravelled();
}