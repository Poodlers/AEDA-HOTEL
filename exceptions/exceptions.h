#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include<string>
#include<vector>
#include <iostream>
#include "../utils/utils.h"

///Thrown if the client does
class NoReservationsToCheckIn{
private:
    /// name of failed check in person
    std::string name;
    /// NIF of failed check in person
    unsigned int NIF;
public:
    ///
    /// \param name - name of failed check in person
    /// \param NIF - NIF of failed check in person
    NoReservationsToCheckIn (const std::string& name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    ///
    /// \return NIF of failed check in person
    unsigned int getNIF() const {return NIF;}
    ///
    /// \return name of failed check in person
    std::string getName() const {return name;}
    ///
    /// \param o - ostream with error message
    /// \param exception - failed check in exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const NoReservationsToCheckIn& exception){
        return o << exception.getName() << " with NIF: " << exception.getNIF() << " doesn't have any reservations to check in."<<std::endl;
    }
};

class NoReservationsToCheckOut{
private:
    /// name of failed check out person
    std::string name;
    /// NIF of failed check out person
    unsigned int NIF;
public:
    ///
    /// \param name - name of failed check out person
    /// \param NIF - NIF of failed check out person
    NoReservationsToCheckOut (const std::string& name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    ///
    /// \return NIF of failed check out person
    unsigned int getNIF() const {return NIF;}
    ///
    /// \return name of failed check out person
    std::string getName() const {return name;}
    ///
    /// \param o - ostream with error message
    /// \param exception - failed to check out exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const NoReservationsToCheckOut& exception){
        return o << exception.getName() << " with NIF: " << exception.getNIF() << " doesn't have any reservations to check out."<<std::endl;
    }
};

class ReservationHasInvalidDates{
public:
    /// invalid dates for reservation exception
    ReservationHasInvalidDates (){}
    ///
    /// \param o - ostream with error message
    /// \param exception - invalid dates for reservation exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const ReservationHasInvalidDates& exception){
        return o << "Check Out date can't be before Check In date."<<std::endl;
    }
};

class AnotherReservationForThisRoomAlreadyExistsAtThisTime{
private:
    /// room id of repeated reservation
    int roomId;
public:
    ///
    /// \param roomId room id of repeated reservation
    AnotherReservationForThisRoomAlreadyExistsAtThisTime(const int& roomId){
        this->roomId = roomId;
    }
    ///
    /// \return room id of repeated reservation
    int getRoomId() const {return roomId;}
    ///
    /// \param o - ostream with error message
    /// \param exception - reservation already made for the room exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const AnotherReservationForThisRoomAlreadyExistsAtThisTime& exception){
        return o << "Room with Id: "<< exception.getRoomId() << " already has a reservation at this time."<<std::endl;
    }
};




class NotAnInt{
private:
    /// value that is not integer
    std::string msg;
public:
    ///
    /// \param msg - value that is not integer
    NotAnInt(const std::string& msg){this->msg = msg;}
    ///
    /// \return value that is not integer
    std::string getMsg() const{
        return msg;
    }
    ///
    /// \param o - ostream with error message
    /// \param exception - not an integer exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, NotAnInt& exception){
        return o << exception.getMsg() << " should be an integer."<<std::endl;
    }
};

class NotAPositiveInt{
private:
    /// value that is not a positive integer
    std::string msg;
public:
    ///
    /// \param msg - value that is not a positive integer
    NotAPositiveInt(const std::string& msg){this->msg = msg;}
    ///
    /// \return value that is not a positive integer
    std::string getMsg() const{
        return msg;
    }
    ///
    /// \param o - ostream with error message
    /// \param exception - not a positive integer exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, NotAPositiveInt& exception){
        return o << exception.getMsg() << " should be a positive integer."<<std::endl;
    }
};

class NotAPositiveFloat{
private:
    /// value that is not a positive float
    std::string msg;
public:
    ///
    /// \param msg - value that is not a positive float
    NotAPositiveFloat(const std::string& msg){this->msg = msg;}
    ///
    /// \return value that is not a positive float
    std::string getMsg() const{
        return msg;
    }
    ///
    /// \param o - ostream with error message
    /// \param exception - not a positive float exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, NotAPositiveFloat& exception){
        return o << exception.getMsg() << " should be a positive float."<<std::endl;
    }
};

class InvalidRoomType{
private:
    /// id of the room with an invalid room type
    unsigned int Id;
    /// invalid room type
    std::string type;

public:
    ///
    /// \param Id - id of the room with an invalid room type
    /// \param type - invalid room type
    InvalidRoomType(const unsigned int &Id, const std::string& type){
        this->Id = Id;
        this->type = type;
    }
    ///
    /// \return id of the room with an invalid room type
    unsigned int getId() const{ return this->Id; }
    ///
    /// \return invalid room type
    std::string  getType() const{ return this->type; }
    ///
    /// \param o - ostream with error message
    /// \param exception - invalid room type exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, InvalidRoomType& exception){
        return o << "Room with Id " << exception.getId() << " has the invalid type "<< exception.getType()<< ". Type must be 'Suite', 'ViewRoom' or 'NoViewRoom'."<< std::endl;
    }
};

class InvalidPosition{
private:
    /// invalid position
    std::string type;
    /// name of the staff member with an invalid position
    std::string name;
public:
    ///
    /// \param type - invalid position
    /// \param name - name of the staff member with an invalid position
    InvalidPosition(const std::string& type,const std::string& name){
        this->type = type;
        this->name = name;
    }
    ///
    /// \return invalid position
    std::string getType() const{ return this->type; }
    ///
    /// \return name of the staff member with an invalid position
    std::string getName() const {return this->name;}
    ///
    /// \param o - ostream with error message
    /// \param exception - invalid position exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, InvalidPosition& exception){
        return o << "Staff member " << exception.getName() << " has the invalid position "<< exception.getType()<< ". Position must be 'Receptionist', 'Responsible', 'Janitor' or 'Manager'."<< std::endl;
    }
};

class SortingError{
public:
    /// sorting error exception
    SortingError(){}
    ///
    /// \param o - ostream with error message
    /// \param exception - sorting error exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, SortingError& exception){
       return o << "Sorting criteria or order is incorrect."<<std::endl;
    }
};

/*HOTEL*/

class FloorDoesNotExist{
private:
    /// floor that doesn't exist
    unsigned int floor;
public:
    ///
    /// \param floor - floor that doesn't exist
    FloorDoesNotExist(const unsigned int &floor){ this->floor = floor; }
    ///
    /// \return floor that doesn't exist
    unsigned int getFloor() const{ return this->floor; }
    ///
    /// \param o - ostream with error message
    /// \param exception - floor does not exist
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, FloorDoesNotExist& exception){
        return o << exception.getFloor() <<" does not exist."<<std::endl;
    }
};

/*STAFF*/

class StaffMemberAlreadyExists{
private:
    /// name of repeated staff member
    std::string name;
    /// NIF of repeated staff member
    unsigned int NIF;
public:
    ///
    /// \param name - name of repeated staff member
    /// \param NIF - NIF of repeated staff member
    StaffMemberAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    ///
    /// \return name of repeated staff member
    std::string getName() const{ return this->name; }
    ///
    /// \return NIF of repeated staff member
    unsigned int getNIF() const{ return this->NIF; }
    ///
    /// \param o - ostream with error message
    /// \param exception - staff member already exists exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, StaffMemberAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " already exists."<<std::endl;
    }
};

class StaffMemberDoesNotExist{
private:
    /// name of staff member who doesn't exist
    std::string name;
    /// NIF of staff member who doesn't exist
    unsigned int NIF;
public:
    ///
    /// \param name - name of staff member who doesn't exist
    /// \param NIF - NIF of staff member who doesn't exist
    StaffMemberDoesNotExist(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    ///
    /// \return name of staff member who doesn't exist
    std::string getName() const{ return this->name; }
    ///
    /// \return name of staff member who doesn't exist
    unsigned int getNIF() const{ return this->NIF; }
    ///
    /// \param o - ostream with error message
    /// \param exception - staff member does not exist exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, StaffMemberDoesNotExist& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " is not in the list of staff members."<<std::endl;
    }
};

class StaffMemberWithThisNIFAlreadyExists{
private:
    /// name of staff member with repeated NIF
    std::string name;
    /// repeated NIF
    unsigned int NIF;
public:
    ///
    /// \param name - name of staff member with repeated NIF
    /// \param NIF - repeated NIF
    StaffMemberWithThisNIFAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    ///
    /// \return name of staff member with repeated NIF
    std::string getName() const{ return this->name; }
    ///
    /// \return repeated NIF
    unsigned int getNIF() const{ return this->NIF; }
    ///
    /// \param o - ostream with error message
    /// \param exception - repeated NIF exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, StaffMemberWithThisNIFAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " exists under a different name."<<std::endl;
    }
};

class ManagerAlreadyExists{
private:
    /// name of repeated manager
    std::string name;
    /// NIF of repeated manager
    unsigned int NIF;
public:
    ///
    /// \param name - name of repeated manager
    /// \param NIF - NIF of repeated manager
    ManagerAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    ///
    /// \return name of repeated manager
    std::string getName() const{ return this->name; }
    ///
    /// \return NIF of repeated manager
    unsigned int getNIF() const{ return this->NIF; }
    ///
    /// \param o - ostream with error message
    /// \param exception - manager already exists exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, ManagerAlreadyExists& exception){
        return o << "There already exists a manager. Name: "<<exception.getName()<<" NIF: " << exception.getNIF() <<std::endl;
    }
};

class InvalidShift{
public:
    /// invalid shift exception
    InvalidShift(){};
    ///
    /// \param o - ostream with error message
    /// \param exception - invalid shift exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, InvalidShift& exception){
        return o << "Shift must be night or day;"<<std::endl;
    }
};
/*CLIENT*/

class ClientAlreadyExists{
private:
    /// name of repeated client
    std::string name;
    /// NIF of repeated client
    unsigned int NIF;
public:
    ///
    /// \param name - name of repeated client
    /// \param NIF - NIF of repeated client
    ClientAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    ///
    /// \return name of repeated client
    std::string getName() const{ return this->name; }
    ///
    /// \return NIF of repeated client
    unsigned int getNIF() const{ return this->NIF; }
    ///
    /// \param o - ostream with error message
    /// \param exception - client already exists exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, ClientAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " already exists."<<std::endl;
    }
};

class ClientDoesNotExist{
private:
    /// name of client who doesn't exist
    std::string name;
    /// NIF of client who doesn't exist
    unsigned int NIF;
public:
    ///
    /// \param name - name of client who doesn't exist
    /// \param NIF - NIF of client who doesn't exist
    ClientDoesNotExist(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    ///
    /// \return name of client who doesn't exist
    std::string getName() const{ return this->name; }
    ///
    /// \return NIF of client who doesn't exist
    unsigned int getNIF() const{ return this->NIF; }
    ///
    /// \param o - ostream with error message
    /// \param exception - client doesn't exist exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, ClientDoesNotExist& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " is not in the list of clients."<<std::endl;
    }
};

class ClientWithThisNIFAlreadyExists{
private:
    /// name of client with repeated NIF
    std::string name;
    /// repeated NIF
    unsigned int NIF;
public:
    ///
    /// \param name - name of client with repeated NIF
    /// \param NIF - repeated NIF
    ClientWithThisNIFAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    ///
    /// \return name of client with repeated NIF
    std::string getName() const{ return this->name; }
    ///
    /// \return repeated NIF
    unsigned int getNIF() const{ return this->NIF; }
    ///
    /// \param o - ostream with error message
    /// \param exception - repeated NIF exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, ClientWithThisNIFAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " exists under a different name."<<std::endl;
    }
};

class ClientCantMakeThisReservation{
public:
    /// client can't make reservation exception
    ClientCantMakeThisReservation(){};
    ///
    /// \param o - ostream with error message
    /// \param exception - client can't make reservation exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, ClientCantMakeThisReservation& exception){
        return o << "Client has to have reserved at least one other room before they can make a reservation for a suite."<<std::endl;
    }
};

/*ROOMS*/

class RoomDoesNotExist{
private:
    /// number of room which doesn't  exist
    int roomNumber;
    /// id of room which doesn't exist
    unsigned int roomId;
public:
    ///
    /// \param roomNumber - number of room which doesn't  exist
    /// \param roomId - id of room which doesn't  exist
    RoomDoesNotExist(const unsigned int &roomNumber, const unsigned int &roomId){
        this->roomNumber = roomNumber;
        this->roomId = roomId;
    }
    ///
    /// \param roomId - id of room which doesn't  exist
    RoomDoesNotExist(const unsigned int &roomId){
        this->roomId = roomId;
        this->roomNumber = -1;
    }
    ///
    /// \return number of room which doesn't  exist
    unsigned int getRoomNumber() const {return this->roomNumber;}
    ///
    /// \return id of room which doesn't  exist
    unsigned int getRoomId() const {return this-> roomId;}
    ///
    /// \param o - ostream with error message
    /// \param exception - room doesn't exist exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, RoomDoesNotExist& exception){
        if(exception.getRoomNumber() != -1) return o << "Room with room number: "<< exception.getRoomNumber() << " and room id:"<<exception.getRoomId()<< "does not exist"<<std::endl;
        else return o << "Room with room id: "<<exception.getRoomId()<< " does not exist"<<std::endl;
    }
};

class RoomDoesNotHaveTheNecessaryCapacity{
private:
    /// id of room without necessary capacity
    unsigned int roomId;
public:
    ///
    /// \param roomId - id of room without necessary capacity
    RoomDoesNotHaveTheNecessaryCapacity(const unsigned int& roomId){
        this->roomId = roomId;
    }
    ///
    /// \return id of room without necessary capacity
    unsigned int getRoomId() const {return this-> roomId;}
    ///
    /// \param o - ostream with error message
    /// \param exception - room without necessary capacity exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, RoomDoesNotHaveTheNecessaryCapacity& exception){
        return o << "Room with room id: "<<exception.getRoomId()<< " doesn't have the necessary capacity for the reservation."<<std::endl;
    }
};

class RoomAlreadyExists{
private:
    /// number of the repeated room
    unsigned int roomNumber;
    /// id of the repeated room
    unsigned int roomId;
public:
    ///
    /// \param roomNumber - number of the repeated room
    /// \param roomId - id of the repeated room
    RoomAlreadyExists(const unsigned int &roomNumber, const unsigned int &roomId){
        this->roomNumber = roomNumber;
        this->roomId = roomId;
    }
    ///
    /// \return number of the repeated room
    unsigned int getRoomNumber() const {return this->roomNumber;}
    ///
    /// \return id of the repeated room
    unsigned int getRoomId() const {return this-> roomId;}
    ///
    /// \param o - ostream with error message
    /// \param exception - room already exists exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, RoomAlreadyExists& exception){
        return o << "Room with room number: "<< exception.getRoomNumber() << " and room id:"<<exception.getRoomId()<< "already exist"<<std::endl;
    }
};

class RoomWithThisRoomIdOrRoomNumberAlreadyExists{
private:
    /// number of the repeated room
    unsigned int roomNumber;
    /// id of the repeated room
    unsigned int roomId;
    /// string with the repeated info
    std::string msg;
public:
    ///
    /// \param roomNumber - number of the repeated room
    /// \param roomId - id of the repeated room
    /// \param msg - string with the repeated info
    RoomWithThisRoomIdOrRoomNumberAlreadyExists(const unsigned int &roomNumber, const unsigned int &roomId, const std::string& msg){
        this->roomNumber = roomNumber;
        this->roomId = roomId;
        this->msg = msg;
    }
    ///
    /// \return number of the repeated room
    unsigned int getRoomNumber() const {return this->roomNumber;}
    ///
    /// \return id of the repeated room
    unsigned int getRoomId() const {return this-> roomId;}
    ///
    /// \return string with the repeated info
    std::string getMsg() const {return this->msg;}
    ///
    /// \param o - ostream with error message
    /// \param exception - room id or room number already exists exception
    /// \return ostream with error message
    friend std::ostream& operator <<(std::ostream& o, RoomWithThisRoomIdOrRoomNumberAlreadyExists& exception){
        if (exception.getMsg() == "Room Id"){
            return o << "A room exists under this room number ("<<exception.getRoomNumber()<<  ")with a different room ID" << std::endl;
        }
        else if (exception.getMsg() == "Room Number"){
            return o << "A room exists under this ID ("<<exception.getRoomId()<<  ")with a different room number" << std::endl;
        }
        return o;
    }
};

/*LOGIN*/
class NotLoggedIn{
private:
    /// command attempted
    std::string action;
public:
    ///
    /// \param action - command attempted
    NotLoggedIn(const std::string& action){this->action = action;}
    ///
    /// \return command attempted
    std::string getAction() const {return action;}
    ///
    /// \param o - ostream with error message
    /// \param exception - not logged in exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const NotLoggedIn& exception){
        return o << "The command "<< exception.getAction() << " is only available to the manager, to access this area freely or LogOut, LogIn first."<<std::endl;
    }
};

class AlreadyLoggedIn{
public:
    /// already logged in exception
    AlreadyLoggedIn(){}
    ///
    /// \param o - ostream with error message
    /// \param exception - already logged in exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const AlreadyLoggedIn& exception){
        return o<<"User is already logged in. Write LogOut to log out."<<std::endl;
    }
};

class IncorrectCredentials{
public:
    /// incorrect credentials exception
    IncorrectCredentials(){}
    ///
    /// \param o - ostream with error message
    /// \param exception - incorrect credentials exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const IncorrectCredentials& exception){
        return o<<"Password or username are incorrect."<<std::endl;
    }
};

class AccessRestricted{
public:
    /// access restricted exception
    AccessRestricted(){}
    ///
    /// \param o - ostream with error message
    /// \param exception - exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const AccessRestricted& exception){
        return o<<"Only the manager has access to this area, log in to access it."<<std::endl;
    }
};


/*PEOPLE*/
class NIFIsNotValid{
private:
    /// name of person with invalid NIF
    std::string name;
    /// invalid NIF
    std::string NIF;
public:
    ///
    /// \param name - name of person with invalid NIF
    /// \param NIF - invalid NIF
    NIFIsNotValid(const std::string& name, const std::string& NIF){this->name = name;this->NIF = NIF;}
    ///
    /// \return invalid NIF
    std::string getNIF() const {return NIF;}
    ///
    /// \return name of person with invalid NIF
    std::string getName() const {return name;}
    ///
    /// \param o - ostream with error message
    /// \param exception - invalid NIF exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const NIFIsNotValid& exception){
        return o << exception.getName() << "has the invalid NIF: " <<  exception.getNIF() << ". Please choose a valid NIF." <<std::endl;
    }
};


/*HOTEL-FILE*/
class FileNotFound{
private:
    /// name of unfound file
    std::string fileName;
public:
    ///
    /// \param fileName - name of unfound file
    FileNotFound(const std::string & fileName){this->fileName = fileName;}
    ///
    /// \return name of unfound file
    std::string getFileName() const {return fileName;}
    ///
    /// \param o - ostream with error message
    /// \param exception - file not found exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const FileNotFound& exception){
        return o << "File not found. Make sure that the name " << exception.getFileName() << " is spelled correctly, that it does not include .txt and that the file is in the same folder as the executable or that otherwise thw file path is written correctly (make sure none of the directories have spaces)."<<std::endl;
    }
};

class HotelFileHasWrongFormat{
private:
    /// issue with file format
    std::string issue;
public:
    ///
    /// \param issue - issue with file format
    HotelFileHasWrongFormat(const std::string& issue){this->issue = issue;}
    ///
    /// \return issue with file format
    std::string getIssue() const {return issue;}
    ///
    /// \param o - ostream with error message
    /// \param exception - hotel file has wrong format exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const HotelFileHasWrongFormat& exception){
        return     o << "File format is wrong, because " << exception.getIssue() << ". Fix the issue and try again."<<std::endl;

    }
};

class DateIsNotValid{
private:
    /// issue with date
    std::string issue;
public:
    ///
    /// \param issue - issue with date
    DateIsNotValid(const std::string& issue){this->issue=issue;}
    ///
    /// \return issue with date
    std::string getIssue() const {return issue;}
    ///
    /// \param o - ostream with error message
    /// \param exception - date isn't valid exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const DateIsNotValid& exception){
        return     o << "Date is invalid, because "<< exception.getIssue()<<"."<<std::endl;

    }
};


class ProductDoesNotExist{
private:
    /// id of product which doesn't exist
    unsigned int productId;
public:
    ///
    /// \param productId - id of product which doesn't exist
    ProductDoesNotExist(const unsigned int& productId){this->productId = productId;}
    ///
    /// \return id of product which doesn't exist
    unsigned int getProductId() const{return productId;};
    ///
    /// \param o - ostream with error message
    /// \param exception - product doesn't exist exception
    /// \return ostream with error message
    friend std::ostream & operator << (std::ostream& o,const ProductDoesNotExist& exception){
        return     o << "Product with productId "<< exception.getProductId()<<" does not exist."<<std::endl;
    }
};

class InvalidEvaluation{
public:
    InvalidEvaluation(){}
    friend std::ostream & operator << (std::ostream& o,const InvalidEvaluation& exception){
        return     o << "Evaluation should be between 1 and 5."<<std::endl;
    }
};
#endif
