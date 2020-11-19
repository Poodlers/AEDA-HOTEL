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
        Room(const int &floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight );
        int getFloor() const;
        int getRoomNumber() const;
        int getCapacity() const;
        float getPricePerNight() const;
        unsigned int getRoomId() const;
        std::vector<Reservation*> getReservations() const;
        bool getAvailability() const;
        virtual void toggleDiscount() = 0;
        virtual bool getDiscountState() const = 0;
        void addReservation(Reservation* reservation);
        void setFloor(const int floor);
        void setRoomNumber(const unsigned int roomNumber);
        void setCapacity(const unsigned int capacity);
        void setPricePerNight(const float pricePerNight);
        void changeAvailability(const bool& free);
        void modify(const std::string& capacity, const std::string& pricePerNight);
        virtual void print() = 0;
        virtual std::string getType() = 0;

private:
        int floor;
        unsigned int roomNumber;
        unsigned int roomId;
        unsigned int capacity;
        float pricePerNight; //guarda o preço-base
        bool free = true;
};

class Suite: public Room{
public:
    Suite(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);
    void print() override;
    void toggleDiscount() override;
    bool getDiscountState() const override;
    float getDiscountValue() const;
    std::string getType() override;

private:
    bool discount;
    const float discountValue = 0.05;
};

class ViewRoom: public Room{
public:
    ViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);
    void print() override;

    void toggleDiscount() override;
    bool getDiscountState() const override;
    float getDiscountValue() const;
    std::string getType() override;

private:
    bool discount;
    const float discountValue = 0.08;
};

class NoViewRoom: public Room{
public:
    NoViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);
    void print() override;
    void toggleDiscount() override;
    bool getDiscountState() const override;
    float getDiscountValue() const;
    std::string getType() override;


private:
    bool discount;
    const float discountValue = 0.12;
};

#endif