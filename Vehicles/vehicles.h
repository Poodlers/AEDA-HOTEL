#ifndef AEDA_HOTEL_PROJETO_VEHICLES_H
#define AEDA_HOTEL_PROJETO_VEHICLES_H

#include <string>

class Vehicle{
private:
    std::string licensePlate;
    float kmsTravelled;
    unsigned capacity;
public:
    Vehicle();
    Vehicle( std::string licensePlate, float kmsTravelled,unsigned capacity);
    std::string getPlate() const;
    float getKmsTravelled() const;
    unsigned getCapacity() const;
    void setPlate(const std::string& licensePlate);
    void setKmsTravelled(const float& kmsTravalled);
    void setCapacity(const unsigned& capacity);
    bool operator< (const Vehicle& v1);
};

#endif //AEDA_HOTEL_PROJETO_VEHICLES_H
