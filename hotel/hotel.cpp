#include "hotel.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include "../GUI/utils.h"
#include "../exceptions/exceptions.h"

Date Hotel::date(10,11,2020);

Date Hotel::getDate() const{
    return date;
}

void Hotel::incrementDate(const int& i){
    date = date + i;
    for(Client* client: clients){
        client->archiveExpiredReservations(this->date);
    }
}

void Hotel::checkIfFloorIsValid(unsigned int floor){
    for (int i = firstFloor; i <= firstFloor + numberOfFloors; i++){
        if (i == floor){
            break;
        }
        if (i == firstFloor + numberOfFloors){
            throw FloorDosNotExist(floor);
        }
    }
}
int Hotel::searchForRoom(unsigned int roomId, unsigned int roomNumber){
    int pos = 0;
    for (Room* room: rooms){
        if(room->getRoomNumber() == roomNumber && room->getRoomId() == roomId){
            return pos;
        }
        if(room->getRoomNumber() == roomNumber && room->getRoomId() != roomId){
            throw RoomWithThisRoomIdOrRoomNumberAlreadyExists(roomNumber,roomId,"Room Number");
        }
        if(room->getRoomNumber() != roomNumber && room->getRoomId() == roomId){
            throw RoomWithThisRoomIdOrRoomNumberAlreadyExists(roomNumber,roomId,"Room Id");
        }
        pos++;
    }
    throw RoomDoesNotExist(roomNumber, roomId);
}

void Hotel::saveHotel(const std::string &hotelFile){
    std::ofstream file;
    file.open(hotelFile+ ".txt");
    if(!file.is_open()){

    }
    file << "Hotel-File\n";
    file << date.getDay()<<"-"<<date.getMonth()<<"-"<<date.getYear();
    file << this->numberOfFloors<<"\n";
    file << this->firstFloor<<"\n";
    file << "Rooms"<<"\n";
    for (Room* room: rooms){
        file << room->getFloor() << " " <<room->getRoomNumber() << " " << room->getRoomId() << " " << room->getCapacity() << " " <<room->getPricePerNight() << " ";
        Suite* suite = dynamic_cast<Suite*>(room);
        NoViewRoom* noViewRoom = dynamic_cast<NoViewRoom*>(room);
        ViewRoom* ViewRoom = dynamic_cast<class ViewRoom*>(room);
        if( suite != nullptr){
            file << "Suite\n";
        }
        else if( noViewRoom != nullptr){
            file << "NoViewRoom\n";
        }
        else if( ViewRoom != nullptr){
            file << "ViewRoom\n";
        }
    }
    file << "Staff\n";
    for(Staff* staff: staff){
        file << staff->getName()<< " " << staff->getNIF() << " " << staff->getWage() << " ";
        Receptionist* receptionist = dynamic_cast<Receptionist*>(staff);
        Responsible* responsible = dynamic_cast<Responsible*>(staff);
        Janitor* janitor = dynamic_cast<Janitor*>(staff);
        Manager* manager = dynamic_cast<Manager*>(staff);
        if(responsible != nullptr){
            file << "Responsible\n";
        }
        else if (receptionist != nullptr){
            file << "Receptionist\n";
        }
        else if (janitor != nullptr){
            file << "Janitor ";
            if (janitor->getShift()){
                file << "day\n";
            }
            else file << "night\n";
        }
        else if (manager != nullptr){
            file << "Manager " << manager->getPassword()<<"\n";
        }
    }
    file << "Client\n";
    for (Client* client: clients){
        file << client->getName()<< " " << client->getNIF()<< " ";
        for (Reservation* reservation: client->getHistory()){
            file << reservation->getRoomId() <<","<<reservation->getCheckIn()<<","<<reservation->getCheckOut()<<","<<reservation->getReservationId()<< ","<<reservation->getReservationSize()<<",0 ";
        }
        for (Reservation* reservation: client->getCurrentReservations()){
            file << reservation->getRoomId() <<","<<reservation->getCheckIn()<<","<<reservation->getCheckOut()<<","<<reservation->getReservationId()<< ","<<reservation->getReservationSize()<<",1 ";
        }
        for (Reservation* reservation: client->getFutureReservations()){
            file << reservation->getRoomId() <<","<<reservation->getCheckIn()<<","<<reservation->getCheckOut()<<","<<reservation->getReservationId()<< ","<<reservation->getReservationSize()<<",0 ";
        }
        file<<"\n";
    }
    file<<"End\n";
}

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

    date = Date(getData);

    std::getline(file,getData);
    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }

    try{
        checkIfPositiveInteger(getData, "Number of Floors");
    }
    catch(NotAPositiveInt& msg){
        std::cout << msg;
        throw HotelFileHasWrongFormat("Next element must be the number of floors.");
    }
    catch(NotAnInt& msg){
        std::cout << msg;
        throw HotelFileHasWrongFormat("Next element must be the number of floors.");
    }
    this->numberOfFloors = stoi(getData);


    std::getline(file,getData);
    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }

    try{
        checkIfInteger(getData,"First Floor");
    }
    catch(NotAnInt& msg){
        std::cout <<msg;
        throw HotelFileHasWrongFormat("Next element has to be the number of the first floor.");
    }
    this->firstFloor = stoi(getData);

    std::getline(file,getData);
    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }
    if (getData != "Rooms"){
        throw HotelFileHasWrongFormat("Line should be 'Rooms'");
    }


    std::string floor;
    std::string roomNumber;
    std::string roomId;
    std::string capacity;
    std::string price;
    std::string type;

    while(std::getline(file,getData) && getData!="Staff"){
        ss<<getData;
        ss >> floor >> roomNumber >> roomId >> capacity>> price >> type;
        try{
            checkIfInteger(floor,"Room Floor");
            checkIfFloorIsValid(stoi(floor));
            checkIfPositiveInteger(roomNumber,"Room Number");
            checkIfPositiveInteger(roomId,"Room ID");
            checkIfPositiveInteger(capacity,"Capacity");
            checkIfValidPriceOrWage(price, "Price");
            searchForRoom(stoi(roomId),stoi(roomNumber));
            throw HotelFileHasWrongFormat("Room Already Exists! Must not repeat rooms.");
        }
        catch(NotAnInt& msg){
            std::cout <<msg;
            throw HotelFileHasWrongFormat("Elements floor, room number, room ID and capacity have to be integers and appear in this order.");
        }
        catch(NotAPositiveInt& msg){
            std::cout <<msg;
            throw HotelFileHasWrongFormat("Elements room number, room ID and capacity have to be positive integers and appear in this order.");
        }
        catch(FloorDosNotExist& msg){
            std::cout <<msg;
            throw HotelFileHasWrongFormat("The floor must be within the ones declared at the begging of the file.");
        }
        catch(NotAPositiveFloat& msg){
            std::cout <<msg;
            throw HotelFileHasWrongFormat("Price must be a positive float or an integer.");
        }
        catch(RoomWithThisRoomIdOrRoomNumberAlreadyExists& msg){
            std::cout <<msg;
            throw HotelFileHasWrongFormat("Must not repeat room numbers and room IDs");
        }
        catch(RoomDoesNotExist){}

        if (type == "Suite"){
            Suite* suite = new Suite(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),stoi(price));
            rooms.push_back(suite);
            freeSuits ++;
        }
        else if(type == "ViewRoom"){
            ViewRoom* viewRoom = new ViewRoom(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),stoi(price));
            rooms.push_back(viewRoom);
            freeRoomsWithView ++;
        }
        else if (type == "NoViewRoom"){
            NoViewRoom* noViewRoom = new NoViewRoom(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),stoi(price));
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

    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }
    if (getData != "Staff"){
        throw HotelFileHasWrongFormat("Line should be 'Staff'");
    }

    std::getline(file,getData);

    std::string name;
    std::string surname;
    std::string NIF;
    std::string salary;
    std::string shift;
    int year;
    bool shift1;
    std::string password;

    while(std::getline(file,getData) && getData!="Client"){
        ss<<getData;
        ss >> name>>surname;
        name = name + " " + surname;
        ss >> NIF >> year >> salary>>type;
        try{
            checkIfValidPriceOrWage(salary, name);
            search(name,NIF,"Staff");
            throw StaffMemberAlreadyExists(name,stoi(NIF));
        }
        catch(NIFIsNotValid& msg){
            std::cout <<msg;
            throw HotelFileHasWrongFormat("NIFs must be valid.");
        }
        catch(NotAPositiveFloat& msg){
            std::cout <<msg;
            throw HotelFileHasWrongFormat("Price must be a positive float or an integer.");
        }
        catch(StaffMemberWithThisNIFAlreadyExists& msg){
            std::cout << msg;
            throw HotelFileHasWrongFormat("Staff Members must have distinct NIFs");
        }
        catch(StaffMemberDoesNotExist& msg){}


        if (type == "Receptionist"){
            Receptionist* receptionist = new Receptionist(name,stoi(NIF),stoi(salary));
            staff.push_back(receptionist);

        }
        else if(type == "Responsible"){
            Responsible* responsible = new Responsible(name,stoi(NIF),stoi(salary));
            staff.push_back(responsible);
        }
        else if (type == "Janitor"){
            ss >> shift;

            if (shift == "night") shift1 = false;
            else if (shift == "day") shift1 = true;
            else { throw HotelFileHasWrongFormat("Invalid shift for janitor "+ name + ". Should be 'night' or 'day'.");}

            Janitor* janitor = new Janitor(shift1,name,stoi(NIF),stoi(salary));
            staff.push_back(janitor);
        }
        else if (type == "Manager"){
            ss >> password;

            Manager* manager = new Manager(name,stoi(NIF),stoi(salary),password);
            staff.push_back(manager);
        }
        else{
            throw HotelFileHasWrongFormat("Staff type invalid, should be 'janitor', 'responsible', 'manager' or 'receptionist'");
        }
        ss.clear();
    }

    if (getData.empty()){
        std::cout << "File ended. Clients must be added manually."<<std::endl;
        return;
    }
    if (getData != "Client"){
        throw HotelFileHasWrongFormat("Line should be 'Client'");
    }

    std::string reservation1;
    int pos = 0;
    while(std::getline(file,getData) && getData != "End"){
        ss<<getData;
        ss>>name>>surname;
        name = name + " "+surname;
        ss>>NIF;
        try{
            search(name,NIF,"Client");
            throw ClientAlreadyExists(name,stoi(NIF));
        }
        catch(NIFIsNotValid& msg){
            std::cout <<msg;
            throw HotelFileHasWrongFormat("NIFs must be valid.");
        }
        catch(NotAPositiveFloat& msg){
            std::cout <<msg;
            throw HotelFileHasWrongFormat("Price must be a positive float or an integer.");
        }
        catch(ClientWithThisNIFAlreadyExists& msg){
            std::cout << msg;
            throw HotelFileHasWrongFormat("Staff Members must have distinct NIFs");
        }
        catch(ClientDoesNotExist& msg){}

        Client* client = new Client(name,stoi(NIF));
        this->clients.push_back(client);
        while(ss>>reservation1){
            int roomId,dayIn,monthIn,yearIn,dayOut,monthOut,yearOut,reservationId,capacity;
            bool in;
            char ignore;
            std::stringstream ss1;
            ss1 << reservation1;
            ss1 >> roomId >>ignore>> dayIn >> ignore>> monthIn >> ignore>> yearIn >> ignore>> dayOut >> ignore>>monthOut >> ignore>> yearOut >> ignore>> reservationId >> ignore >> capacity>>in;
            Date* checkIn =new Date(dayIn,monthIn,yearIn);
            Date* checkOut =new Date(dayOut,monthOut,yearOut);
            try{
                this->makeReservation(roomId,checkIn,checkOut,capacity,pos,reservationId,in);
            }
            catch(RoomDoesNotHaveTheNecessaryCapacity& msg){
                std::cout<<msg;
                throw HotelFileHasWrongFormat("Room chosen for reservation by "+ name + " with NIF "+NIF+ " doesn't have the necessary capacity.");
            }
            catch(AnotherReservationForThisRoomAlreadyExistsAtThisTime& msg){
                std::cout<<msg;
                throw HotelFileHasWrongFormat("Room chosen for reservation by "+ name + " with NIF "+NIF+ " is not free in the chosen date.");
            }
            catch(RoomDoesNotExist& msg){
                std::cout<<msg;
                throw HotelFileHasWrongFormat("Room chosen for reservation by "+ name + " with NIF "+NIF+ " does not exist.");
            }
            catch(ReservationHasInvalidDates& msg){
                std::cout<<msg;
                throw HotelFileHasWrongFormat("Reservation by "+ name + " with NIF "+NIF+ " has invalid dates.");
            }
            catch(NoReservationsToCheckIn& msg){
                std::cout<<msg;
                throw HotelFileHasWrongFormat("A reservation that can't be check in at the time is marked as checked in.");
            }
        }
        pos++;
        ss.clear();
    }

    this->incrementDate(1);

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

void Hotel::makeReservation(const unsigned int& roomId,Date* checkIn,Date* checkOut, const int& capacity, const int& posClient,const int& reservationId, const bool& in){
    for (Room* room: rooms){
        if (room->getRoomId() == roomId){
            if (room->getCapacity() < capacity){
                throw RoomDoesNotHaveTheNecessaryCapacity(roomId);
            }
            for(Reservation* reservation: room->getReservations()){
                if (reservation->getCheckIn() <= *checkIn && *checkIn<= reservation->getCheckOut()){
                    throw AnotherReservationForThisRoomAlreadyExistsAtThisTime(roomId);
                }
            }
            try{
                Reservation* reservation = new Reservation(capacity,checkIn,checkOut,roomId,reservationId);
                clients[posClient]->addNewReservation(reservation);
                room->addReservation(reservation);
                if (in == true){
                    clients[posClient]->checkIn(date);
                }
            }
            catch(...){
                throw;
            }
            return;
        }
    }
    throw RoomDoesNotExist(roomId);
}

int Hotel::search(const std::string& name, const std::string& NIF, const std::string& type){
    int pos = 0;

    try{
        validateNIF(NIF, name);
    }
    catch(...){
        throw;
    }

    if (type == "Client"){
        for(Client* client: clients){
            if (client->getName() == name && client->getNIF() == stoi(NIF)){
                return pos;
            }
            if (client->getName() != name && client->getNIF() == stoi(NIF)){
                throw ClientWithThisNIFAlreadyExists(name, stoi(NIF));
            }
            pos ++;
        }
        throw ClientDoesNotExist(name, stoi(NIF));
    }
    else if (type == "Staff"){
        for(Staff* staff: staff){
            if (staff->getName() == name && staff->getNIF() == stoi(NIF)){
                return pos;
            }
            if (staff->getName() != name && staff->getNIF() == stoi(NIF)){
                throw StaffMemberWithThisNIFAlreadyExists(name, stoi(NIF));
            }
            pos ++;
        }
        throw StaffMemberDoesNotExist(name, stoi(NIF));
    }
}

void Hotel::logIn(const std::string &name, const std::string &password) {
    if(name == getManagerName() && password == getManagerPassword()){
        if (loggedIn == true){
            throw AlreadyLoggedIn();
        }
        loggedIn = true;
    }
    throw IncorrectCredentials();
}

void Hotel::logOut(){
    if(!this->loggedIn){
        throw NotLoggedIn("LogOut");
    }
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
void Hotel::addClient(const std::string& name, const std::string& NIF){
    try{
        int pos = search(name,NIF, "Client");
    }
    catch(ClientDoesNotExist& msg){
        Client* client = new Client(name, stoi(NIF));
        this->clients.push_back(client);
        return;
    }
    catch(...){
        throw;
    }
    throw ClientAlreadyExists(name, stoi(NIF));
}

void Hotel::modifyClient(const std::string & name, std::string& NIF, const int& pos){
    if (NIF != "."){
        try{
            validateNIF(NIF,name);
        }
        catch(...){
            throw;
        }
    }

    clients[pos]->personModify(name,NIF);
}

void Hotel::removeClient(const int& pos){
    clients.erase(clients.begin() + pos);
}

void Hotel::clientSort(const std::string& input,const std::string& order1){
    bool order;
    if (order1 == "Ascending"){
        order = true;
    }
    else if (order1 == "Descending"){
        order = false;
    }
    else throw SortingError();

    if (input == "name"){
        if (order){
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return c1->getName() < c2->getName();
            });
        }
        else{
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return c1->getName() > c2->getName();
            });
        }
    }
    else if (input == "NIF"){
        if (order){
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return c1->getNIF() < c2->getNIF();
            });
        }
        else{
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return c1->getNIF() > c2->getNIF();
            });
        }
    }
    else if (input == "Amount of future reservations"){
        if (order){
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return c1->getFutureReservations().size() < c2->getFutureReservations().size();
            });
        }
        else{
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return c1->getFutureReservations().size() > c2->getFutureReservations().size();
            });
        }
    }
    else if (input == "Amount of past reservations"){
        if (order){
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return c1->getHistory().size() < c2->getHistory().size();
            });
        }
        else{
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return c1->getHistory().size() > c2->getHistory().size();
            });
        }
    }
    else if (input == "Current reservations"){
        if (order){
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return c1->getCurrentReservations().size() < c2->getCurrentReservations().size();
            });
        }
        else{
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return c1->getCurrentReservations().size() > c2->getCurrentReservations().size();
            });
        }
    }
    else if (input == "Amount of reservations"){
        if (order){
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return (c1->getCurrentReservations().size() + c1->getHistory().size() + c1->getCurrentReservations().size()) < (c2->getCurrentReservations().size() + c2->getHistory().size() + c2->getCurrentReservations().size());
            });
        }
        else{
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                return (c1->getCurrentReservations().size() + c1->getHistory().size() + c1->getCurrentReservations().size()) > (c2->getCurrentReservations().size() + c2->getHistory().size() + c2->getCurrentReservations().size());
            });
        }
    }
    else if(input == "Most Recent Reservation"){
        if (order){
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                Date min1(31,12,9999), min2(31,12,9999);
                if(!c1->getCurrentReservations().empty()){
                    for(Reservation* reservation: c1->getCurrentReservations()){
                        if (reservation->getCheckIn() > min1){
                            min1 = reservation->getCheckIn();
                        }
                    }
                }
                else{
                    for(Reservation* reservation: c1->getHistory()){
                        if (reservation->getCheckIn() > min1){
                            min1 = reservation->getCheckIn();
                        }
                    }
                }
                if(!c2->getCurrentReservations().empty()) {
                    for (Reservation *reservation: c2->getCurrentReservations()) {
                        if (reservation->getCheckIn() > min2) {
                            min2 = reservation->getCheckIn();
                        }
                    }
                }
                else{
                    for(Reservation* reservation: c2->getHistory()){
                        if (reservation->getCheckIn() > min2){
                            min2 = reservation->getCheckIn();
                        }
                    }
                }
                return min1 < min2;
            });
        }
        else{
            sort(clients.begin(),clients.end(),[](Client* c1, Client* c2){
                Date min1(31,12,9999), min2(31,12,9999);
                if(!c1->getCurrentReservations().empty()){
                    for(Reservation* reservation: c1->getCurrentReservations()){
                        if (reservation->getCheckIn() > min1){
                            min1 = reservation->getCheckIn();
                        }
                    }
                }
                else{
                    for(Reservation* reservation: c1->getHistory()){
                        if (reservation->getCheckIn() > min1){
                            min1 = reservation->getCheckIn();
                        }
                    }
                }
                if(!c2->getCurrentReservations().empty()) {
                    for (Reservation *reservation: c2->getCurrentReservations()) {
                        if (reservation->getCheckIn() > min2) {
                            min2 = reservation->getCheckIn();
                        }
                    }
                }
                else{
                    for(Reservation* reservation: c2->getHistory()){
                        if (reservation->getCheckIn() > min2){
                            min2 = reservation->getCheckIn();
                        }
                    }
                }
                return min1 < min2;
            });
        }
    }
    else throw SortingError();
}