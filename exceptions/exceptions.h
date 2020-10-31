#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include<string>
#include<vector>

class InvalidQualityValue{
private:
    unsigned int Id;
    unsigned int quality;
public:
    InvalidQualityValue(const unsigned int &Id, const unsigned int& quality){
        this->Id = Id;
        this->quality = quality;
    }
    unsigned int getId() const{ return this->Id; }
    unsigned int getQuality() const{ return this->quality; }
};

class StaffMemberAlreadyExists{
private:
    std::string name;
    unsigned int NIF;
public:
    StaffMemberAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    std::string getName() const{ return this->name; }
    unsigned int getNIF() const{ return this->NIF; }
};

class StaffWithThisNIFAlreadyExists{
private:
    std::string name;
    unsigned int NIF;
public:
    StaffWithThisNIFAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    std::string getName() const{ return this->name; }
    unsigned int getNIF() const{ return this->NIF; }
};

class FloorDosNotExist{
private:
    unsigned int floor;
public:
    FloorDosNotExist(const unsigned int &floor){ this->floor = floor; }
    unsigned int getFloor() const{ return this->floor; }
};

class InvalidEvaluation{
private:
    unsigned int evaluation;
public:
    InvalidEvaluation(const unsigned int & evaluation) { this->evaluation = evaluation; }
    unsigned int getEvaluation() const{ return this->evaluation; }
};

class InvalidPrice{
private:
    unsigned int Id;
    float price;
public:
    InvalidPrice(const unsigned int &Id, const float& price){
        this->Id = Id;
        this->price = price;
    }
    unsigned int getId() const{ return this->Id; }
    float getPrice() const{ return this->price; }
};

class InvalidType{
private:
    unsigned int Id;
    std::string type;
public:
    InvalidType(const unsigned int &Id, const std::string& type){
        this->Id = Id;
        this->type = type;
    }
    unsigned int getId() const{ return this->Id; }
    std::string  getType() const{ return this->type; }
};

class ClientAlreadyExists{
private:
    std::string name;
    unsigned int NIF;
public:
    ClientAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    std::string getName() const{ return this->name; }
    unsigned int getNIF() const{ return this->NIF; }
};

class ClientWithThisNIFAlreadyExists{
private:
    std::string name;
    unsigned int NIF;
public:
    ClientWithThisNIFAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    std::string getName() const{ return this->name; }
    unsigned int getNIF() const{ return this->NIF; }
};

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

#endif
