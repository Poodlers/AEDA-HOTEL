#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../hotel/reservation.h"
#include "../exceptions/exceptions.h"

class Room{
public:
    /// Room constructor
    ///
    /// \param floor - floor of the room
    /// \param roomNumber - number of the room
    /// \param roomId - id of the room
    /// \param capacity - room's capacity
    /// \param pricePerNight - room's price per night
    Room(const int &floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight );
    ///
    /// \return room's floor
    int getFloor() const;
    ///
    /// \return number of the room
    int getRoomNumber() const;
    ///
    /// \return room's capacity
    int getCapacity() const;
    ///
    /// \return room's price per night
    float getPricePerNight() const;
    ///
    /// \return id of the room
    unsigned int getRoomId() const;

    ///Checks if the room is available
    ///
    /// \return availability of the room: true means the room is free; false means otherwise
    bool getAvailability() const;
    ///
    virtual void toggleDiscount() = 0;
    ///
    virtual bool getDiscountState() const = 0;
    ///
    /// \param floor - floor of the room
    void setFloor(const int floor);
    ///
    /// \param roomNumber - number of the room
    void setRoomNumber(const unsigned int roomNumber);
    ///
    /// \param capacity - room's capacity
    void setCapacity(const unsigned int capacity);
    ///
    /// \param pricePerNight - room's price per night
    void setPricePerNight(const float pricePerNight);
    ///
    /// \param free - new state of room's availability
    void changeAvailability(const bool& free);

    ///Modifies the rooms capacity and/ot pricePerNight
    ///
    /// \param capacity - room's capacity in string form
    /// \param pricePerNight - room's price per night in string form
    void modify(const std::string& capacity, const std::string& pricePerNight);
    ///
    virtual void print() = 0;
    ///
    /// \return
    virtual std::string getType() = 0;

private:
    /// room's floor
    int floor;
    /// room's number
    unsigned int roomNumber;
    /// room's id
    unsigned int roomId;
    /// room's capacity
    unsigned int capacity;
    /// room's base price per night
    float pricePerNight;
    /// room's availability
    bool free = true;
};

class Suite: public Room{
public:
    ///
    /// \param floor - suite's floor
    /// \param roomNumber - suite's room number
    /// \param roomId - suite's id
    /// \param capacity - suite's capacity
    /// \param pricePerNight - suite's price per night
    Suite(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);
    ///
    void print() override;
    /// changes discount value
    void toggleDiscount() override;
    ///
    /// \return true if discount is active; false otherwise
    bool getDiscountState() const override;
    ///
    /// \return value of the possible discount
    float getDiscountValue() const;
    ///
    /// \return "Suite"
    std::string getType() override;

private:
    /// discount is true if a discount is to be applied
    bool discount;
    /// discount value
    const float discountValue = 0.05;
};

class ViewRoom: public Room{
public:
    ///
    /// \param floor - view room's floor
    /// \param roomNumber - view room's number
    /// \param roomId - view room's id
    /// \param capacity - view room's capacity
    /// \param pricePerNight - view room's price per night
    ViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);
    ///
    void print() override;
    /// changes discount value
    void toggleDiscount() override;
    ///
    /// \return true if discount is active; false otherwise
    bool getDiscountState() const override;
    ///
    /// \return value of the possible discount
    float getDiscountValue() const;
    ///
    /// \return "ViewRoom"
    std::string getType() override;

private:
    /// discount is true if a discount is to be applied
    bool discount;
    /// discount value
    const float discountValue = 0.08;
};

class NoViewRoom: public Room{
public:
    ///
    /// \param floor - floor of the room
    /// \param roomNumber - number of the room
    /// \param roomId - id of the room
    /// \param capacity - room's capacity
    /// \param pricePerNight - room's price per night
    NoViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);
    ///
    void print() override;
    /// changes discount value
    void toggleDiscount() override;
    ///
    /// \return true if discount is active; false otherwise
    bool getDiscountState() const override;
    ///
    /// \return value of the possible discount
    float getDiscountValue() const;
    ///
    /// \return "NoViewRoom"
    std::string getType() override;


private:
    /// discount is true if a discount is to be applied
    bool discount;
    /// discount value
    const float discountValue = 0.12;
};

#endif