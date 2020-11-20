#include "hotel.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "../utils/utils.h"
#include "../exceptions/exceptions.h"

Date Hotel::date(9,11,2020);

Date Hotel::getDate() const{
    return date;
}

void Hotel::addProvider(Provider* provider){
    providers.push_back(provider);
}

std::vector<Provider*> Hotel::getProviders () const{
    return providers;
}

int Hotel::getCosts() const{
    int money = 0;
    for (Transaction* transaction: accounting){
        if (transaction->value < 0) money += transaction->value;
    }
    return money;
}

int Hotel::getProfit() const{
    int money = 0;
    for (Transaction* transaction: accounting){
        money += transaction->value;
    }
    return money;
}

int Hotel::getMoneyEarned() const{
    int money = 0;
    for (Transaction* transaction: accounting){
        if (transaction->value > 0) money += transaction->value;
    }
    return money;
}

void Hotel::reduceNecessity(std::string type) {
    if(type == "Cleaning"){
        this->cleaningNecessity--;
    }else if(type == "Other"){
        this->otherNecessity--;
    }else if(type == "Catering"){
        this->cateringNecessity--;
    }
}

void Hotel::buy(const unsigned int &productId){
    for (Provider* provider: providers){
        for (unsigned int i = 0; i < provider->getProducts().size(); i++){
            if (productId == provider->getProducts()[i]->getId()){
                Transaction* transaction = new Transaction;
                transaction->value =  - provider->getProducts()[i]->getPrice();
                transaction->description = "Bought " + provider->getProducts()[i]->getType() + " product from " + provider->getName();
                accounting.push_back(transaction);
                this->reduceNecessity(provider->getProducts()[i]->getType());
                this->budget = this->budget - provider->getProducts()[i]->getPrice();
                provider->getProducts()[i]->reduceStock();
                return;
            }
        }
    }
    throw ProductDoesNotExist(productId);
}

void Hotel::autoBuy(){
    std::vector<Product*> products;
    for (Provider* provider: providers){
        for (Product* product: provider->getProducts()){
            products.push_back(product);
        }
    }
    sort(products.begin(),products.end(),[](Product* p1, Product* p2){
        if (p1->getType() == p2->getType()){
            return p1->getPrice() < p2->getPrice();
        }
        else{
            if (p1->getType() == "Cleaning" && p2->getType() != "Cleaning"){
                return false;
            }
            if (p1->getType() == "Catering" && p2->getType() != "Cleaning" && p2->getType() != "Catering"){
                return false;
            }
            return true;
        }
    });

    for (Product* product: products){
        if (product->getType() == "Cleaning" && cleaningNecessity != 0){
            while(product->getStock()!= 0  && cleaningNecessity != 0){
                buy(product->getId());
            }
        }
        if (product->getType() == "Catering" && cateringNecessity != 0){
            while(product->getStock()!= 0 && cateringNecessity != 0){
                buy(product->getId());
            }
        }
        if (product->getType() == "Other" && otherNecessity != 0){
            while(product->getStock()!= 0 && otherNecessity != 0){
                buy(product->getId());
            }
        }
    }
}

void Hotel::incrementDate(const int& i){
    date = date + i;
    for(Client* client: clients){
        client->archiveExpiredReservations(&this->date);
    }
    if (date.getDay() == 1){
        for (Provider* provider: providers){
            provider->restock();
        }
    }
    if (date.getDay() == date.getDaysInMonth(date.getMonth())){
        payStaff();
    }
    if (date.getDay() == 1 && date.getMonth() == 1){
        for (Staff* staff: staff){
            staff->setYearsOfService(staff->getYearsOfService()+ 1);
        }
    }
}

void Hotel::payStaff(){
    for (Staff* staff: staff){
        Transaction* transaction = new Transaction;
        transaction->value = -  8 * staff->getWage() * date.getDaysInMonth(date.getMonth());
        transaction->description = "Wage of staff member " + staff->getName();
        accounting.push_back(transaction);
    }
}

void Hotel::checkIfFloorIsValid(const unsigned int& floor){
    for (int i = firstFloor; i <= firstFloor + numberOfFloors; i++){
        if (i == floor){
            break;
        }
        if (i == firstFloor + numberOfFloors){
            throw FloorDoesNotExist(floor);
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

int Hotel::searchForRoomByRoomId(const unsigned int &roomId) {
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
            file << "Manager " << manager->getPassword()<< " " << manager->getEvaluation()<<"\n";
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
    file<<"Transactions\n";
    for (Transaction* transaction: accounting){
        file << transaction->value << " " << transaction->description<<"\n";
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

    std::string name;
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
        catch(FloorDoesNotExist& msg){
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
        }
        else if(type == "ViewRoom"){
            ViewRoom* viewRoom = new ViewRoom(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),price);
            rooms.push_back(viewRoom);
        }
        else if (type == "NoViewRoom"){
            NoViewRoom* noViewRoom = new NoViewRoom(stoi(floor),stoi(roomNumber),stoi(roomId),stoi(capacity),price);
            rooms.push_back(noViewRoom);
        }
        else{
            throw HotelFileHasWrongFormat("Room type invalid, should be 'Suite', 'ViewRoom' or 'NoViewRoom'");
        }
        ss.clear();
    }
    this->numberOfRooms = rooms.size();

    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }
    if (getData != "Staff"){
        throw HotelFileHasWrongFormat("Line should be 'Staff'");
    }

    std::string surname;
    std::string NIF;
    std::string salary1;
    std::string shift,typeSearch;
    int year;
    bool shift1;
    std::string password, evaluation;

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
            ss >> evaluation;
            try{
                checkIfInteger(evaluation, "Evaluation");
                if (stoi(evaluation) < 1 || stoi(evaluation) > 5){
                    throw  HotelFileHasWrongFormat("Manager evaluation is invalid");
                }
            }
            catch(NotAnInt& msg){
                std::cout << msg;
                throw  HotelFileHasWrongFormat("Evaluation has to be an int");
            }
            Manager* manager = new Manager(name,stoi(NIF),salary,password,stoi(evaluation));
            manager->setYearsOfService(date.getYear()-year);
            staff.push_back(manager);
        }
        else{
            throw HotelFileHasWrongFormat("Staff type invalid, should be 'Janitor', 'Responsible', 'Manager' or 'Receptionist'");
        }
        ss.clear();
    }

    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }
    if (getData != "Client"){
        throw HotelFileHasWrongFormat("Line should be 'Client'");
    }

    std::string reservation1;
    int pos = 0;
    while(std::getline(file,getData) && getData != "Transactions"){
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
            try{
                Date* checkIn =new Date(dayIn,monthIn,yearIn);
                Date* checkOut =new Date(dayOut,monthOut,yearOut);
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
            catch(DateIsNotValid& msg){
                std::cout<<msg;
                throw HotelFileHasWrongFormat(name + "'s reservation has an invalid date.");
            }
        }
        pos++;
        ss.clear();
    }
    int max =0;
    for (Reservation* reservation: reservations){
        if (reservation->getReservationId() > max){
            max = reservation->getReservationId();
        }
    }
    reservations[0]->setID(max);
    this->assignFloorsToResponsibles();

    if (getData.empty()){
        throw HotelFileHasWrongFormat("File ends prematurely.");
    }
    if (getData != "Transactions"){
        throw HotelFileHasWrongFormat("Line should be 'Transactions'");
    }
    std::string description;
    float value;
    while (std::getline(file,getData) && getData != "End"){
        ss << getData;
        ss >> value;
        if (ss.fail()){
            throw HotelFileHasWrongFormat("the transaction value has to be a number.");
        }
        std::getline(ss,description);
        Transaction* transaction;
        transaction->value = value;
        transaction->description = description;
        ss.clear();
    }

    file.close();

}

std::vector<Reservation*> Hotel::getReservations() const{
    return reservations;
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
            for(Reservation* reservation: reservations){
                if (reservation->getRoomId() == roomId && reservation->getCheckIn() <= *checkIn && *checkIn<= reservation->getCheckOut()){
                    throw AnotherReservationForThisRoomAlreadyExistsAtThisTime(roomId);
                }
            }
            try{
                Reservation* reservation = new Reservation(capacity,checkIn,checkOut,roomId,reservationId);
                if(*checkOut < date){
                    clients[posClient]->addToHistory(reservation);
                }
                else if (in){
                    if (*checkOut > date && (*checkIn > date || *checkIn == date)){
                        clients[posClient]->addCurrentReservation(reservation);
                    }
                    else throw NoReservationsToCheckIn(clients[posClient]->getName(),clients[posClient]->getNIF());
                }
                else clients[posClient]->addNewReservation(reservation);

                this->reservations.push_back(reservation);
            }
            catch(...){
                throw;
            }
            return;
        }
    }
    throw RoomDoesNotExist(roomId);
}

void Hotel::removeClient(const int& pos){
    clients.erase(clients.begin() + pos);
}

void Hotel::removeStaffMember(const int& pos){
    staff.erase(staff.begin() + pos);
}


std::vector<int> Hotel::searchReservations(const std::string& searchCriteria, const std::string& value){
    std::vector<int> pos;
    if(searchCriteria == "ID"){
        for (int i = 0; i < reservations.size(); i++){
            if (reservations[i]->getReservationId() == stoi(value)){
                pos.push_back(i);
                return pos;
            }
        }
    }
    else if (searchCriteria == "Room"){
        for (int i = 0; i < reservations.size(); i++){
            if (reservations[i]->getRoomId() == stoi(value)){
                pos.push_back(i);
            }
        }
        return pos;
    }
    else if (searchCriteria == "Date"){
        try{
            Date date1(value);
            for (int i = 0; i < reservations.size(); i++){
                if (reservations[i]->getCheckIn() == date1){
                    pos.push_back(i);
                }
            }
            return pos;
        }
        catch(...){
            throw;
        }
    }
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
    std::vector<int> reservationIds;
    try{
        std::stringstream ss;
        reservationIds = clients[pos]->checkIn(&date);
        for (int id: reservationIds){
            ss << id;
            for (Reservation* reservation: reservations){
                if (reservation->getReservationId() == id) {
                    pos1 = searchForRoomByRoomId(reservation->getRoomId());
                    rooms[pos1]->changeAvailability(false);
                    Transaction *transaction = new Transaction;
                    transaction->value = (rooms[pos1]->getPricePerNight() -
                                          (rooms[pos1]->getPricePerNight() * rooms[pos1]->getDiscountValue() *
                                           rooms[pos1]->getDiscountState())) *
                                         (reservation->getCheckOut() - reservation->getCheckIn());
                    transaction->description = "Client check in to room " + std::to_string(reservation->getRoomId()) +
                                               " which was reserved for " +
                                               std::to_string(reservation->getCheckOut() - reservation->getCheckIn()) +
                                               " days.\n";
                    accounting.push_back(transaction);
                    cleaningNecessity += 10 * (reservation->getCheckOut() - reservation->getCheckIn());
                    cateringNecessity += 10 * (reservation->getCheckOut() - reservation->getCheckIn());
                    otherNecessity += 10 * (reservation->getCheckOut() - reservation->getCheckIn());
                }
            }
        }
    }
    catch(...){
        throw;
    }
}

unsigned int Hotel::getCleaningNecessity() const{
    return cleaningNecessity;
}
unsigned int Hotel::getCateringNecessity() const{
    return cateringNecessity;
}
unsigned int Hotel::getOtherNecessity() const{
    return otherNecessity;
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
        numberOfRooms++;
    }
    catch(...){
        throw;
    }
}

void Hotel::activateDiscount(const std::string& type){
    if(!this->loggedIn){
        throw AccessRestricted();
    }
    if (type == "Suite") {
        for (Room *room : rooms) {
            Suite *suite = dynamic_cast<Suite *> (room);
            if (suite != nullptr) {
                suite->toggleDiscount();
            }
        }
    }
    else if (type == "NoViewRoom") {
        for (Room *room : rooms) {
            NoViewRoom *noViewRoom = dynamic_cast<NoViewRoom *> (room);
            if (noViewRoom != nullptr) {
                noViewRoom->toggleDiscount();
            }
        }
    }
    else if (type == "ViewRoom") {
        for (Room *room : rooms) {
            ViewRoom *viewRoom = dynamic_cast<class ViewRoom*> (room);
            if (viewRoom != nullptr) {
                viewRoom->toggleDiscount();
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

                if (suite2 == nullptr && suite1!= nullptr){
                    return true;
                }
                if (noViewRoom2 != nullptr && viewRoom1 != nullptr){
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
    for(auto& staff_member: this->staff){
        if(staff_member->getType() == "Manager"){
            return staff_member->getName();
        }
    }
    return "ERROR";
}

std::string Hotel::getManagerPassword() const{
    for(auto& staff_member: this->staff){
        if(staff_member->getType() == "Manager"){
            Manager* manager = dynamic_cast<Manager*>(staff_member);
            return manager->getPassword();
        }
    }
    return "ERROR";
}

std::vector<Transaction*> Hotel::getAccounting() const{
    return accounting;
}


std::vector<Client*>& Hotel::getClients()  {
    return this->clients;
}

std::vector<Room*>& Hotel::getRooms() {
    return this->rooms;
}

std::vector<Staff*>& Hotel::getStaff() {
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

void Hotel::modifyStaffMember(const std::string & name, std::string& NIF,std::string& wage, const int& pos, const std::string& type, const std::string& shift,const std::string& password, const std::string& evaluation){
    if (NIF != "."){
        try{
            validateNIF(NIF,name);
            checkIfValidPriceOrWage(wage, "wage");
        }
        catch(...){
            throw;
        }
    }
    if (evaluation != "." && type == "Manager"){
        try{
            checkIfInteger(evaluation,"manager evaluation");
            if (stoi(evaluation) < 1 || stoi(evaluation)>5){
                throw InvalidEvaluation();
            }
        }
        catch(...){
            throw;
        }
    }
    if (type == "Janitor"){
        Janitor* janitor = dynamic_cast<Janitor*> (staff[pos]);
        staff.erase(staff.begin()+pos);
        try{
            janitor->janitorModify(name,NIF,shift,wage);
        }
        catch(InvalidShift& msg){
            throw;
        }
        staff.insert(staff.begin()+pos,janitor);
    }
    else if(type == "Manager"){
        Manager* manager = dynamic_cast<Manager*> (staff[pos]);
        staff.erase(staff.begin()+pos);
        manager->managerModify(name,NIF,wage,password,evaluation);
        staff.insert(staff.begin()+pos,manager);

    }
    else {
        staff[pos]->modifyStaffMember(name,NIF,wage);
    }
}


void Hotel::addStaffMember(const std::string& name, const std::string& NIF, const std::string& type,const std::string& password, const std::string& shift, const std::string& wage, const std::string& evaluation){
    std::string type1;
    bool shf;
    try{

        checkIfValidPriceOrWage(wage, "wage");
        checkIfInteger(evaluation,"manager evaluation");
        int pos = search(name, NIF, type1 = "Staff");
        throw StaffMemberAlreadyExists(name, stoi(NIF));
    }
    catch(StaffMemberDoesNotExist& msg){
        if (type == "Manager"){
            for (int i= 0; i< this->staff.size();i++){
                Manager* manager = dynamic_cast<Manager*>(staff[i]);
                if (manager != nullptr){
                    this->staff.erase(this->staff.begin()+ i);
                    break;
                }
            }
            if (stoi(evaluation) < 1 || stoi(evaluation)>5){
                throw InvalidEvaluation();
            }
            Manager* manager = new Manager(name, stoi(NIF), stof(wage), password,stoi(evaluation));
            this->staff.push_back(manager);
        }
        else if (type == "Janitor"){
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
        else if (type == "Responsible"){
            Responsible* responsible = new Responsible(name, stoi(NIF), stof(wage));
            this->assignFloorsToResponsibles();
            this->staff.push_back(responsible);
        }
        else if (type == "Receptionist"){
            Receptionist* receptionist = new Receptionist(name, stoi(NIF), stof(wage));
            this->staff.push_back(receptionist);
        }
        else throw InvalidPosition(type,name);
        return;
    }
    catch(...){
        throw;
    }
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

    if (input == "Name"){
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
    else if (input == "Future reservations"){
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
    else if (input == "Past reservations"){
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
    else if(input == "Most recent reservation"){
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

void Hotel::deleteReservation(Reservation *reservation) {
    auto find = std::find(this->reservations.begin(),this->reservations.end(),reservation);
    for(auto client: this->clients){
        for(auto Reservation:client->getHistory()){
            if(Reservation == reservation){
                this->reservations.erase(find);
                client->removeReservation(reservation);
                return;
            }
        }
        for(auto Reservation:client->getFutureReservations()){
            if(Reservation == reservation){
                this->reservations.erase(find);
                client->removeReservation(reservation);
                return;
            }
        }
        for(auto Reservation:client->getCurrentReservations()){
            if(Reservation == reservation){
                this->reservations.erase(find);
                client->removeReservation(reservation);
                return;
            }
        }
    }
}

void Hotel::eraseStaff(Staff *staff) {
    auto find = std::find(this->staff.begin(),this->staff.end(),staff);
    this->staff.erase(find);
    delete staff;
}

void Hotel::eraseClient(Client *client) {
    auto find = std::find(this->clients.begin(),this->clients.end(),client);
    this->clients.erase(find);
    delete client;
}

void Hotel::eraseRoom(Room *room) {
    auto find = std::find(this->rooms.begin(),this->rooms.end(),room);
    this->rooms.erase(find);
    delete room;
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

    if (input == "Name"){
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
    else if (input == "Wage"){
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
    else if (input == "Years of service"){
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
    else if(input == "Position"){
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

int Hotel::getFirstFloor() const {
    return this->firstFloor;
}

int Hotel::getNumberOfFloors() const {
    return this->numberOfFloors;
}

unsigned int Hotel::getBudget() {
    return this->budget;
}