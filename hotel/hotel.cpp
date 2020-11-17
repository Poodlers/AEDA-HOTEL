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

void Hotel::checkIfFloorIsValid(const unsigned int& floor){
    for (int i = firstFloor; i <= firstFloor + numberOfFloors; i++){
        if (i == floor){
            break;
        }
        if (i == firstFloor + numberOfFloors){
            throw FloorDosNotExist(floor);
        }
    }
}
int Hotel::searchForRoom(const std::string& roomId, const std::string& roomNumber){
    try{
        checkIfPositiveInteger(roomId, "Room Id");
        checkIfPositiveInteger(roomNumber, "Room Number");
    }
    catch(...){
        throw;
    }
    int pos = 0;
    for (Room* room: rooms){
        if(room->getRoomNumber() == stoi(roomNumber) && room->getRoomId() == stoi(roomId)){
            return pos;
        }
        if(room->getRoomNumber() == stoi(roomNumber) && room->getRoomId() != stoi(roomId)){
            throw RoomWithThisRoomIdOrRoomNumberAlreadyExists(stoi(roomNumber),stoi(roomId),"Room Number");
        }
        if(room->getRoomNumber() != stoi(roomNumber) && room->getRoomId() == stoi(roomId)){
            throw RoomWithThisRoomIdOrRoomNumberAlreadyExists(stoi(roomNumber),stoi(roomId),"Room Id");
        }
        pos++;
    }
    throw RoomDoesNotExist(stoi(roomNumber), stoi(roomId));
}

int Hotel::searchForRoomByRoomId(const int &roomId) {

    int pos = 0;
    for (Room* room: rooms){
        if(room->getRoomId() == roomId){
            return pos;
        }
        pos++;
    }
    throw RoomDoesNotExist(roomId);
}

void Hotel::saveHotel(const std::string &hotelFile){
    std::ofstream file;
    std::stringstream ss;
    std::string f;
    file.open(hotelFile+ ".txt");
    if(!file.is_open()){

    }
    file << "Hotel-File\n";
    file << date.getDay()<<"-"<<date.getMonth()<<"-"<<date.getYear()<<"\n";
    file << this->numberOfFloors<<"\n";
    file << this->firstFloor<<"\n";
    file << "Rooms"<<"\n";
    for (Room* room: rooms){
        ss<<room->getPricePerNight();
        ss>>f;
        file << room->getFloor() << " " <<room->getRoomNumber() << " " << room->getRoomId() << " " << room->getCapacity() << " " << f << " ";
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
        ss<<staff->getWage();
        ss>>f;
        file << staff->getName()<< " " << staff->getNIF() << " "<<date.getYear() - staff->getYearsOfService()<<" "<<f<<" ";
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
            file << reservation->getRoomId() <<","<<reservation->getCheckIn().getDay()<<"-"<<reservation->getCheckIn().getMonth()<<"-"<<reservation->getCheckIn().getYear()<<","<<reservation->getCheckOut().getDay()<<"-"<<reservation->getCheckOut().getMonth()<<"-"<<reservation->getCheckOut().getYear()<<","<<reservation->getReservationId()<< ","<<reservation->getReservationSize()<<",0 ";
        }
        for (Reservation* reservation: client->getCurrentReservations()){
            file << reservation->getRoomId() <<","<<reservation->getCheckIn().getDay()<<"-"<<reservation->getCheckIn().getMonth()<<"-"<<reservation->getCheckIn().getYear()<<","<<reservation->getCheckOut().getDay()<<"-"<<reservation->getCheckOut().getMonth()<<"-"<<reservation->getCheckOut().getYear()<<","<<reservation->getReservationId()<< ","<<reservation->getReservationSize()<<",1 ";
        }
        for (Reservation* reservation: client->getFutureReservations()){
            file << reservation->getRoomId() <<","<<reservation->getCheckIn().getDay()<<"-"<<reservation->getCheckIn().getMonth()<<"-"<<reservation->getCheckIn().getYear()<<","<<reservation->getCheckOut().getDay()<<"-"<<reservation->getCheckOut().getMonth()<<"-"<<reservation->getCheckOut().getYear()<<","<<reservation->getReservationId()<< ","<<reservation->getReservationSize()<<",0 ";
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
    std::string price1;
    std::string type;

    while(std::getline(file,getData) && getData!="Staff"){
        ss<<getData;
        ss >> floor >> roomNumber >> roomId >> capacity>> price1 >> type;
        try{
            checkIfInteger(floor,"Room Floor");
            checkIfFloorIsValid(stoi(floor));
            checkIfPositiveInteger(capacity,"Capacity");
            checkIfValidPriceOrWage(price1, "Price");
            searchForRoom(roomId,roomNumber);
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

        float price = stof(price1);
        if (type == "Suite"){
            Suite* suite = new Suite(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),price);
            rooms.push_back(suite);
            freeSuits ++;
        }
        else if(type == "ViewRoom"){
            ViewRoom* viewRoom = new ViewRoom(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),price);
            rooms.push_back(viewRoom);
            freeRoomsWithView ++;
        }
        else if (type == "NoViewRoom"){
            NoViewRoom* noViewRoom = new NoViewRoom(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),price);
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

    std::string name;
    std::string surname;
    std::string NIF;
    std::string salary1;
    std::string shift,typeSearch;
    int year;
    bool shift1;
    std::string password;

    while(std::getline(file,getData) && getData!="Client"){
        ss<<getData;
        ss >> name>>surname;
        name = name + " " + surname;
        ss >> NIF >> year >> salary1>>type;
        try{
            checkIfValidPriceOrWage(salary1, name);
            search(name, NIF,  typeSearch="Staff");
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

        float salary = stof(salary1);

        if (type == "Receptionist"){
            Receptionist* receptionist = new Receptionist(name,stoi(NIF),salary);
            receptionist->setYearsOfService(date.getYear()-year);
            staff.push_back(receptionist);

        }
        else if(type == "Responsible"){
            Responsible* responsible = new Responsible(name,stoi(NIF),salary);
            responsible->setYearsOfService(date.getYear()-year);
            staff.push_back(responsible);
        }
        else if (type == "Janitor"){
            ss >> shift;

            if (shift == "night") shift1 = false;
            else if (shift == "day") shift1 = true;
            else { throw HotelFileHasWrongFormat("Invalid shift for janitor "+ name + ". Should be 'night' or 'day'.");}

            Janitor* janitor = new Janitor(shift1,name,stoi(NIF),salary);
            janitor->setYearsOfService(date.getYear()-year);
            staff.push_back(janitor);
        }
        else if (type == "Manager"){
            ss >> password;

            Manager* manager = new Manager(name,stoi(NIF),salary,password);
            manager->setYearsOfService(date.getYear()-year);
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
            search(name, NIF, typeSearch = "Client");
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
            catch(ClientCantMakeThisReservation& msg){
                std::cout <<msg;
                throw HotelFileHasWrongFormat(name + "'s first reservation can't be for a suite.");
            }
        }
        pos++;
        ss.clear();
    }
    this->assignFloorsToResponsibles();

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
            Suite* suite = dynamic_cast<Suite*>(room);
            if (suite != nullptr && clients[posClient]->getHistory().size() == 0){
                throw ClientCantMakeThisReservation();
            }
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
                if(*checkOut < date){
                    clients[posClient]->addToHistory(reservation);
                }
                else if (in) clients[posClient]->addCurrentReservation(reservation);
                else clients[posClient]->addNewReservation(reservation);

                room->addReservation(reservation);
                if (in == true){
                    this->checkIn(posClient);
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

int Hotel::search(const std::string& name, const std::string& NIF, std::string& type){
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
                Manager* manager = dynamic_cast<Manager*>(staff);
                Receptionist* receptionist = dynamic_cast<Receptionist*>(staff);
                Responsible* responsible = dynamic_cast<Responsible*>(staff);
                Janitor* janitor = dynamic_cast<Janitor*>(staff);
                if (manager != nullptr){
                    type = "manager";
                }
                else if (responsible != nullptr){
                    type = "responsible";
                }
                else if (receptionist != nullptr){
                    type = "receptionist";
                }
                else if (janitor != nullptr){
                    type = "janitor";
                }
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

void Hotel::checkIn(const int& pos){
    int pos1;
    std::vector<int> roomIds;
    try{
        roomIds = clients[pos]->checkIn(&date);
        for (int roomId: roomIds){
            pos1 = searchForRoomByRoomId(roomId);
            rooms[pos1]->changeAvailability(false);
        }
    }
    catch(...){
        throw;
    }
}

void Hotel::addRoom(const std::string &floor, const std::string & roomNumber ,const std::string & roomId, const std::string & capacity, const std::string &pricePerNight, const std::string& type){
    int pos;
    try{
        checkIfInteger(floor, "Floor");
        checkIfFloorIsValid(stoi(floor));
        checkIfPositiveInteger(capacity, "Capacity");
        checkIfValidPriceOrWage(pricePerNight,"Price per Night");
        pos = searchForRoom(roomId,roomNumber);
        throw RoomAlreadyExists(stoi(roomNumber),stoi(roomId));
    }
    catch(RoomDoesNotExist){
        if (type == "ViewRoom"){
            ViewRoom* viewRoom = new ViewRoom(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),stof(pricePerNight));
            rooms.push_back(viewRoom);
        }
        else if (type == "NoViewRoom"){
            NoViewRoom* noViewRoom = new NoViewRoom(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),stof(pricePerNight));
            rooms.push_back(noViewRoom);
        }
        else if (type == "Suite"){
            Suite* suite = new Suite(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),stof(pricePerNight));
            rooms.push_back(suite);
        }
        else throw InvalidRoomType(stoi(roomId),type);
    }
    catch(...){
        throw;
    }
}

void Hotel::activateDiscount(const std::string& type){
    if(!this->loggedIn){
        throw AccessRestricted();
    }
    if (type == "Suite"){
        for (Room* room : rooms){
            Suite* suite = dynamic_cast<Suite*> (room);
            if (suite != nullptr){
                if (suite->getDiscountState()){
                    suite->activateDiscount();
                }
                else suite->deactivateDiscount();
            }
        }
    }
    else if (type == "NoViewRoom") {
        for (Room *room : rooms) {
            NoViewRoom *noViewRoom = dynamic_cast<NoViewRoom *> (room);
            if (noViewRoom != nullptr) {
                if (noViewRoom->getDiscountState()){
                    noViewRoom->activateDiscount();
                }
                else noViewRoom->deactivateDiscount();
            }
        }
    }
    else if (type == "ViewRoom") {
        for (Room *room : rooms) {
            ViewRoom *viewRoom = dynamic_cast<class ViewRoom*> (room);
            if (viewRoom != nullptr) {
                if (viewRoom->getDiscountState()){
                    viewRoom->activateDiscount();
                }
                else viewRoom->deactivateDiscount();
            }
        }
    }
    else throw InvalidRoomType(-1, type);
}

void Hotel::modifyRoom(const std::string& capacity, const std::string& pricePerNight, const int& pos){
    try{
        if(capacity != "."){
            checkIfPositiveInteger(capacity, "Capacity");
        }
        if (pricePerNight != "."){
            checkIfValidPriceOrWage(pricePerNight, "Price per night");
        }
        rooms[pos]->modify(capacity,pricePerNight);
    }
    catch(...){
        throw;
    }
}

void Hotel::sortRooms(const std::string& input,const std::string& order1){
    bool order;
    if (order1 == "Ascending"){
        order = true;
    }
    else if (order1 == "Descending"){
        order = false;
    }
    else throw SortingError();

    if (input == "Room ID"){
        if (order){
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                return r1->getRoomId()<r2->getRoomId();
            });
        }
        else{
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                return r1->getRoomId()> r2->getRoomId();
            });
        }
    }
    else if (input == "Room Number"){
        if (order){
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                return r1->getRoomNumber()<r2->getRoomNumber();
            });
        }
        else{
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                return r1->getRoomNumber()> r2->getRoomNumber();
            });
        }
    }
    else if (input == "Floor"){
        if (order){
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                if (r1->getFloor() == r2->getFloor()) return r1->getRoomNumber()<r2->getRoomNumber();
                else return r1->getFloor() < r2->getFloor();
            });
        }
        else{
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                if (r1->getFloor() == r2->getFloor()) return r1->getRoomNumber()>r2->getRoomNumber();
                else return r1->getFloor() > r2->getFloor();
            });
        }
    }
    else if (input == "Capacity"){
        if (order){
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                if (r1->getCapacity() == r2->getCapacity()) return r1->getRoomId()<r2->getRoomId();
                else return r1->getCapacity() < r2->getCapacity();
            });
        }
        else{
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                if (r1->getCapacity() == r2->getCapacity()) return r1->getRoomId()>r2->getRoomId();
                else return r1->getCapacity() > r2->getCapacity();
            });
        }
    }
    else if (input == "Price"){
        if (order){
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                if (r1->getCapacity() == r2->getCapacity()) return r1->getRoomId()<r2->getRoomId();
                else return r1->getCapacity() < r2->getCapacity();
            });
        }
        else{
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                if (r1->getPricePerNight() == r2->getPricePerNight()) return r1->getRoomId()>r2->getRoomId();
                else return r1->getPricePerNight() > r2->getPricePerNight();
            });
        }
    }
    else if (input == "Type"){
        if (order){
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                Suite* suite1 = dynamic_cast<Suite*> (r1);
                NoViewRoom* noViewRoom1 = dynamic_cast<NoViewRoom*> (r1);
                ViewRoom* viewRoom1 = dynamic_cast<class ViewRoom*> (r1);
                Suite* suite2 = dynamic_cast<Suite*> (r2);
                NoViewRoom* noViewRoom2 = dynamic_cast<NoViewRoom*> (r2);
                ViewRoom* viewRoom2 = dynamic_cast<class ViewRoom*> (r2);

                if (suite1 == nullptr && suite2 != nullptr){
                    return true;
                }
                if (noViewRoom1 != nullptr && viewRoom2 != nullptr){
                    return true;
                }
                else return false;
            });
        }
        else{
            sort(rooms.begin(),rooms.end(),[](Room* r1, Room* r2){
                Suite* suite1 = dynamic_cast<Suite*> (r1);
                NoViewRoom* noViewRoom1 = dynamic_cast<NoViewRoom*> (r1);
                ViewRoom* viewRoom1 = dynamic_cast<class ViewRoom*> (r1);
                Suite* suite2 = dynamic_cast<Suite*> (r2);
                NoViewRoom* noViewRoom2 = dynamic_cast<NoViewRoom*> (r2);
                ViewRoom* viewRoom2 = dynamic_cast<class ViewRoom*> (r2);

                if (suite2 == nullptr && suite1 != nullptr){
                    return true;
                }
                if (noViewRoom2 == nullptr && viewRoom1 != nullptr){
                    return true;
                }
                else return false;
            });
        }
    }
    else throw SortingError();
}


void Hotel::checkOut(const int& pos){
    int pos1;
    std::vector<int> roomIds;
    try{
        roomIds = clients[pos]->checkOut(&date);
        for (int roomId: roomIds){
            pos1 = searchForRoomByRoomId(roomId);
            rooms[pos1]->changeAvailability(true);
        }
    }
    catch(...){
        throw;
    }
}

void Hotel::logIn(const std::string &name, const std::string &password) {
    if(name == getManagerName() && password == getManagerPassword()){
        if (loggedIn == true){
            throw AlreadyLoggedIn();
        }
        loggedIn = true;
        std::cout << "Logged in successfully."<<std::endl;
        return;
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
    std::string type = "Client";
    try{
        int pos = search(name, NIF, type);
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

void Hotel::modifyStaffMember(const std::string & name, std::string& NIF, const int& pos, const std::string& type, const std::string& shift,const std::string& password){
    if (NIF != "."){
        try{
            validateNIF(NIF,name);
        }
        catch(...){
            throw;
        }
    }
    if (type == "janitor"){
        Janitor* janitor = dynamic_cast<Janitor*> (staff[pos]);
        staff.erase(staff.begin()+pos);
        try{
            janitor->janitorModify(name,NIF,shift);
        }
        catch(InvalidShift& msg){
            throw;
        }
        staff.insert(staff.begin()+pos,janitor);
    }
    else if(type == "manager"){
        Manager* manager = dynamic_cast<Manager*> (staff[pos]);
        staff.erase(staff.begin()+pos);
        manager->managerModify(name,NIF,password);
        staff.insert(staff.begin()+pos,manager);

    }
    else {
        staff[pos]->personModify(name,NIF);
    }
}

void Hotel::addStaffMember(const std::string& name, const std::string& NIF, const std::string& type, const std::string& password, const std::string& shift, const std::string& wage){
    std::string type1;
    bool shf;
    try{
        int pos = search(name, NIF, type1 = "Staff");
        checkIfValidPriceOrWage(wage, "wage");
    }
    catch(StaffMemberDoesNotExist& msg){
        if (type == "manager"){
            for (int i= 0; i< this->staff.size();i++){
                Manager* manager = dynamic_cast<Manager*>(staff[i]);
                if (manager != nullptr){
                    this->staff.erase(this->staff.begin()+ i);
                    break;
                }
            }
            Manager* manager = new Manager(name, stoi(NIF), stof(wage), password);
            this->staff.push_back(manager);
        }
        else if (type == "janitor"){
            if(shift == "day"){
                shf = true;
            }
            else if (shift == "night"){
                shf = false;
            }
            else throw InvalidShift();

            Janitor* janitor = new Janitor(shf,name, stoi(NIF), stof(wage));
            this->staff.push_back(janitor);
        }
        else if (type == "responsible"){
            Responsible* responsible = new Responsible(name, stoi(NIF), stof(wage));
            this->assignFloorsToResponsibles();
            this->staff.push_back(responsible);
        }
        else if (type == "receptionist"){
            Receptionist* receptionist = new Receptionist(name, stoi(NIF), stof(wage));
            this->staff.push_back(receptionist);
        }
        else throw InvalidPosition(type,name);
        return;
    }
    catch(...){
        throw;
    }
    throw StaffMemberAlreadyExists(name, stoi(NIF));
}

void Hotel::removeStaffMember(const int &pos) {
    staff.erase(staff.begin() + pos);
}

void Hotel::removeClient(const int& pos){
    clients.erase(clients.begin() + pos);
}

void Hotel::assignFloorsToResponsibles(){
    std::vector<Responsible*> responsibles;
    for (Staff* staff: staff){
        Responsible* responsible = dynamic_cast<Responsible*> (staff);
        if (responsible != nullptr){
            responsible->clearAssignedFloors();
            responsibles.push_back(responsible);
        }
    }
    int floors = numberOfFloors;
    while (floors != 0){
        for (Responsible* responsible: responsibles){
            responsible->assignFloor(floors);
            floors--;
            if (floors == 0) break;
        }
    }

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
                if(c1->getCurrentReservations().empty() && c2->getCurrentReservations().empty()&& c1->getHistory().empty() && c2->getHistory().empty()){
                    return false;
                }
                else if ((!c1->getCurrentReservations().empty()||!c1->getHistory().empty()) && c2->getCurrentReservations().empty() && c2->getHistory().empty()){
                    return false;
                }
                else if ((!c2->getCurrentReservations().empty()||!c2->getHistory().empty()) && c1->getCurrentReservations().empty() && c1->getHistory().empty()){
                    return true;
                }
                else {
                    if (!c1->getCurrentReservations().empty()) {
                        for (Reservation *reservation: c1->getCurrentReservations()) {
                            if (reservation->getCheckIn() < min1) {
                                min1 = reservation->getCheckIn();
                            }
                        }
                    } else {
                        for (Reservation *reservation: c1->getHistory()) {
                            if (reservation->getCheckIn() < min1) {
                                min1 = reservation->getCheckIn();
                            }
                        }
                    }
                    if (!c2->getCurrentReservations().empty()) {
                        for (Reservation *reservation: c2->getCurrentReservations()) {
                            if (reservation->getCheckIn() < min2) {
                                min2 = reservation->getCheckIn();
                            }
                        }
                    } else {
                        for (Reservation *reservation: c2->getHistory()) {
                            if (reservation->getCheckIn() < min2) {
                                min2 = reservation->getCheckIn();
                            }
                        }
                    }
                    return min1 < min2;
                }
            });
        }
        else {
            sort(clients.begin(), clients.end(), [](Client *c1, Client *c2) {
                Date min1(31, 12, 9999), min2(31, 12, 9999);
                if (c1->getCurrentReservations().empty() && c2->getCurrentReservations().empty() &&
                    c1->getHistory().empty() && c2->getHistory().empty()) {
                    return false;
                } else if ((!c1->getCurrentReservations().empty() || !c1->getHistory().empty()) &&
                           c2->getCurrentReservations().empty() && c2->getHistory().empty()) {
                    return true;
                } else if ((!c2->getCurrentReservations().empty() || !c2->getHistory().empty()) &&
                           c1->getCurrentReservations().empty() && c1->getHistory().empty()) {
                    return false;
                } else {
                    if (!c1->getCurrentReservations().empty()) {
                        for (Reservation *reservation: c1->getCurrentReservations()) {
                            if (reservation->getCheckIn() < min1) {
                                min1 = reservation->getCheckIn();
                            }
                        }
                    } else {
                        for (Reservation *reservation: c1->getHistory()) {
                            if (reservation->getCheckIn() < min1) {
                                min1 = reservation->getCheckIn();
                            }
                        }
                    }
                    if (!c2->getCurrentReservations().empty()) {
                        for (Reservation *reservation: c2->getCurrentReservations()) {
                            if (reservation->getCheckIn() < min2) {
                                min2 = reservation->getCheckIn();
                            }
                        }
                    } else {
                        for (Reservation *reservation: c2->getHistory()) {
                            if (reservation->getCheckIn() < min2) {
                                min2 = reservation->getCheckIn();
                            }
                        }
                    }
                    return min1 > min2;
                }
            });
        }
    }
    else throw SortingError();
}

void Hotel::staffSort(const std::string& input,const std::string& order1){
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
            sort(staff.begin(),staff.end(),[](Staff* c1, Staff* c2){
                return c1->getName() < c2->getName();
            });
        }
        else{
            sort(staff.begin(),staff.end(),[](Staff* c1, Staff* c2){
                return c1->getName() > c2->getName();
            });
        }
    }
    else if (input == "NIF"){
        if (order){
            sort(staff.begin(),staff.end(),[](Staff* c1, Staff* c2){
                return c1->getNIF() < c2->getNIF();
            });
        }
        else{
            sort(staff.begin(),staff.end(),[](Staff* c1, Staff* c2){
                return c1->getNIF() > c2->getNIF();
            });
        }
    }
    else if (input == "wage"){
        if (order){
            sort(staff.begin(),staff.end(),[](Staff* c1, Staff* c2){
                return c1->getWage() < c2->getWage();
            });
        }
        else{
            sort(staff.begin(),staff.end(),[](Staff* c1, Staff* c2){
                return c1->getWage() > c2->getWage();
            });
        }
    }
    else if (input == "years of service"){
        if (order){
            sort(staff.begin(),staff.end(),[](Staff* c1, Staff* c2){
                return c1->getYearsOfService() < c2->getYearsOfService();
            });
        }
        else{
            sort(staff.begin(),staff.end(),[](Staff* c1, Staff* c2){
                return c1->getYearsOfService() > c2->getYearsOfService();
            });
        }
    }
    else if(input == "position"){
        if (order){
            sort(staff.begin(),staff.end(),[](Staff* c1, Staff* c2){
                Manager* manager1 = dynamic_cast<Manager*> (c1);
                Receptionist* receptionist1 = dynamic_cast<Receptionist*> (c1);
                Responsible* responsible1 = dynamic_cast<Responsible*> (c1);
                Janitor* janitor1 = dynamic_cast<Janitor*> (c1);
                Manager* manager2 = dynamic_cast<Manager*> (c2);
                Receptionist* receptionist2 = dynamic_cast<Receptionist*> (c2);
                Responsible* responsible2 = dynamic_cast<Responsible*> (c2);
                Janitor* janitor2 = dynamic_cast<Janitor*> (c2);
                if (manager1 == nullptr && manager2 != nullptr){
                    return true;
                }
                if (receptionist1 !=nullptr && responsible1 == nullptr && responsible2 != nullptr){
                    return true;
                }
                if (manager1 == nullptr && responsible1 == nullptr && receptionist2 == nullptr && janitor2 == nullptr){
                    return true;
                }
                if(janitor1 != nullptr && janitor2 == nullptr){
                    return true;
                }
                else return false;
            });
        }
        else{
            sort(staff.begin(),staff.end(),[](Staff* c1, Staff* c2){
                Manager* manager1 = dynamic_cast<Manager*> (c1);
                Receptionist* receptionist1 = dynamic_cast<Receptionist*> (c1);
                Responsible* responsible1 = dynamic_cast<Responsible*> (c1);
                Janitor* janitor1 = dynamic_cast<Janitor*> (c1);
                Manager* manager2 = dynamic_cast<Manager*> (c2);
                Receptionist* receptionist2 = dynamic_cast<Receptionist*> (c2);
                Responsible* responsible2 = dynamic_cast<Responsible*> (c2);
                Janitor* janitor2 = dynamic_cast<Janitor*> (c2);
                if (manager2 == nullptr && manager1 != nullptr){
                    return true;
                }
                if (receptionist2 !=nullptr && responsible2 == nullptr && responsible1 != nullptr){
                    return true;
                }
                if (manager2 == nullptr && responsible2 == nullptr && receptionist1 == nullptr && janitor1 == nullptr){
                    return true;
                }
                if(janitor2 != nullptr && janitor1 == nullptr){
                    return true;
                }
                else return false;
            });
        }
    }
    else throw SortingError();
}