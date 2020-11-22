#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../hotel/reservation.h"
#include "../exceptions/exceptions.h"

/// \class Room
/// Class which represents a Room.
///
/// Defined by floor, roomNumber, roomId, capacity, availability and price per night.
class Room{
public:
    /// Room constructor
    ///
    /// \param floor  floor of the room.
    /// \param roomNumber  number of the room.
    /// \param roomId  ID of the room.
    /// \param capacity  room's capacity.
    /// \param pricePerNight  room's price per night.
    Room(const int &floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight );

    /// Returns floor.
    ///
    /// \return room's floor.
    int getFloor() const;

    /// Returns room number.
    ///
    /// \return number of the room.
    int getRoomNumber() const;

    /// Returns capacity.
    ///
    /// \return room's capacity.
    int getCapacity() const;

    /// Returns price per night.
    ///
    /// \return room's price per night.
    float getPricePerNight() const;

    /// Returns ID.
    ///
    /// \return id of the room.
    unsigned int getRoomId() const;

    /// Checks if the room is available.
    ///
    /// \return availability of the room: true means the room is free; false means otherwise.
    bool getAvailability() const;

    /// Abstract.
    virtual void toggleDiscount() = 0;
    /// Abstract.
    virtual bool getDiscountState() const = 0;

    /// change floor
    ///
    /// \param floor  new floor
    void setFloor(const int &floor);

    /// change room number
    ///
    /// \param roomNumber
    void setRoomNumber(const unsigned int &roomNumber);

    /// change room id
    ///
    /// \param roomId  new room id
    void setRoomId(const unsigned int &roomId);

    /// change capacity
    ///
    /// \param capacity  new capacity
    void setCapacity(const unsigned int &capacity);

    /// change price per night
    ///
    /// \param pricePerNight  new price per night
    void setPricePerNight(const float &pricePerNight);

    /// Change availability.
    ///
    /// \param free  new state of room's availability.
    void setAvailability(const bool& free);

    /// Modifies rooms capacity and/or pricePerNight.
    ///
    /// \param capacity  room's capacity.
    /// \param pricePerNight  room's price per night.
    void modify(const std::string& capacity, const std::string& pricePerNight);

    /// Abstract.
    virtual float getDiscountValue() const = 0;

    /// Abstract.
    virtual void print() = 0;

    /// Abstract.
    virtual std::string getType() = 0;

    /// Changes room availability.
    void changeAvailability(const bool& availability);

private:
    /// Room's floor.
    int floor;
    /// Room's number.
    unsigned int roomNumber;
    /// Room's ID.
    unsigned int roomId;
    /// Room's capacity.
    unsigned int capacity;
    /// Room's base price per night.
    float pricePerNight;
    /// Room's availability.
    bool free = true;
};

/// \class Suite
/// Class which represents a Suite.
///
///
/// Defined by floor, roomNumber, roomId, capacity, availability and price per night by inheritance from room and its specific discount.
class Suite: public Room{
public:

    /// Suite Constructor.
    ///
    /// \param floor  suite's floor.
    /// \param roomNumber  suite's room number.
    /// \param roomId  suite's ID.
    /// \param capacity  suite's capacity.
    /// \param pricePerNight  suite's price per night.
    Suite(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);

    /// Prints Suite in format:
    ///
    /// Suite roomId roomNumber capacity pricePerNight availability
    void print() override;

    /// Activates/Deactivates discount.
    void toggleDiscount() override;

    /// Returns if discount is activated.
    ///
    /// \return true if discount is active, false otherwise.
    bool getDiscountState() const override;

    /// Returns the discount value.
    ///
    /// \return value of the possible discount.
    float getDiscountValue() const override;

    /// changes discount state
    ///
    /// \param discount  new discount state
    void setDiscountState(const bool &discount);

    /// Returns room type.
    ///
    /// \return "Suite".
    std::string getType() override;

private:
    /// Discount is true if a discount is applied.
    bool discount;
    /// Discount value.
    const float discountValue = 0.05;
};

/// \class ViewRoom
/// Class which represents a room with a view (ViewRoom).
///
///
/// Defined by floor, roomNumber, roomId, capacity, availability and price per night by inheritance from room and its specific discount.
class ViewRoom: public Room{
public:

    /// Suite constructor.
    ///
    /// \param floor  view room's floor.
    /// \param roomNumber  view room's number.
    /// \param roomId  view room's ID.
    /// \param capacity  view room's capacity.
    /// \param pricePerNight  view room's price per night.
    ViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);

    /// Prints ViewRoom in format:
    ///
    /// ViewRoom roomId roomNumber capacity pricePerNight availability
    void print() override;

    /// Activates/Deactivates discount.
    void toggleDiscount() override;

    /// Returns if discount is activated.
    ///
    /// \return true if discount is active, false otherwise.
    bool getDiscountState() const override;

    /// Returns the discount value.
    ///
    /// \return value of the possible discount.
    float getDiscountValue() const override;

    /// changes discount state
    ///
    /// \param discount  new discount state
    void setDiscountState(const bool &discount);

    /// Returns room type.
    ///
    /// \return "ViewRoom".
    std::string getType() override;
private:
    /// Discount is true if a discount is applied.
    bool discount;
    /// Discount value.
    const float discountValue = 0.08;
};

/// \class NoViewRoom
/// Class which represents a room without a view (NoViewRoom).
///
///
/// Defined by floor, roomNumber, roomId, capacity, availability and price per night by inheritance from room and its specific discount.
class NoViewRoom: public Room{
public:
    /// NoViewRoom constructor
    ///
    /// \param floor  floor of the room.
    /// \param roomNumber  number of the room.
    /// \param roomId  ID of the room.
    /// \param capacity  room's capacity.
    /// \param pricePerNight  room's price per night.
    NoViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);

    /// Prints NoViewRoom in format:
    ///
    /// ViewRoom roomId roomNumber capacity pricePerNight availability
    void print() override;

    /// Activates/Deactivates discount.
    void toggleDiscount() override;

    /// Returns if discount is activated.
    ///
    /// \return true if discount is active, false otherwise.
    bool getDiscountState() const override;

    /// Returns the discount value.
    ///
    /// \return value of the possible discount.
    float getDiscountValue() const override;

    /// changes discount state
    ///
    /// \param discount  new discount state
    void setDiscountState(const bool &discount);

    /// Returns room type.
    ///
    /// \return "NoViewRoom".
    std::string getType() override;

private:
    /// Discount is true if a discount is applied.
    bool discount;
    /// Discount value.
    const float discountValue = 0.12;
};

#endif