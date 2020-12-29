#ifndef AEDA_HOTEL_PROJETO_VEHICLES_H
#define AEDA_HOTEL_PROJETO_VEHICLES_H

#include <string>
#include <iostream>

/// Class that represents a vehicle
///
/// Defined by a license plate, the kmsTravelled by the vehicles, its price, capacity and if its already rented by someone or not
class Vehicle{
private:
    ///vehicle's license Plate
    std::string licensePlate;
    /// how many kms the vehicle has travelled
    float kmsTravelled;
    /// how much it costs to rent the car
    float price;
    /// how many people the vehicle can program
    unsigned capacity;
    /// true if its already being rented, false otherwise
    bool rented;
public:
    ///Default constructor for vehicle class
    Vehicle();
    ///Constructor for vehicle object
    ///
    /// \param licensePlate initializes licensePlate member
    /// \param kmsTravelled initializes kmsTravelled member
    /// \param capacity initializes capacity member
    /// \param price initializes price member
    Vehicle( std::string licensePlate, float kmsTravelled,unsigned capacity, float price);
    ///Returns vehicle's licensePlate
    ///
    /// \return licensePlate
    std::string getPlate() const;
    /// Returns vehicle's kmsTravelled
    ///
    /// \return kmsTravelled
    float getKmsTravelled() const;
    ///Returns the vehicle's capacity
    ///
    /// \return capacity
    unsigned getCapacity() const;
    ///Returns true if the vehicle has been rented, false otherwise
    ///
    /// \return isRented
    bool getRented() const;
    /// Returns the vehicle's price
    ///
    /// \return price
    float getPrice() const;
    /// Replaces current licensePlate by a new one
    ///
    /// \param licensePlate licensePlate that will replace the old one
    void setPlate(const std::string& licensePlate);
    ///Replaces current kmsTravelled by a new value
    ///
    /// \param kmsTravalled kmsTravelled to replace the current value
    void setKmsTravelled(const float& kmsTravalled);
    /// Replaces the current capacity by a new value
    ///
    /// \param capacity new value to replace the old capacity
    void setCapacity(const unsigned& capacity);
    ///Replaces the current rented status by a new one
    ///
    /// \param rented new rented status to replace the old one
    void setRented(const bool& rented);
    ///Replaces the old price by a new value
    ///
    /// \param price value to replace the current price value
    void setPrice(const float& price);
    ///Operator overloading for < (necessary for the Binary Search Tree)
    bool operator< (const Vehicle& v1) const;
    ///Operator overloading for ==
    ///
    /// \return True if the two vehicles are equal(they are equal if the licensePlates match), False otherwise
    bool operator== (const Vehicle& v1) const;
    ///Adds to the current kmsTravelled parameter the value specified
    ///
    /// \param distance value to be added to the kmsTravelled
    void addKms(const float& distance);
    ///Toggles the rented status
    void changeRented();
    ///Operator overloading for printing the vehicle's information
    friend std::ostream & operator << (std::ostream& o, const Vehicle& v1);
};

#endif //AEDA_HOTEL_PROJETO_VEHICLES_H
