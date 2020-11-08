#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include<string>
#include<vector>
#include <iostream>

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

/* */
class NotLoggedIn{
private:
    std::string action;
public:
    NotLoggedIn(const std::string& action){this->action = action;}
    std::string getAction() const {return action;}
    friend std::ostream & operator << (std::ostream& o,const NotLoggedIn& exception);
};

std::ostream & operator << (std::ostream& o,const NotLoggedIn& exception){
    o << "The command "<< exception.getAction() << " is only available to the manager, to access this area freely, LogIn."<<std::endl;
}

/* */
class AlreadyLoggedIn{
public:
    AlreadyLoggedIn(){}
    friend std::ostream & operator << (std::ostream& o,const AlreadyLoggedIn& exception);
};
std::ostream & operator << (std::ostream& o,const AlreadyLoggedIn& exception){
    o<<"User is already logged in. Write LogOut to log out."<<std::endl;
}

/**/
class FileNotFound{
private:
    std::string fileName;
public:
    FileNotFound(const std::string & fileName){this->fileName = fileName;}
    std::string getFileName() const {return fileName;}
    friend std::ostream & operator << (std::ostream& o,const FileNotFound& exception);
};

std::ostream & operator << (std::ostream& o,const FileNotFound& exception){
    o << "File not found. Make sure that the name " << exception.getFileName() << " is spelled correctly, that it does not include .txt and that the file is in the cmake-build-debug folder.";
}

class HotelFileHasWrongFormat{
private:
    std::string issue;
public:
    HotelFileHasWrongFormat(const std::string& issue){this->issue = issue;}
    std::string getIssue() const {return issue;}
    friend std::ostream & operator << (std::ostream& o,const HotelFileHasWrongFormat& exception);
};

std::ostream & operator << (std::ostream& o,const HotelFileHasWrongFormat& exception){
    o << "File format is wrong, because " << exception.getIssue() << ". Fix the issue and try again.";

}
#endif
