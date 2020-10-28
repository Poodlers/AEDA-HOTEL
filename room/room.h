#ifndef ROOM_H
#define ROOM_H
#include <string>

class RoomAlreadyExists{
private:
    unsigned int roomNumber;
    unsigned int roomId;
public:
    RoomAlreadyExists(const unsigned int &roomNumber, const unsigned int &roomId){ 
        this->roomNumber = roomNumber;
        this->roomId = roomId;
    }
    unsigned int getRoomNumber() const {return this->roomNumber;}
    unsigned int getRoomId() const {return this-> roomId;}
};

class RoomWithThisRoomIdAlreadyExists{
private:
    unsigned int roomNumber;
    unsigned int roomId;
public:
    RoomWithThisRoomIdAlreadyExists(const unsigned int &roomNumber, const unsigned int &roomId){ 
        this->roomNumber = roomNumber;
        this->roomId = roomId;
    }
    unsigned int getRoomNumber() const {return this->roomNumber;}
    unsigned int getRoomId() const {return this-> roomId;}
};

class Room{
public:
        Room(const int &floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight );
        int getFloor() const;
        int getroomNumber() const;
        int getCapacity() const;
        float getPricePerNight() const {return this->pricePerNight;} //implementar em cada classe
        
        void setFloor(const int floor);
        void setRoomNumber(const unsigned int roomNumber);
        void setCapacity(const unsigned int capacity);
        void setPricePerNight(const float pricePerNight);

protected:
        int floor;
        unsigned int roomNumber; //maneira de acessar numero de quarto a partir de roomId
        unsigned int roomId;
        unsigned int capacity;
        float pricePerNight; //guarda o preço-base
};

class Suite: public Room{
public:
    Suite(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);
    void activateDeactivateDiscount();

private:
    static bool discount;
    const float discountValue = 0.05;
};

class ViewRoom: public Room{
public:
    ViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);
    void activateDeactivateDiscount();

private:
    static bool discount;
    const float discountValue = 0.08;
};

class NoViewRoom: public Room{
public:
    NoViewRoom(const int & floor, const unsigned int & roomNumber ,const unsigned int & roomId, const unsigned int & capacity, const float &pricePerNight);
    void activateDeactivateDiscount();

private:
    static bool discount;
    const float discountValue = 0.12;
};

#endif