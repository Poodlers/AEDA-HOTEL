#include "hotel.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include "../GUI/utils.h"
#include "../exceptions/exceptions.h"

Hotel::Hotel(const std::string &hotelFile) {
    std::ifstream file;
    std::string getData;
    std::stringstream ss;
    int check;

    file.open(hotelFile +".txt");
    if(!file.is_open()){
        throw FileNotFound(hotelFile);
    }

    std::getline(file,getData);
    if (getData != "Hotel-File"){
        throw HotelFileHasWrongFormat("First line should be 'Hotel-File'");
    }
    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }

    std::getline(file,getData);
    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }
    ss << getData;
    ss >> check;
    ss.clear();
    if(ss.fail()){
        throw HotelFileHasWrongFormat("Number of floors should be an integer");
    }
    if (check < 0){
        throw HotelFileHasWrongFormat("Number of floors should be a positive integer.");
    }
    this->floors = check;

    std::getline(file,getData);
    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }
    ss << getData;
    ss >> check;
    ss.clear();
    if(ss.fail()) {
        throw HotelFileHasWrongFormat("First floor should be an integer");
    }
    this->firstFloor = check;

    std::getline(file,getData);
    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }
    if (getData != "Rooms"){
        throw HotelFileHasWrongFormat("Line should be 'Rooms'");
    }


    int floor;
    unsigned int roomNumber;
    unsigned int roomId;
    unsigned int capacity;
    float price;
    std::string type;

    while(std::getline(file,getData) && getData!="Staff"){
        ss<<getData;
        ss >> floor >> roomNumber >> roomId >> capacity>> price;
        if(ss.fail()) {
            throw HotelFileHasWrongFormat("Floor, Room Number, Room Id, capacity and price should be integers");
        }
        if (roomId < 0 || capacity<=0 || price <= 0){
            throw HotelFileHasWrongFormat("Room Id, capacity and price should be positive integers. Capacity and price can't be 0.");
        }
        ss>>type;
        if (type == "Suite"){
            Suite* suite = new Suite(floor,roomNumber,roomId,capacity,price);
            rooms.push_back(suite);
            freeSuits ++;
        }
        else if(type == "ViewRoom"){
            ViewRoom* viewRoom = new ViewRoom(floor,roomNumber,roomId,capacity,price);
            rooms.push_back(viewRoom);
            freeRoomsWithView ++;
        }
        else if (type == "NoViewRoom"){
            NoViewRoom* noViewRoom = new NoViewRoom(floor,roomNumber,roomId,capacity,price);
            rooms.push_back(noViewRoom);
            freeRoomsWithOutView++;
        }
        else{
            throw HotelFileHasWrongFormat("Room type invalid, should be 'Suite', 'ViewRoom' or 'NoViewRoom'");
        }
        ss.clear();
    }
    this->freeRooms = rooms.size();
    this->numberOfRooms = rooms.size();

    std::getline(file,getData);
    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }
    if (getData != "Staff"){
        throw HotelFileHasWrongFormat("Line should be 'Staff'");
    }

    std::string name;
    unsigned int NIF;
    float salary;
    std::string shift;
    bool shift1;
    std::string password;

    while(std::getline(file,getData) && getData!="Client"){
        ss<<getData;
        ss >> name;
        ss >> NIF >> salary;
        if(ss.fail()) {
            throw HotelFileHasWrongFormat("NIF and salary should be integers");
        }
        if (NIF < 0 || salary<=0){
            throw HotelFileHasWrongFormat("Nif and salary should be positive integers, salary should not be 0.");
        }
        ss >> type;
        //switch fixe aqui
        if (type == "Receptionist"){
            Receptionist* receptionist = new Receptionist(name,NIF,salary);
            staff.push_back(receptionist);

        }
        else if(type == "Responsible"){
            Responsible* responsible = new Responsible(name,NIF,salary);
            staff.push_back(responsible);
        }
        else if (type == "Janitor"){
            ss >> shift;

            if (shift == "night") shift1 = false;
            else if (shift == "day") shift1 = true;
            else { throw HotelFileHasWrongFormat("Invalid shift for janitor "+ name + ". Should be 'night' or 'day'.");}

            Janitor* janitor = new Janitor(shift1,name,NIF,salary);
            staff.push_back(janitor);
        }
        else if (type == "Manager"){
            ss >> password;

            Manager* manager = new Manager(name,NIF,salary,password);
            staff.push_back(manager);
        }
        else{
            throw HotelFileHasWrongFormat("Staff type invalid, should be 'janitor', 'responsible', 'manager' or 'receptionist'");
        }
        ss.clear();
    }

    if (getData.empty()){
        return;
    }
    if (getData != "Client"){
        throw HotelFileHasWrongFormat("Line should be 'Client'");
    }

    std::string reservation1;

    while(std::getline(file,getData) && getData != "End"){
        ss<<getData;
        ss>>name>>NIF;
        if(!validateNIF(std::to_string(NIF))){
            continue;
        }
        Client* client = new Client(name,NIF);
        while(ss>>reservation1){
            Reservation* reservation = new Reservation(reservation1);
            client->addToHistory(reservation);
        }
        this->clients.push_back(client);
        ss.clear();
    }
    /*
    std::string product_types;
    while(std::getline(file,getData) && getData != "End"){
        ss<<getData;
        ss>>name>> product_types;


        while(ss>>reservation1){
            Reservation* reservation = new Reservation(reservation1);
            client->addToHistory(reservation);
        }
        this->clients.push_back(client);
        ss.clear();
    }
     */

    file.close();

}

bool Hotel::logIn(const std::string &name, const std::string &password) {
    if(name == getManagerName() && password == getManagerPassword()){
        loggedIn = true;
        return true;
    }
    return false;
}

void Hotel::logOut(){
    loggedIn = false;
}

std::string Hotel::getManagerName() const{
    for(Staff* staff_member: this->staff){
        if(staff_member->getType() == "Manager"){
            return staff_member->getName();
        }
    }
    return "ERROR";
}

std::string Hotel::getManagerPassword() const{
    for(Staff* staff_member: this->staff){
        if(staff_member->getType() == "Manager"){
            Manager* manager = dynamic_cast<Manager*>(staff_member);
            return manager->getPassword();
        }
    }
    return "ERROR";
}

std::vector<Client *>& Hotel::getClients() {
    return this->clients;
}

std::vector<Room *>& Hotel::getRooms() {
    return this->rooms;
}

std::vector<Staff *>& Hotel::getStaff() {
    return this->staff;
}
bool Hotel::getLoggedInState() const{
    return this->loggedIn;
}
void Hotel::addClient(Client* client){
    this->clients.push_back(client);
}
