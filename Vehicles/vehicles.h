#ifndef AEDA_HOTEL_PROJETO_VEHICLES_H
#define AEDA_HOTEL_PROJETO_VEHICLES_H

#include <string>
#include <iostream>

class Vehicle{
private:
    std::string licensePlate;
    float kmsTravelled, price;
    unsigned capacity;
    bool rented;
public:
    Vehicle();
    Vehicle( std::string licensePlate, float kmsTravelled,unsigned capacity, float price);
    std::string getPlate() const;
    float getKmsTravelled() const;
    unsigned getCapacity() const;
    bool getRented() const;
    float getPrice() const;
    void setPlate(const std::string& licensePlate);
    void setKmsTravelled(const float& kmsTravalled);
    void setCapacity(const unsigned& capacity);
    void setRented(const bool& rented);
    void setPrice(const float& price);
    bool operator< (const Vehicle& v1) const;
    bool operator== (const Vehicle& v1) const;
    void addKms(const float& distance);
    void changeRented();
    friend std::ostream & operator << (std::ostream& o, const Vehicle& v1);
};

#endif //AEDA_HOTEL_PROJETO_VEHICLES_H
