#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include<string>
#include<vector>
#include <iostream>
#include "../GUI/utils.h"


class NoReservationsToCheckIn{
private:
    std::string name;
    unsigned int NIF;
public:
    NoReservationsToCheckIn (const std::string& name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    unsigned int getNIF() const {return NIF;}
    std::string getName() const {return name;}
    friend std::ostream & operator << (std::ostream& o,const NoReservationsToCheckIn& exception){
        return o << exception.getName() << " with NIF: " << exception.getNIF() << " doesn't have any reservations to check in."<<std::endl;
    }
};

class NoReservationsToCheckOut{
private:
    std::string name;
    unsigned int NIF;
public:
    NoReservationsToCheckOut (const std::string& name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    unsigned int getNIF() const {return NIF;}
    std::string getName() const {return name;}
    friend std::ostream & operator << (std::ostream& o,const NoReservationsToCheckOut& exception){
        return o << exception.getName() << " with NIF: " << exception.getNIF() << " doesn't have any reservations to check out."<<std::endl;
    }
};

class ReservationHasInvalidDates{
public:
    ReservationHasInvalidDates (){}
    friend std::ostream & operator << (std::ostream& o,const ReservationHasInvalidDates& exception){
        return o << "Check Out date can't be before Check In date."<<std::endl;
    }
};

class AnotherReservationForThisRoomAlreadyExistsAtThisTime{
private:
    int roomId;
public:
    AnotherReservationForThisRoomAlreadyExistsAtThisTime(const int& roomId){
        this->roomId = roomId;
    }
    int getRoomId() const {return roomId;}
    friend std::ostream & operator << (std::ostream& o,const AnotherReservationForThisRoomAlreadyExistsAtThisTime& exception){
        return o << "Room with Id: "<< exception.getRoomId() << " already has a reservation at this time."<<std::endl;
    }
};


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


class InvalidEvaluation{
private:
    unsigned int evaluation;
public:
    InvalidEvaluation(const unsigned int & evaluation) { this->evaluation = evaluation; }
    unsigned int getEvaluation() const{ return this->evaluation; }
};




class NotAnInt{
private:
    std::string msg;
public:
    NotAnInt(const std::string& msg){this->msg = msg;}
    std::string getMsg() const{
        return msg;
    }
    friend std::ostream& operator <<(std::ostream& o, NotAnInt& exception){
        return o << exception.getMsg() << " should be an integer."<<std::endl;
    }
};

class NotAPositiveInt{
private:
    std::string msg;
public:
    NotAPositiveInt(const std::string& msg){this->msg = msg;}
    std::string getMsg() const{
        return msg;
    }
    friend std::ostream& operator <<(std::ostream& o, NotAPositiveInt& exception){
        return o << exception.getMsg() << " should be a positive integer."<<std::endl;
    }
};

class NotAPositiveFloat{
private:
    std::string msg;
public:
    NotAPositiveFloat(const std::string& msg){this->msg = msg;}
    std::string getMsg() const{
        return msg;
    }
    friend std::ostream& operator <<(std::ostream& o, NotAPositiveFloat& exception){
        return o << exception.getMsg() << " should be a positive float."<<std::endl;
    }
};

class InvalidRoomType{
private:
    unsigned int Id;
    std::string type;

public:
    InvalidRoomType(const unsigned int &Id, const std::string& type){
        this->Id = Id;
        this->type = type;
    }

    unsigned int getId() const{ return this->Id; }
    std::string  getType() const{ return this->type; }
    friend std::ostream& operator <<(std::ostream& o, InvalidRoomType& exception){
        return o << "Room with Id " << exception.getId() << " has the invalid type "<< exception.getType()<< ". Type must be 'Suite', 'ViewRoom' or 'NoViewRoom'."<< std::endl;
    }
};

class InvalidPosition{
private:
    std::string type;
    std::string name;
public:
    InvalidPosition(const std::string& type,const std::string& name){
        this->type = type;
        this->name = name;
    }

    std::string getType() const{ return this->type; }
    std::string getName() const {return this->name;}
    friend std::ostream& operator <<(std::ostream& o, InvalidPosition& exception){
        return o << "Staff member " << exception.getName() << " has the invalid position "<< exception.getType()<< ". Position must be 'Receptionist', 'Responsible', 'Janitor' or 'Manager'."<< std::endl;
    }
};

class SortingError{
public:
    SortingError(){}
    friend std::ostream& operator <<(std::ostream& o, SortingError& exception){
       return o << "Sorting criteria or order is incorrect."<<std::endl;
    }
};

/*HOTEL*/

class FloorDosNotExist{
private:
    unsigned int floor;
public:
    FloorDosNotExist(const unsigned int &floor){ this->floor = floor; }
    unsigned int getFloor() const{ return this->floor; }
    friend std::ostream& operator <<(std::ostream& o, FloorDosNotExist& exception){
        return o << exception.getFloor() <<" does not exist."<<std::endl;
    }
};

/*STAFF*/

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
    friend std::ostream& operator <<(std::ostream& o, StaffMemberAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " already exists."<<std::endl;
    }
};

class StaffMemberDoesNotExist{
private:
    std::string name;
    unsigned int NIF;
public:
    StaffMemberDoesNotExist(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    std::string getName() const{ return this->name; }
    unsigned int getNIF() const{ return this->NIF; }
    friend std::ostream& operator <<(std::ostream& o, StaffMemberDoesNotExist& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " is not in the list of staff members."<<std::endl;
    }
};

class StaffMemberWithThisNIFAlreadyExists{
private:
    std::string name;
    unsigned int NIF;
public:
    StaffMemberWithThisNIFAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    std::string getName() const{ return this->name; }
    unsigned int getNIF() const{ return this->NIF; }
    friend std::ostream& operator <<(std::ostream& o, StaffMemberWithThisNIFAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " exists under a different name."<<std::endl;
    }
};

class ManagerAlreadyExists{
private:
    std::string name;
    unsigned int NIF;
public:
    ManagerAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    std::string getName() const{ return this->name; }
    unsigned int getNIF() const{ return this->NIF; }
    friend std::ostream& operator <<(std::ostream& o, ManagerAlreadyExists& exception){
        return o << "There already exists a manager. Name: "<<exception.getName()<<" NIF: " << exception.getNIF() <<std::endl;
    }
};

class InvalidShift{
public:
    InvalidShift(){};
    friend std::ostream& operator <<(std::ostream& o, InvalidShift& exception){
        return o << "Shift must be night or day;"<<std::endl;
    }
};
/*CLIENT*/

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
    friend std::ostream& operator <<(std::ostream& o, ClientAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " already exists."<<std::endl;
    }
};

class ClientDoesNotExist{
private:
    std::string name;
    unsigned int NIF;
public:
    ClientDoesNotExist(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    std::string getName() const{ return this->name; }
    unsigned int getNIF() const{ return this->NIF; }
    friend std::ostream& operator <<(std::ostream& o, ClientDoesNotExist& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " is not in the list of clients."<<std::endl;
    }
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
    friend std::ostream& operator <<(std::ostream& o, ClientWithThisNIFAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " exists under a different name."<<std::endl;
    }
};

class ClientCantMakeThisReservation{
public:
    ClientCantMakeThisReservation(){};
    friend std::ostream& operator <<(std::ostream& o, ClientCantMakeThisReservation& exception){
        return o << "Client has to have reserved at least one other room before they can make a reservation for a suite."<<std::endl;
    }
};

/*ROOMS*/

class RoomDoesNotExist{
private:
    int roomNumber;
    unsigned int roomId;
public:
    RoomDoesNotExist(const unsigned int &roomNumber, const unsigned int &roomId){
        this->roomNumber = roomNumber;
        this->roomId = roomId;
    }
    RoomDoesNotExist(const unsigned int &roomId){
        this->roomId = roomId;
        this->roomNumber = -1;
    }
    unsigned int getRoomNumber() const {return this->roomNumber;}
    unsigned int getRoomId() const {return this-> roomId;}
    friend std::ostream& operator <<(std::ostream& o, RoomDoesNotExist& exception){
        if(exception.getRoomNumber() != -1) return o << "Room with room number: "<< exception.getRoomNumber() << " and room id:"<<exception.getRoomId()<< "does not exist"<<std::endl;
        else return o << "Room with room id: "<<exception.getRoomId()<< " does not exist"<<std::endl;
    }
};

class RoomDoesNotHaveTheNecessaryCapacity{
private:
    unsigned int roomId;
public:
    RoomDoesNotHaveTheNecessaryCapacity(const unsigned int& roomId){
        this->roomId = roomId;
    }
    unsigned int getRoomId() const {return this-> roomId;}
    friend std::ostream& operator <<(std::ostream& o, RoomDoesNotHaveTheNecessaryCapacity& exception){
        return o << "Room with room id: "<<exception.getRoomId()<< " doesn't have the necessary capacity for the reservation."<<std::endl;
    }
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
    friend std::ostream& operator <<(std::ostream& o, RoomAlreadyExists& exception){
        return o << "Room with room number: "<< exception.getRoomNumber() << " and room id:"<<exception.getRoomId()<< "already exist"<<std::endl;
    }
};

class RoomWithThisRoomIdOrRoomNumberAlreadyExists{
private:
    unsigned int roomNumber;
    unsigned int roomId;
    std::string msg;
public:
    RoomWithThisRoomIdOrRoomNumberAlreadyExists(const unsigned int &roomNumber, const unsigned int &roomId, const std::string& msg){
        this->roomNumber = roomNumber;
        this->roomId = roomId;
    }
    unsigned int getRoomNumber() const {return this->roomNumber;}
    unsigned int getRoomId() const {return this-> roomId;}
    std::string getMsg() const {return this->msg;}
    friend std::ostream& operator <<(std::ostream& o, RoomWithThisRoomIdOrRoomNumberAlreadyExists& exception){
        if (exception.getMsg() == "Room Id"){
            return o << "A room exists under this room number ("<<exception.getRoomNumber()<<  ")with a different room ID" << std::endl;
        }
        else if (exception.getMsg() == "Room Number"){
            return o << "A room exists under this ID ("<<exception.getRoomId()<<  ")with a different room number" << std::endl;
        }
    }
};

/*LOGIN*/
class NotLoggedIn{
private:
    std::string action;
public:
    NotLoggedIn(const std::string& action){this->action = action;}
    std::string getAction() const {return action;}
    friend std::ostream & operator << (std::ostream& o,const NotLoggedIn& exception){
        return o << "The command "<< exception.getAction() << " is only available to the manager, to access this area freely or LogOut, LogIn first."<<std::endl;
    }
};

class AlreadyLoggedIn{
public:
    AlreadyLoggedIn(){}
    friend std::ostream & operator << (std::ostream& o,const AlreadyLoggedIn& exception){
        return o<<"User is already logged in. Write LogOut to log out."<<std::endl;
    }
};

class IncorrectCredentials{
public:
    IncorrectCredentials(){}
    friend std::ostream & operator << (std::ostream& o,const IncorrectCredentials& exception){
        return o<<"Password or username are incorrect."<<std::endl;
    }
};

class AccessRestricted{
public:
    AccessRestricted(){}
    friend std::ostream & operator << (std::ostream& o,const AccessRestricted& exception){
        return o<<"Only the manager has access to this area, log in to access it."<<std::endl;
    }
};


/*PEOPLE*/
class NIFIsNotValid{
private:
    std::string name;
    std::string NIF;
public:
    NIFIsNotValid(const std::string& name, const std::string& NIF){this->name = name;
    this->NIF = NIF;}
    std::string getNIF() const {return NIF;}
    std::string getName() const {return name;}
    friend std::ostream & operator << (std::ostream& o,const NIFIsNotValid& exception){
        return o << exception.getName() << "has the invalid NIF: " <<  exception.getNIF() << ". Please choose a valid NIF." <<std::endl;
    }
};


/*HOTEL-FILE*/
class FileNotFound{
private:
    std::string fileName;
public:
    FileNotFound(const std::string & fileName){this->fileName = fileName;}
    std::string getFileName() const {return fileName;}
    friend std::ostream & operator << (std::ostream& o,const FileNotFound& exception){
        return     o << "File not found. Make sure that the name " << exception.getFileName() << " is spelled correctly, that it does not include .txt and that the file is in the cmake-build-debug folder."<<std::endl;
    }
};

class HotelFileHasWrongFormat{
private:
    std::string issue;
public:
    HotelFileHasWrongFormat(const std::string& issue){this->issue = issue;}
    std::string getIssue() const {return issue;}
    friend std::ostream & operator << (std::ostream& o,const HotelFileHasWrongFormat& exception){
        return     o << "File format is wrong, because " << exception.getIssue() << ". Fix the issue and try again."<<std::endl;

    }
};

class DateIsNotValid{
private:
    std::string issue;
public:
    DateIsNotValid(const std::string& issue){this->issue=issue;}
    std::string getIssue() const {return issue;}
    friend std::ostream & operator << (std::ostream& o,const DateIsNotValid& exception){
        return     o << "Date is invalid, because "<< exception.getIssue()<<"."<<std::endl;

    }
};
#endif
