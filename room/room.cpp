#include "room.h"
#include <iostream>
#include "../GUI/utils.h"
#include <iomanip>
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


void Room::edit() {
    std::string edit;
    std::cout << "Edit the Room's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    std::cout << "RoomNumber: " << std::endl;
    edit = GetNumberInput(14,3,CheckIfInteger);
    if (edit != ".") this->setRoomNumber(std::stoi(edit));
    gotoxy(0,5);
    std::cout << "Floor: " << std::endl;
    edit = GetNumberInput(9,5,CheckIfInteger);
    if (edit != ".") this->setFloor(std::stoi(edit));
    gotoxy(0,7);
    std::cout << "Capacity: " << std::endl;
    edit = GetNumberInput(12,7,CheckIfInteger);
    if (edit != ".") this->setCapacity(std::stoi(edit));
    gotoxy(0,9);
    std::cout << "Price per Night: " << std::endl;
    edit = GetNumberInput(20,9,CheckIfFloat);
    if (edit != ".") this->setPricePerNight(std::stof(edit));

}


void Room::print() {
    std::cout << std::left <<  std::setw(10) << std::setfill(' ') << this->roomId << std::setw(15)
              << this->roomNumber << std::setw(8)<< this->floor << std::setw(10) << this->capacity << std::setw(18)
              << this->pricePerNight << std::endl;
}