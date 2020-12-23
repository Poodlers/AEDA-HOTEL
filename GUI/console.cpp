#include "console.h"
#include "utils.h"
#include <string>
#include <iostream>
#include <random>

using namespace std;

void vehicle(Hotel* hotel){
    std::string input, oldPlate, plate, kilometers, capacity;
    while(true){
        cout << "Date: " << hotel->getDate() <<endl;
        hotel->getFleet().printTree();
        cout << "Write Help to see possible commands."<<endl;

        cin >> input;
        try{
            if (input == "Help"){
                cout << "Valid commands are: Modify, Remove, Add, Search, Time, Back and Help "<<endl;
            }
            else if(input == "Modify"){

                cout << "Insert the plate of the vehicle you wish to modify:"<<endl;

                cleanCinBuffer();
                getline(cin, oldPlate);

                cout << "Write the modification when prompted, if you do not wish to alter a specific camp write '.' "
                     << endl;

                cout << "New Plate: " << endl;
                cleanCinBuffer();
                getline(cin, plate);

                cout << "New Number of Kilometers: " << endl;
                cin >> kilometers;

                cout << "New Capacity: " << endl;
                cin >> capacity;

                hotel->modifyVehicle(oldPlate, plate, kilometers, capacity);

            }
            else if(input == "Remove"){
                cout << "Insert the plate of the vehicle you wish to remove:"<<endl;

                cleanCinBuffer();
                getline(cin, oldPlate);

                hotel->removeVehicle(oldPlate);
            }
            else if (input == "Add"){
                cout << "Insert the plate of the vehicle you wish to add:"<<endl;

                cleanCinBuffer();
                getline(cin, plate);

                cout << "Insert the number of kilometers of the vehicle you wish to add:"<<endl;

                cleanCinBuffer();
                getline(cin, kilometers);

                cout << "Insert the capacity of the vehicle you wish to add:"<<endl;

                cleanCinBuffer();
                getline(cin, capacity);


                hotel->addVehicle(plate, kilometers, capacity);


            }
            else if (input == "Search"){
                cout << "Insert the plate of the vehicle you wish to add:"<<endl;

                cleanCinBuffer();
                getline(cin, plate);
                Vehicle v1 = hotel->searchVehicle(plate);
                cout << v1;
            }
            else if(input == "Back"){
                return;
            }
            else if(input == "Time"){
                hotel->incrementDate(1);
            }
            else{
                cout << "Invalid command. Write Help to see possible commands."<<endl;
            }
        }
        catch(NIFIsNotValid& msg){
            cout << msg;
        }
        catch(ClientWithThisNIFAlreadyExists& msg){
            cout << msg;
        }
        catch(ClientDoesNotExist& msg){
            cout << msg;
        }
        catch(ClientAlreadyExists& msg){
            cout << msg;
        }
        catch(SortingError& msg){
            cout << msg;
        }
        system("pause");
        system("CLS");
    }
}

void accounting(Hotel* hotel){
    if (!hotel->getLoggedInState()){
        throw AccessRestricted();
    }
    cout << left<<setw(8) << setfill(' ') <<"Value" <<"Description"<<endl;
    for (Transaction* transaction: hotel->getAccounting()){
        cout << left << setw(8) << setfill(' ')<< transaction->value << transaction->description<<endl;
    }
    cout << "Costs: " << hotel->getCosts()<<endl;
    cout << "Money earned: " << hotel->getMoneyEarned()<<endl;
    cout << "Profit: " << hotel->getProfit()<<endl;
}

void providers(Hotel* hotel){
    if (!hotel->getLoggedInState()){
        throw AccessRestricted();
    }
    while(true){
        for (Provider* provider: hotel->getProviders()){
            provider->printConsole();
            cout << endl;
        }
        cout << "Cleaning products need: " << hotel->getCleaningNecessity()<<endl;
        cout << "Catering products need: " << hotel->getCateringNecessity()<<endl;
        cout << "Other products need: " << hotel->getOtherNecessity()<<endl;
        std::string input, Id;
        cout << "Date: " << hotel->getDate() <<endl;
        cout << "Write Help to see possible commands."<<endl;
        cin >> input;
        try{
            if (input == "Back"){
                break;
            }
            else if (input == "Auto-buy"){
                hotel->autoBuy();
            }
            else if (input == "Buy"){
                cout << "Insert the ID of the product you wish to buy."<<endl;
                cin >> Id;
                checkIfPositiveInteger(Id,"product ID");

                hotel->buy(stoi(Id));
            }
            else if (input == "Help"){
                cout << "Valid commands are: Buy, Auto-buy, Time and Help "<<endl;

            }
            else if (input == "Time"){
                hotel->incrementDate(1);
            }
            else{
                cout << "Invalid command. Write Help to see possible commands."<<endl;
            }
        }
        catch(NotAPositiveInt& msg){
            cout << msg;
        }
        catch(ProductDoesNotExist& msg){
            cout <<msg;
        }
        system("pause");
        system("CLS");
    }
}

void reservation(Hotel * hotel){
    system("CLS");
    string name, NIF, capacity, roomId, date, input, reservationId;
    int pos1;
    vector<int> pos;
    string type;

        while (true) {
            cout << "Date: " << hotel->getDate() << endl;

            std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation ID"
                      << std::setw(25) << "Reservation Size" <<std::setw(16)<< "Check In"<< std::setw(16)
                      << "Check Out"
                      << std::setw(8) << "Room ID"<<std::endl;
            for (Reservation* reservation: hotel->getReservations()) {
                reservation->print();
                cout << endl;}

            cout << "Write Help to see possible commands." << endl;
            cin >> input;
            try {
                if (input == "Make") {
                    cout << endl << "Input the name and NIF of the client making the reservation." << endl;
                    cout << "Name: " << endl;
                    cleanCinBuffer();
                    getline(cin, name);
                    cout << "NIF: " << endl;
                    cin >> NIF;

                    pos1 = hotel->search(name, NIF, type = "Client");
                    cout << "Insert the reservation size: " << endl;
                    cin >> capacity;
                    checkIfPositiveInteger(capacity, "capacity");
                    cout << "Choose Room (type in room ID): " << endl;
                    cin >> roomId;
                    checkIfPositiveInteger(roomId, "roomId");
                    cout << "Choose Check In date (in format day-month-year): " << endl;
                    cin >> date;
                    Date *checkIn = new Date(date);
                    cout << "Choose Check Out date (in format day-month-year): " << endl;
                    cin >> date;
                    Date *checkOut = new Date(date);
                    hotel->makeReservation(stoi(roomId), checkIn, checkOut, stoi(capacity), pos1, -1, false);
                } else if (input == "Search") {
                    cout
                            << "Do you want reservations for/from a specific date (Date), room (Room) or a specific Id (ID)?"
                            << endl;
                    cin >> type;

                    if (type == "Date") {
                        cout << "Insert the date of the reservations you wish to find (dd-mm-yyyy):" << endl;
                        cin >> date;
                        pos = hotel->searchReservations("Date", date);
                        std::cout << std::left << std::setw(20) << std::setfill(' ') << "Reservation ID"
                                  << std::setw(25) << "Reservation Size" << std::setw(19) << "Check In" << std::setw(19)
                                  << "Check Out"
                                  << std::setw(8) << "Room ID" << std::endl;
                        for (int position: pos) {
                            hotel->getReservations()[position]->print();
                        }
                    } else if (type == "Room") {
                        cout << "Insert the room ID of the reservations you wish to find:" << endl;
                        cin >> roomId;
                        pos = hotel->searchReservations("Room", roomId);
                        std::cout << std::left << std::setw(20) << std::setfill(' ') << "Reservation ID"
                                  << std::setw(25) << "Reservation Size" << std::setw(19) << "Check In" << std::setw(19)
                                  << "Check Out"
                                  << std::setw(8) << "Room ID" << std::endl;
                        for (int position: pos) {
                            hotel->getReservations()[position]->print();
                        }
                    } else if (type == "ID") {
                        cout << "Insert the room of the ID of the reservation you wish to find:" << endl;
                        cin >> reservationId;
                        pos = hotel->searchReservations("ID", reservationId);
                        std::cout << std::left << std::setw(20) << std::setfill(' ') << "Reservation ID"
                                  << std::setw(25) << "Reservation Size" << std::setw(19) << "Check In" << std::setw(19)
                                  << "Check Out"
                                  << std::setw(8) << "Room ID" << std::endl;
                        hotel->getReservations()[pos[0]]->print();
                    } else {
                        cout << "Invalid command, please retry." << endl;
                    }
                    pos.clear();
                } else if (input == "Back") {
                    return;
                } else if (input == "Sort") {
                    cout << "Insert the type of sorting to be done. Options are: Room Id, Check In or Check Out "
                         << endl;
                    string sorting, order;
                    cleanCinBuffer();
                    getline(cin, sorting);
                    cout << "Should the order by Ascending or Descending?" << endl;
                    cin >> order;

                    sortReservations(hotel->getReservations(), sorting, order);
                } else if (input == "Remove") {
                    cout << "Insert the room of the ID of the reservation you wish to remove:" << endl;
                    cin >> reservationId;
                    pos = hotel->searchReservations("ID", reservationId);
                    hotel->removeReservation(pos[0]);
                }  else if (input == "Help") {
                    cout << "Valid commands are: Search, Remove, Make, Sort, Search or Help" << endl;
                } else {
                    cout << "Invalid command, please retry." << endl;
                }
            }
            catch (RoomDoesNotExist &msg) {
                cout << msg;
            }
            catch (ClientDoesNotExist &msg) {
                cout << msg;
            }
            catch (NotAPositiveInt &msg) {
                cout << msg;
            }
            catch (NotAnInt &msg) {
                cout << msg;
            }
            catch (DateIsNotValid &msg) {
                cout << msg;
            }
            catch (NIFIsNotValid &msg) {
                cout << msg;
            }
            catch (ClientWithThisNIFAlreadyExists &msg) {
                cout << msg;
            }
            catch (ReservationHasInvalidDates &msg) {
                cout << msg;
            }
            catch (RoomWithThisRoomIdOrRoomNumberAlreadyExists &msg) {
                cout << msg;
            }
            catch (RoomDoesNotHaveTheNecessaryCapacity &msg) {
                cout << msg;
            }
            catch (ClientCantMakeThisReservation &msg) {
                cout << msg;
            }
            catch (AnotherReservationForThisRoomAlreadyExistsAtThisTime &msg) {
                cout << msg;
            }
            catch (NoReservationsToCheckIn &msg) {
                cout << msg;
            }
            system("pause");
            system("CLS");
        }
}


void rooms(Hotel * hotel){
    string input, order, sort;
    int pos;
    string roomId, roomNumber, capacity, type, price, floor;
    while (true){
        cout << "Date: " << hotel->getDate() <<endl;
        std::cout << std::left << std::setw(14) << "Type" <<  std::setw(10) << std::setfill(' ') << "Room ID" << std::setw(15)
                  << "Room Number" << std::setw(8)<< "Floor" << std::setw(10) << "Capacity" <<std::setw(18) << "Price per night"
                  << " Availability"<<std::endl;

        for (Room* room: hotel->getRooms()){
            room->print();
            cout <<endl;
        }

        cout << "Write Help to see possible commands."<<endl;

        cin >> input;
        try{
            if (input == "Help"){
                cout << "Valid commands are: Modify, Add, Sort, Search, Time, Discount, Back and Help "<<endl;
            }
            else if (input == "Back"){
                return;
            }
            else if (input == "Add"){
                cout << "Insert the Room ID of the room you wish to add:"<<endl;
                cin >> roomId;

                cout << "Insert the Room Number of the room you wish to add:"<<endl;
                cin >> roomNumber;

                cout << "Insert the Floor of the room you wish to add:"<<endl;
                cin >> floor;

                cout << "Insert the Capacity of the room you wish to add:"<<endl;
                cin >> capacity;

                cout << "Insert the Price of the room you wish to add:"<<endl;
                cin >> price;

                cout << "Insert the Type of the room you wish to add:"<<endl;
                cin >> type;

                hotel->addRoom(floor,roomNumber,roomId,capacity,price, type);
            }
            else if (input == "Modify"){
                cout << "Insert the Room ID of the room you wish to modify:"<<endl;
                cin >> roomId;

                cout << "Insert the Room Number of the room you wish to modify:"<<endl;
                cin >> roomNumber;

                pos = hotel->searchForRoom(roomId,roomNumber);

                cout << "Insert the Capacity of the room you wish to modify (write '.' to keep as is):"<<endl;
                cin >> capacity;

                cout << "Insert the Price of the room you wish to modify (write '.' to keep as is):"<<endl;
                cin >> price;

                hotel->modifyRoom(capacity,price,pos);
            }
            else if (input == "Time"){
                hotel->incrementDate(1);
            }
            else if (input == "Sort"){
                cout << "Insert the type of sorting to be done. Options are: Room ID, Room Number, Capacity, Price, Floor or Type "<<endl;
                string sorting,order;
                cleanCinBuffer();
                getline(cin,sorting);
                cout <<"Should the order by Ascending or Descending?"<<endl;
                cin>> order;

                hotel->sortRooms(sorting,order);
            }
            else if (input == "Search"){
                cout << "Insert the Room ID of the room you wish to search:"<<endl;
                cin >> roomId;

                cout << "Insert the Room Number of the room you wish to search:"<<endl;
                cin >> roomNumber;
                pos = hotel->searchForRoom(roomId,roomNumber);
                hotel->getRooms()[pos]->print();
            }
            else if (input == "Discount"){
                cout << "What type of room should be or stop being in discount?"<<endl;
                cin>>type;
                hotel->activateDiscount(type);
            }
            else{
                cout << "Invalid command. Write Help to see possible commands."<<endl;

            }
        }
        catch(NotAPositiveInt& msg){
            cout << msg;
        }
        catch(NotAnInt& msg){
            cout << msg;
        }
        catch(RoomDoesNotExist& msg){
            cout <<msg;
        }
        catch(RoomAlreadyExists& msg){
            cout <<msg;
        }
        catch(RoomWithThisRoomIdOrRoomNumberAlreadyExists& msg){
            cout <<msg;
        }
        catch(SortingError& msg){
         cout << msg;
        }
        catch(AccessRestricted& msg){
            cout << msg;
        }
        catch(FloorDoesNotExist& msg){
            cout << msg;
        }
        catch(InvalidRoomType& msg){
            cout << msg;
        }
        catch(NotAPositiveFloat& msg){
            cout << msg;
        }
        system("pause");
        system("CLS");
    }

}

void checkIn(Hotel* hotel){
    string name, NIF;
    int pos;
    string type;

    cout << endl << "Input the name and NIF of the client who wishes to check in."<<endl;
    cout << "Name: "<<endl;
    cleanCinBuffer();
    getline(cin, name);
    cout << "NIF: "<<endl;
    cin >>NIF;

    try{
        pos = hotel->search(name,NIF, type ="Client");
        hotel->checkIn(pos, true);
    }
    catch(ClientDoesNotExist& msg){
        cout <<msg;
    }
    catch(NIFIsNotValid& msg){
        cout << msg;
    }
    catch(ClientWithThisNIFAlreadyExists& msg){
        cout <<msg;
    }
    catch(NoReservationsToCheckIn& msg){
        cout << msg;
    }

}

void checkOut(Hotel* hotel){
    string name, NIF;
    int pos;
    string type;

    cout <<endl<< "Input the name and NIF of the client who wishes to check in."<<endl;
    cout << "Name: "<<endl;
    cleanCinBuffer();
    getline(cin, name);
    cout << "NIF: "<<endl;
    cin >>NIF;

    try{
        pos = hotel->search(name,NIF, type = "Client");
        hotel->checkOut(pos);
    }
    catch(ClientDoesNotExist& msg){
        cout <<msg;
    }
    catch(NIFIsNotValid& msg){
        cout << msg;
    }
    catch(ClientWithThisNIFAlreadyExists& msg){
        cout <<msg;
    }
    catch(NoReservationsToCheckOut& msg){
        cout << msg;
    }

}

void clients(Hotel *hotel){
    system("CLS");
    cout << endl;
    int pos;
    string input;
    string name;
    string NIF;
    string type;
    while(true){
        cout << "Date: " << hotel->getDate() <<endl;
        for(Client* client: hotel->getClients()){
            client->printConsole();
        }
        cout << "Write Help to see possible commands."<<endl;

        cin >> input;
        try{
            if (input == "Help"){
                cout << "Valid commands are: Modify, Remove, Add, Sort, Search, Time, CheckIn, CheckOut, Back and Help "<<endl;
            }
            else if(input == "Modify"){

                cout << "Insert the name of the client you wish to modify:"<<endl;

                cleanCinBuffer();
                getline(cin, name);

                cout << "Insert the NIF of the client you wish to modify:"<<endl;
                cin >> NIF;

                pos = (hotel->search(name, NIF, type ="Client"));

                cout << "Write the modification when prompted, if you do not wish to alter a specific camp write '.' "
                     << endl;

                cout << "New Name: " << endl;
                cleanCinBuffer();
                getline(cin, name);

                cout << "New NIF: " << endl;
                cin >> NIF;

                hotel->modifyClient(name,NIF,pos);

            }
            else if(input == "Remove"){
                cout << "Insert the name of the client you wish to remove:"<<endl;

                cleanCinBuffer();
                getline(cin, name);

                cout << "Insert the NIF of the client you wish to remove:"<<endl;
                cin >> NIF;

                pos = hotel->search(name,NIF,type="Client");
                hotel->removeClient(pos);
            }
            else if (input == "Add"){
                cout << "Insert the name of the client you wish to add:"<<endl;

                cleanCinBuffer();
                getline(cin, name);

                cout << "Insert the NIF of the client you wish to add:"<<endl;
                cin >> NIF;

                hotel->addClient(name,NIF);


            }
            else if (input == "Sort"){
                cout << "Insert the type of sorting to be done. Options are: Name, NIF, Future reservations, Past reservations, Current reservations,"
                        " Amount of reservations, Most recent reservation"<<endl;
                string sorting,order;
                cleanCinBuffer();
                getline(cin,sorting);
                cout <<"Should the order by Ascending or Descending?"<<endl;
                cin>> order;

                hotel->clientSort(sorting,order);
            }
            else if (input == "Search"){
                cout << "Insert the name of the client you wish to find:"<<endl;

                cleanCinBuffer();
                getline(cin, name);

                cout << "Insert the NIF of the client you wish to find:"<<endl;
                cin >> NIF;

                pos = (hotel->search(name,NIF,type="Client"));

                hotel->getClients()[pos]->printConsole();
            }
            else if(input == "Back"){
                return;
            }
            else if(input == "CheckIn"){
                checkIn(hotel);
            }
            else if(input == "Time"){
                hotel->incrementDate(1);
            }
            else if (input == "CheckOut"){
                checkOut(hotel);
            }
            else{
                cout << "Invalid command. Write Help to see possible commands."<<endl;
            }
        }
        catch(NIFIsNotValid& msg){
            cout << msg;
        }
        catch(ClientWithThisNIFAlreadyExists& msg){
            cout << msg;
        }
        catch(ClientDoesNotExist& msg){
            cout << msg;
        }
        catch(ClientAlreadyExists& msg){
            cout << msg;
        }
        catch(SortingError& msg){
            cout << msg;
        }
        system("pause");
        system("CLS");
    }
}

void staff(Hotel *hotel){
    if(!hotel->getLoggedInState()){
        throw AccessRestricted();
    }
    system("CLS");
    cout << endl;
    int pos;
    string input, c;
    string name;
    string NIF;
    string type;
    string password, shift, wage, yearsOfService, evaluation;
    while(true){
        cout << "Date: " << hotel->getDate() <<endl;
        std::cout << std::left << std::setw(13) << "Position" <<  std::setw(22) << std::setfill(' ') << "Name" <<
                  std::setw(10) << "NIF" << std::setw(7) << "Wage" << std::setw(16) << "Years of work"
                  << std::setw(16) << "Floors assigned" << std::setw(7) << "Shift" << std::setw(12)<< "Evaluation"<<std::endl;
        for(Staff* staff: hotel->getStaff()){
            staff->printConsole();
            cout<<endl;
        }
        cout << "Write Help to see possible commands."<<endl;

        cin >> input;
        try{
            if (input == "Help"){
                cout << "Valid commands are: Modify, Remove, Add, Sort, Search, Time, DistributeFloors, Back and Help "<<endl;
            }
            else if(input == "Modify"){

                cout << "Insert the name of the staff member you wish to modify:"<<endl;

                cleanCinBuffer();
                getline(cin, name);

                cout << "Insert the NIF of the staff member you wish to modify:"<<endl;
                cin >> NIF;

                pos = (hotel->search(name, NIF, type = "Staff"));
                Manager* manager = dynamic_cast<Manager*> (hotel->getStaff()[pos]);
                Receptionist* receptionist = dynamic_cast<Receptionist*> (hotel->getStaff()[pos]);
                Responsible* responsible = dynamic_cast<Responsible*> (hotel->getStaff()[pos]);
                Janitor* janitor = dynamic_cast<Janitor*> (hotel->getStaff()[pos]);
                if(manager != nullptr){
                    type = "Manager";
                }
                else if (responsible != nullptr){
                    type = "Responsible";
                }
                else if (receptionist != nullptr){
                    type = "Receptionist";
                }
                else{
                    type = "Janitor";
                }

                cout << "Write the modification when prompted, if you do not wish to alter a specific camp write '.' "
                     << endl;

                cout << "New Name: " << endl;
                cleanCinBuffer();
                getline(cin, name);

                cout << "New NIF: " << endl;
                cin >> NIF;

                cout << "New wage: " << endl;
                cin >> wage;

                if (type == "Manager"){
                    cout << "New Password: " << endl;
                    cin >> password;

                    cout << "New Evaluation: " << endl;
                    cin >> evaluation;
                }
                if (type == "Janitor"){
                    cout << "New Shift: " << endl;
                    cin >> shift;
                }
                hotel->modifyStaffMember(name,NIF,wage,pos,type,shift,password,evaluation);

            }
            else if(input == "Remove"){
                cout << "Insert the name of the staff member you wish to remove:"<<endl;

                cleanCinBuffer();
                getline(cin, name);

                cout << "Insert the NIF of the staff member you wish to remove:"<<endl;
                cin >> NIF;

                pos = hotel->search(name,NIF,type = "Staff");
                hotel->removeStaffMember(pos);
            }
            else if (input == "Add"){
                cout << "Insert the name of the staff member you wish to add:"<<endl;

                cleanCinBuffer();
                getline(cin, name);

                cout << "Insert the NIF of the staff member you wish to add:"<<endl;
                cin >> NIF;

                cout << "Insert the position of the staff member you wish to add:"<<endl;
                cin >> type;

                if (type == "Manager"){
                    cout << "This action will replace the manager. Write yes to proceed, and anything else to cancel" << endl;
                    cin >> c;
                    if (c != "yes"){
                        continue;
                    }
                }
                cout << "Insert the wage of the staff member you wish to add:"<<endl;
                cin >> wage;

                if (type == "Janitor"){
                    cout << "Insert the shift of the janitor you wish to add:"<<endl;
                    cin >> shift;
                }
                else if (type == "Manager"){
                    cout << "Insert the password of the manager you wish to add:"<<endl;
                    cin >> password;
                    cout << "Insert the evaluation of the manager you wish to add:"<<endl;
                    cin >> evaluation;
                }

                hotel->addStaffMember(name,NIF,type,password,shift,wage,evaluation);
            }
            else if (input == "Sort"){
                cout << "Insert the type of sorting to be done. Options are: Name, NIF, Wage, Position and Years of service"<<endl;
                string sorting,order;
                cleanCinBuffer();
                getline(cin,sorting);
                cout <<"Should the order by Ascending or Descending?"<<endl;
                cin >> order;

                hotel->staffSort(sorting,order);
            }
            else if (input == "Search"){
                cout << "Insert the name of the staff member you wish to find:"<<endl;

                cleanCinBuffer();
                getline(cin, name);

                cout << "Insert the NIF of the staff member you wish to find:"<<endl;
                cin >> NIF;

                pos = (hotel->search(name,NIF,type="Staff"));

                hotel->getStaff()[pos]->print();
                cout << endl;
            }
            else if(input == "Back"){
                return;
            }
            else if(input == "Time"){
                hotel->incrementDate(1);
            }
            else if(input == "DistributeFloors"){
                hotel->assignFloorsToResponsibles();
                cout<< "Floors reassigned."<<endl;
            }
            else{
                cout << "Invalid command. Write Help to see possible commands."<<endl;
            }
        }
        catch(NIFIsNotValid& msg){
            cout << msg;
        }
        catch(NotAPositiveFloat& msg){
            cout << msg;
        }
        catch(NotAnInt& msg){
            cout <<msg;
        }
        catch(CantRemoveManager& msg){
            cout <<msg;
        }
        catch(StaffMemberWithThisNIFAlreadyExists& msg){
            cout << msg;
        }
        catch(StaffMemberDoesNotExist& msg){
            cout << msg;
        }
        catch(StaffMemberAlreadyExists& msg){
            cout << msg;
        }
        catch(SortingError& msg){
            cout << msg;
        }
        catch(InvalidShift& msg){
            cout <<msg;
        }
        catch(InvalidPosition& msg){
            cout << msg;
        }
        catch(InvalidEvaluation& msg){
            cout << msg;
        }
        system("pause");
        system("CLS");
    }
}

void system(Hotel* hotel){

    std::string input;

    while (true){
        cout << "Date: " << hotel->getDate() <<endl;
        cout << "Write Help to see commands"<<endl;
        cin>>input;

        if (input == "Clients"){
            clients(hotel);
        }
        else if (input == "Rooms"){
            rooms(hotel);
        }
        else if (input == "Vehicles"){
            vehicle(hotel);
        }
        else if (input == "LogIn"){
            try{
                string username, password;
                cout << "Insert Username"<<endl;
                cleanCinBuffer();
                getline(cin,username);
                cout << "Insert Password"<<endl;
                cin >> password;
                hotel->logIn(username,password);
            }
            catch(IncorrectCredentials& msg){
                cout << msg;
            }
            catch(AlreadyLoggedIn& msg){
                cout << msg;
            }
        }
        else if (input == "Help"){
            cout << "Valid commands are: Clients, Rooms, Reservations, LogIn, LogOut, Staff, Providers, Accounting, Time, Vehicles and Exit"<<endl;
        }
        else if (input == "Reservations"){
            reservation(hotel);
        }
        else if(input == "Time"){
            hotel->incrementDate(1);
        }
        else if(input == "LogOut"){
            try{
                hotel->logOut();
            }
            catch(NotLoggedIn& msg){
                cout<<msg;
            }
        }
        else if(input == "Staff"){
            try{
                staff(hotel);
            }
            catch(AccessRestricted& msg){
                cout << msg;
            }
        }
        else if (input =="Providers"){
            try{
                providers(hotel);
            }
            catch(AccessRestricted& msg){
                cout << msg;
            }
        }
        else if (input == "Accounting"){
            try{
                accounting(hotel);
            }
            catch(AccessRestricted& msg){
                cout << msg;
            }
        }
        else if (input == "Exit"){
            string filename;
            cout << "Input the name of the file to save the current hotel!"<<endl;
            cleanCinBuffer();
            getline(cin,filename);
            hotel->saveHotel(filename);
            break;
        }
        else{
            cout << "Invalid command. Write Help to see possible commands."<<endl;
        }
        system("pause");
        system("CLS");
    }
}


