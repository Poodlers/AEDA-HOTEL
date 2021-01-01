#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <string>
#include <vector>
#include <iostream>

/// Thrown if the client does not have any reservations to check in.
class NoReservationsToCheckIn{
private:
    /// Name of client.
    std::string name;
    /// NIF of client.
    unsigned int NIF;
public:

    /// Constructor.
    ///
    /// \param name name of the client
    /// \param NIF NIF of the client
    NoReservationsToCheckIn (const std::string& name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }

    /// Returns NIF.
    ///
    /// \return NIF
    unsigned int getNIF() const {return NIF;}

    /// Returns name.
    ///
    /// \return name.
    std::string getName() const {return name;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const NoReservationsToCheckIn& exception){
        return o << exception.getName() << " with NIF: " << exception.getNIF() << " doesn't have any reservations to check in."<<std::endl;
    }
};

/// Thrown if client has no reservations to check out.
class NoReservationsToCheckOut{
private:
    /// Name of client.
    std::string name;
    /// NIF of client.
    unsigned int NIF;
public:

    /// Constructor.
    ///
    /// \param name name of the client
    /// \param NIF NIF of the client
    NoReservationsToCheckOut (const std::string& name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }

    /// Returns NIF.
    ///
    /// \return NIF
    unsigned int getNIF() const {return NIF;}

    /// Returns name.
    ///
    /// \return name
    std::string getName() const {return name;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const NoReservationsToCheckOut& exception){
        return o << exception.getName() << " with NIF: " << exception.getNIF() << " doesn't have any reservations to check out."<<std::endl;
    }
};

/// Thrown when a reservation has an invalid date.
class ReservationHasInvalidDates{
public:
    /// Constructor.
    ReservationHasInvalidDates (){}


    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const ReservationHasInvalidDates& exception){
        return o << "Check Out date can't be before Check In date."<<std::endl;
    }
};

class CantMakeNewResevOldResev{
public:
    /// Constructor.
    CantMakeNewResevOldResev (){}
    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const CantMakeNewResevOldResev& exception){
        return o << "Can't turn a Future Reservation into a Past one!"<<std::endl;
    }
};

/// Thrown when a client tries to claim a room that is already claimed for the intended period of time.
class AnotherReservationForThisRoomAlreadyExistsAtThisTime{
private:
    /// Room id of repeated reservation.
    int roomId;
public:
    /// Constructor.
    ///
    /// \param roomId room id of repeated reservation.
    AnotherReservationForThisRoomAlreadyExistsAtThisTime(const int& roomId){
        this->roomId = roomId;
    }

    /// Return room ID.
    ///
    /// \return room id of repeated reservation.
    int getRoomId() const {return roomId;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const AnotherReservationForThisRoomAlreadyExistsAtThisTime& exception){
        return o << "Room with Id: "<< exception.getRoomId() << " already has a reservation at this time."<<std::endl;
    }
};

/// Thrown when trying to add a vehicle with an already existing plate.
class VehicleAlreadyExists{
private:
    /// Plate of repeated vehicle.
    std::string plate;
public:
    /// Constructor.
    ///
    /// \param plate plate of repeated vehicle
    VehicleAlreadyExists(const std::string& plate){
        this->plate = plate;
    }

    /// Return plate of repeated vehicle.
    ///
    /// \param plate plate of repeated vehicle
    std::string getPlate() const {return plate;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const VehicleAlreadyExists& exception){
        return o << "Vehicle with plate: "<< exception.getPlate() << " already exists."<<std::endl;
    }
};

/// Thrown when trying to create vehicle with invalid plate.
class InvalidPlate{
private:
    /// Invalid plate.
    std::string plate;
public:
    /// Constructor.
    ///
    /// \param plate invalid plate
    InvalidPlate(const std::string& plate){
        this->plate = plate;
    }

    /// Return the invalid plate.
    ///
    /// \param plate invalid plate
    std::string getPlate() const{
        return this->plate;
    }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const InvalidPlate& exception){
        return o << "Plate : "<< exception.getPlate() << " is not a valid plate."<<std::endl;
    }
};


/// Thrown when input is not an integer.
class NotAnInt{
private:
    /// Description of the input.
    std::string msg;
public:
    /// Constructor.
    ///
    /// \param msg description of the input.
    NotAnInt(const std::string& msg){this->msg = msg;}

    /// Returns description.
    ///
    /// \return description of the input.
    std::string getMsg() const{
        return msg;
    }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, NotAnInt& exception){
        return o << exception.getMsg() << " should be an integer."<<std::endl;
    }
};

/// Thrown when input is not a positive integer.
class NotAPositiveInt{
private:
    /// Description of the input.
    std::string msg;
public:
    /// Constructor.
    ///
    /// \param msg description of the input.
    NotAPositiveInt(const std::string& msg){this->msg = msg;}

    /// Returns description.
    ///
    /// \return description of the input.
    std::string getMsg() const{
        return msg;
    }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, NotAPositiveInt& exception){
        return o << exception.getMsg() << " should be an integer."<<std::endl;
    }
};

/// Thrown if the input is not a float bigger than 0
class NotAPositiveFloat{
private:
    /// Description of the input.
    std::string msg;
public:
    /// Constructor
    ///
    /// \param msg - value that is not a positive float
    NotAPositiveFloat(const std::string& msg){this->msg = msg;}

    /// Returns description.
    ///
    /// \return description of the input.
    std::string getMsg() const{
        return msg;
    }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, NotAPositiveFloat& exception){
        return o << exception.getMsg() << " should be a positive float."<<std::endl;
    }
};

class InvalidInput{
public:
    /// Constructor
    InvalidInput(){}
    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, InvalidInput& exception){
        return o << "Input is not valid."<< std::endl;
    }
};

/// Thrown if room type is not valid (valid : "Suite", "NoViewRoom" or "ViewRoom").
class InvalidRoomType{
private:
    /// ID of the room with an invalid room type.
    unsigned int Id;
    /// Invalid room type.
    std::string type;

public:
    /// Constructor.
    ///
    /// \param Id  id of the room with an invalid room type.
    /// \param type  invalid room type.
    InvalidRoomType(const unsigned int &Id, const std::string& type){
        this->Id = Id;
        this->type = type;
    }

    /// Return ID.
    ///
    /// \return id of the room with an invalid room type.
    unsigned int getId() const{ return this->Id; }
    ///
    /// \return invalid room type.
    std::string  getType() const{ return this->type; }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, InvalidRoomType& exception){
        return o << "Room with Id " << exception.getId() << " has the invalid type "<< exception.getType()<< ". Type must be 'Suite', 'ViewRoom' or 'NoViewRoom'."<< std::endl;
    }
};

/// Thrown if staff type is not valid (valid: "Manager", "Janitor", "Receptionist" or "Responsible").
class InvalidPosition{
private:
    /// Invalid position.
    std::string type;
    /// Name of the staff member with an invalid position.
    std::string name;
public:
    /// Constructor.
    ///
    /// \param type  invalid position.
    /// \param name  name of the staff member with an invalid position.
    InvalidPosition(const std::string& type,const std::string& name){
        this->type = type;
        this->name = name;
    }

    /// Return position.
    ///
    /// \return invalid position.
    std::string getType() const{ return this->type; }

    /// Return Name.
    ///
    /// \return name of the staff member with an invalid position.
    std::string getName() const {return this->name;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, InvalidPosition& exception){
        return o << "Staff member " << exception.getName() << " has the invalid position "<< exception.getType()<< ". Position must be 'Receptionist', 'Responsible', 'Janitor' or 'Manager'."<< std::endl;
    }
};

/// Thrown if there's a sorting error (criteria or order is wrong).
class SortingError{
public:
    /// Constructor.
    SortingError(){}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, SortingError& exception){
       return o << "Sorting criteria or order is incorrect."<<std::endl;
    }
};

/// Thrown if the selected floor does not exist.
class FloorDoesNotExist{
private:
    /// Floor that doesn't exist.
    unsigned int floor;
public:
    /// Constructor
    ///
    /// \param floor  floor that doesn't exist.
    FloorDoesNotExist(const unsigned int &floor){ this->floor = floor; }

    /// Returns floor.
    ///
    /// \return floor that doesn't exist.
    unsigned int getFloor() const{ return this->floor; }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, FloorDoesNotExist& exception){
        return o << exception.getFloor() <<" does not exist."<<std::endl;
    }
};

/// Thrown if you try to add a new staff member with the same NIF and name as an already existing staff member.
class StaffMemberAlreadyExists{
private:
    /// Name of repeated staff member.
    std::string name;
    /// NIF of repeated staff member.
    unsigned int NIF;
public:
    /// Constructor.
    ///
    /// \param name  name of repeated staff member.
    /// \param NIF  NIF of repeated staff member.
    StaffMemberAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }

    /// Returns name.
    ///
    /// \return name of repeated staff member.
    std::string getName() const{ return this->name; }

    /// Returns NIF.
    ///
    /// \return NIF of repeated staff member.
    unsigned int getNIF() const{ return this->NIF; }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, StaffMemberAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " already exists."<<std::endl;
    }
};

/// Thrown if you try to search for a staff member that does not exist.
class StaffMemberDoesNotExist{
private:
    /// Name of staff member who doesn't exist.
    std::string name;
    /// NIF of staff member who doesn't exist.
    unsigned int NIF;
public:
    /// Constructor.
    ///
    /// \param name  name of staff member who doesn't exist.
    /// \param NIF  NIF of staff member who doesn't exist.
    StaffMemberDoesNotExist(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }

    /// Returns name.
    ///
    /// \return name of staff member who doesn't exist.
    std::string getName() const{ return this->name; }

    /// Returns NIF
    ///
    /// \return name of staff member who doesn't exist.
    unsigned int getNIF() const{ return this->NIF; }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, StaffMemberDoesNotExist& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " is not in the list of staff members."<<std::endl;
    }
};

/// Thrown if you try to add a new staff member to the program with a NIF that one other staff member already has.
class StaffMemberWithThisNIFAlreadyExists{
private:
    /// Name of staff member with repeated NIF.
    std::string name;
    /// Repeated NIF.
    unsigned int NIF;
public:
    /// Constructor
    ///
    /// \param name  name of staff member with repeated NIF.
    /// \param NIF  repeated NIF.
    StaffMemberWithThisNIFAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }

    /// Returns name.
    ///
    /// \return name of staff member with repeated NIF.
    std::string getName() const{ return this->name; }

    /// Returns NIF.
    ///
    /// \return repeated NIF.
    unsigned int getNIF() const{ return this->NIF; }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, StaffMemberWithThisNIFAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " exists under a different name."<<std::endl;
    }
};


/// Thrown if you try to initialize a Janitor with a shift different from "day" or "night".
class InvalidShift{
public:
    /// Constructor
    InvalidShift(){};

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, InvalidShift& exception){
        return o << "Shift must be night or day;"<<std::endl;
    }
};

/// Thrown if you try to initialize a Client with the same name and NIF as an already existing client.
class ClientAlreadyExists{
private:
    /// Name of repeated client.
    std::string name;
    /// NIF of repeated client.
    unsigned int NIF;
public:

    /// Constructor.
    ///
    /// \param name  name of repeated client.
    /// \param NIF  NIF of repeated client.
    ClientAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    /// Returns name.
    ///
    /// \return name of repeated client.
    std::string getName() const{ return this->name; }

    /// Returns NIF.
    ///
    /// \return NIF of repeated client.
    unsigned int getNIF() const{ return this->NIF; }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, ClientAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " already exists."<<std::endl;
    }
};

/// Thrown if you search for a client who doesn't exist.
class ClientDoesNotExist{
private:
    /// Name of client who doesn't exist.
    std::string name = "";
    /// NIF of client who doesn't exist.
    unsigned int NIF;
public:
    /// Constructor.
    ///
    /// \param name  name of client who doesn't exist.
    /// \param NIF  NIF of client who doesn't exist.
    ClientDoesNotExist(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }

    /// Returns name.
    ///
    /// \return name of client who doesn't exist
    std::string getName() const{ return this->name; }

    /// Returns NIF.
    ///
    /// \return NIF of client who doesn't exist
    unsigned int getNIF() const{ return this->NIF; }


    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, ClientDoesNotExist& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " is not in the list of clients."<<std::endl;
    }
};

/// Thrown if you try to add a new Client with a NIF of an already existent client.
class ClientWithThisNIFAlreadyExists{
private:
    /// Name of client with repeated NIF.
    std::string name;
    /// Repeated NIF.
    unsigned int NIF;
public:
    /// Constructor.
    ///
    /// \param name  name of client with repeated NIF.
    /// \param NIF  repeated NIF.
    ClientWithThisNIFAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }

    /// Returns name.
    ///
    /// \return name of client with repeated NIF
    std::string getName() const{ return this->name; }

    /// Returns NIF.
    ///
    /// \return repeated NIF
    unsigned int getNIF() const{ return this->NIF; }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, ClientWithThisNIFAlreadyExists& exception){
        return o << exception.getName() << " with NIF "<< exception.getNIF() << " exists under a different name."<<std::endl;
    }
};

/// Thrown if a client with no previous reservations tries to claim a suite.
class ClientCantMakeThisReservation{
public:
    /// Constructor.
    ClientCantMakeThisReservation(){};

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, ClientCantMakeThisReservation& exception){
        return o << "Client has to have reserved at least one other room before they can make a reservation for a suite."<<std::endl;
    }
};

/// Thrown if the searched Room does not exist.
class RoomDoesNotExist{
private:
    /// Number of room which doesn't exist.
    int roomNumber;
    /// ID of room which doesn't exist.
    unsigned int roomId;
public:
    /// Constructor.
    ///
    /// \param roomNumber  number of the room which doesn't exist.
    /// \param roomId  ID of room which doesn't exist.
    RoomDoesNotExist(const unsigned int &roomNumber, const unsigned int &roomId){
        this->roomNumber = roomNumber;
        this->roomId = roomId;
    }

    /// Constructor.
    ///
    /// \param roomId  ID of room which doesn't exist.
    RoomDoesNotExist(const unsigned int &roomId){
        this->roomId = roomId;
        this->roomNumber = -1;
    }

    /// Returns room number.
    ///
    /// \return number of room which doesn't exist.
    unsigned int getRoomNumber() const {return this->roomNumber;}

    /// Returns room ID.
    ///
    /// \return ID of room which doesn't  exist.
    unsigned int getRoomId() const {return this-> roomId;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, RoomDoesNotExist& exception){
        if(exception.getRoomNumber() != -1) return o << "Room with room number: "<< exception.getRoomNumber() << " and room id:"<<exception.getRoomId()<< "does not exist"<<std::endl;
        else return o << "Room with room id: "<<exception.getRoomId()<< " does not exist"<<std::endl;
    }
};

/// Thrown if the Room does not have the capacity to accommodate the desired reservation size.
class RoomDoesNotHaveTheNecessaryCapacity{
private:
    /// ID of room without necessary capacity.
    unsigned int roomId;
public:
    /// Constructor.
    ///
    /// \param roomId  ID of room without necessary capacity.
    RoomDoesNotHaveTheNecessaryCapacity(const unsigned int& roomId){
        this->roomId = roomId;
    }

    /// Returns room ID.
    ///
    /// \return ID of room without necessary capacity.
    unsigned int getRoomId() const {return this-> roomId;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, RoomDoesNotHaveTheNecessaryCapacity& exception){
        return o << "Room with room id: "<<exception.getRoomId()<< " doesn't have the necessary capacity for the reservation."<<std::endl;
    }
};

/// Thrown if the user attempts to add a new Room which already exists.
class RoomAlreadyExists{
private:
    /// Number of the repeated room.
    unsigned int roomNumber;
    /// ID of the repeated room.
    unsigned int roomId;
public:

    /// Constructor.
    ///
    /// \param roomNumber  number of the repeated room.
    /// \param roomId  ID of the repeated room.
    RoomAlreadyExists(const unsigned int &roomNumber, const unsigned int &roomId){
        this->roomNumber = roomNumber;
        this->roomId = roomId;
    }

    /// Return room number.
    ///
    /// \return number of the repeated room.
    unsigned int getRoomNumber() const {return this->roomNumber;}

    /// Return room ID.
    ///
    /// \return ID of the repeated room.
    unsigned int getRoomId() const {return this-> roomId;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, RoomAlreadyExists& exception){
        return o << "Room with room number: "<< exception.getRoomNumber() << " and room id:"<<exception.getRoomId()<< "already exist"<<std::endl;
    }
};

/// Thrown if the user attempts to edit a Room or create a new one and gives it the room ID or room number of an already existing room.
class RoomWithThisRoomIdOrRoomNumberAlreadyExists{
private:
    /// Number of the repeated room.
    unsigned int roomNumber;
    /// ID of the repeated room.
    unsigned int roomId;
    /// Type of repeated info can be "Room ID" or "Room Number".
    std::string msg;
public:
    /// Constructor.
    ///
    /// \param roomNumber  number of the repeated room.
    /// \param roomId  id of the repeated room.
    /// \param msg  type of repeated info.
    RoomWithThisRoomIdOrRoomNumberAlreadyExists(const unsigned int &roomNumber, const unsigned int &roomId, const std::string& msg){
        this->roomNumber = roomNumber;
        this->roomId = roomId;
        this->msg = msg;
    }

    /// Return room number.
    ///
    /// \return number of the repeated room.
    unsigned int getRoomNumber() const {return this->roomNumber;}

    /// Return room ID.
    ///
    /// \return id of the repeated room.
    unsigned int getRoomId() const {return this-> roomId;}

    /// Return type.
    ///
    /// \return type of repeated info.
    std::string getMsg() const {return this->msg;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
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

/// Thrown if user tries to log out when they're not currently logged in.
class NotLoggedIn{
public:
    /// Constructor
    NotLoggedIn(){}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const NotLoggedIn& exception){
        return o << "You are not logged in. Log out before you log in."<<std::endl;
    }
};

/// Thrown if user attempts to log in again if they are already logged in.
class AlreadyLoggedIn{
public:
    /// Constructor.
    AlreadyLoggedIn(){}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const AlreadyLoggedIn& exception){
        return o<<"User is already logged in. Write LogOut to log out."<<std::endl;
    }
};

/// Thrown if user fails the authentication process.
class IncorrectCredentials{
public:
    /// Constructor
    IncorrectCredentials(){}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const IncorrectCredentials& exception){
        return o<<"Password or username are incorrect."<<std::endl;
    }
};

/// Thrown if you attempt to access a section of the program that you do not have the permission to.
class AccessRestricted{
public:
    /// Constructor.
    AccessRestricted(){}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const AccessRestricted& exception){
        return o<<"Only the manager has access to this area, log in to access it."<<std::endl;
    }
};


/*PEOPLE*/
/// Thrown if you do not input a valid NIF when prompted to do so.
class NIFIsNotValid{
private:
    /// Name of person with invalid NIF.
    std::string name;
    /// Invalid NIF.
    std::string NIF;
public:
    /// Constructor.
    ///
    /// \param name  name of person with invalid NIF
    /// \param NIF  invalid NIF
    NIFIsNotValid(const std::string& name, const std::string& NIF){this->name = name;this->NIF = NIF;}

    /// Returns NIF.
    ///
    /// \return invalid NIF
    std::string getNIF() const {return NIF;}

    /// Returns Name.
    ///
    /// \return name of person with invalid NIF.
    std::string getName() const {return name;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const NIFIsNotValid& exception){
        return o << exception.getName() << "has the invalid NIF: " <<  exception.getNIF() << ". Please choose a valid NIF." <<std::endl;
    }
};


/*HOTEL-FILE*/
/// Thrown if the file you use to start the program does not exist.
class FileNotFound{
private:
    /// name of missing file
    std::string fileName;
public:

    /// Constructor.
    ///
    /// \param fileName name of missing file.
    FileNotFound(const std::string & fileName){this->fileName = fileName;}

    /// Returns file name.
    ///
    /// \return name of missing file
    std::string getFileName() const {return fileName;}


    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const FileNotFound& exception){
        return o << "File not found. Make sure that the name " << exception.getFileName() << " is spelled correctly, that it does not include .txt and that the file is in the same folder as the executable or that otherwise thw file path is written correctly (make sure none of the directories have spaces)."<<std::endl;
    }
};

/// Thrown if the initializing file has the wrong format.
class HotelFileHasWrongFormat{
private:
    /// Issue with file format.
    std::string issue;
public:
    /// Constructor.
    ///
    /// \param issue  issue with file format
    HotelFileHasWrongFormat(const std::string& issue){this->issue = issue;}

    /// Returns file format.
    ///
    /// \return issue with file format.
    std::string getIssue() const {return issue;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const HotelFileHasWrongFormat& exception){
        return     o << "File format is wrong, because " << exception.getIssue() << ". Fix the issue and try again."<<std::endl;

    }
};

/// Thrown if the a date does not have a valid format.
class DateIsNotValid{
private:
    /// Issue with date.
    std::string issue;
public:
    /// Constructor.
    ///
    /// \param issue  issue with date.
    DateIsNotValid(const std::string& issue){this->issue=issue;}

    /// Return issue.
    ///
    /// \return issue with date.
    std::string getIssue() const {return issue;}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const DateIsNotValid& exception){
        return     o << "Date is invalid, because "<< exception.getIssue()<<"."<<std::endl;

    }
};

/// Thrown when product with product ID does not exist.
class ProductDoesNotExist{
private:
    /// ID of product which doesn't exist.
    unsigned int productId;
public:
    /// Constructor.
    ///
    /// \param productId  ID of product which doesn't exist.
    ProductDoesNotExist(const unsigned int& productId){this->productId = productId;}

    /// Returns product ID.
    ///
    /// \return ID of product which doesn't exist.
    unsigned int getProductId() const{return productId;};

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const ProductDoesNotExist& exception){
        return     o << "Product with productId "<< exception.getProductId()<<" does not exist."<<std::endl;
    }
};

/// Thrown when you give a manager an evaluation that is not within bounds(1-5).
class InvalidEvaluation{
public:
    /// Constructor.
    InvalidEvaluation(){}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const InvalidEvaluation& exception){
        return     o << "Evaluation should be between 1 and 5."<<std::endl;
    }
};

/// Thrown when user tris to remove a manager.
class CantRemoveManager{
public:
    /// Constructor.
    CantRemoveManager(){};

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const CantRemoveManager& exception){
        return     o << "Can't remove manager, if you wish to replace the manager add a new manager instead."<<std::endl;
    }
};

/// Thrown if user attempts to modify a past or current reservation.
class CantChangeReservation{
public:
    ///Constructor
    CantChangeReservation(){};

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream & operator << (std::ostream& o,const CantChangeReservation& exception){
        return     o << "Only future reservations can be altered."<<std::endl;
    }
};

/// Thrown if the selected vehicle does not exist.
class VehicleDoesNotExist{
private:
    /// Plate of the vehicle that doesn't exist.
    std::string plate;
public:
    /// Constructor
    ///
    /// \param plate  plate of vehicle that doesn't exist.
    VehicleDoesNotExist(const std::string& plate){ this->plate = plate; }

    /// Returns plate.
    ///
    /// \return plate of vehicle that doesn't exist.
    std::string getPlate() const{ return this->plate; }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, VehicleDoesNotExist& exception){
        return o << "Vehicle with plate "<<exception.getPlate() << " does not exist." << std::endl;
    }
};

/// Thrown if there are no vehicles left in the fleet.
class NoVehiclesInFleet{
public:
    /// Constructor
    NoVehiclesInFleet(){}
    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, NoVehiclesInFleet& exception){
        return o << "There are no vehicles left in the fleet." << std::endl;
    }
};

/// Thrown if vehicle's kilometers travelled exceed limit.
class KmsOverLimit{
private:
    /// kilometers of travel.
    std::string kmsTravelled;
public:
    /// Constructor
    ///
    /// \param kmsTravelled  kilometers travelled.
    KmsOverLimit(std::string kmsTravelled){this->kmsTravelled = kmsTravelled;}
    /// Returns kilometers travelled.
    ///
    /// \return kilometers travelled.
    std::string getKmsTravelled() const{ return this->kmsTravelled; }
    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, KmsOverLimit& exception){
        return o << "Number of kilometers travelled (" << exception.getKmsTravelled() << ") exceeds limit."<<  std::endl;
    }
};

class NotLightweightCar{
private:
    /// invalid capacity.
    std::string capacity;
public:
    /// Constructor
    ///
    /// \param capacity  invalid capacity
    NotLightweightCar(std::string capacity){this->capacity = capacity;}
    /// Returns invalid capacity.
    ///
    /// \return invalid capacity.
    std::string getCapacity() const{ return this->capacity; }
    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, NotLightweightCar& exception){
        return o << "Capacity exceeds lightweight car's limit(" << exception.getCapacity() << ": should be lower or equal to 9)."<<  std::endl;
    }
};

/// Thrown if the searched for product does not exist
class NoSuchProductExists{
private:
    /// Name of the non existing product
    std::string prodName;
public:
    /// Constructor
    ///
    /// \param prodName the name of the non existent product Name
    NoSuchProductExists(const std::string& prodName){ this->prodName = prodName; }

    /// Returns prodName.
    ///
    /// \return name of the product that doesn't exist.
    std::string getProdName() const{ return this->prodName; }

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, NoSuchProductExists& exception){
        return o << "Product with name "<<exception.getProdName() << " does not exist." << std::endl;
    }
};

///Thrown if the manager is asked to input an initial but writes something else
class MustBeInitial{
public:
    /// Constructor
    MustBeInitial(){}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, MustBeInitial& exception){
        return o << "Input must be a single letter."<< std::endl;
    }
};

///Thrown when the user searches for a reservation that does not exist
class ReservationNotFound{
public:
    /// Constructor
    ReservationNotFound(){}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, ReservationNotFound& exception){
        return o << "There are no reservations with this characteristic."<< std::endl;
    }
};

/// Thrown if rating is invalid
class InvalidRating{
public:
    /// Constructor
    InvalidRating(){}

    /// Operator overload for <<.
    ///
    /// \param o
    /// \param exception
    /// \return ostream
    friend std::ostream& operator <<(std::ostream& o, InvalidRating& exception){
        return o << "Rating must be between 0 and 5."<< std::endl;
    }
};
#endif
