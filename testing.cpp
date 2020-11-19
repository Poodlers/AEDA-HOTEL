#include "hotel/hotel.h"
#include "provider/provider.h"
#include "product/product1.h"
#include "person/client/client.h"
#include "room/room.h"
#include "person/staff/staff.h"
#include "exceptions/exceptions.h"
#include "GUI/utils.h"
#include <string>
#include <iostream>
using namespace std;

void providers(Hotel* hotel){
    if (!hotel->getLoggedInState()){
        throw AccessRestricted();
    }
    for (Provider* provider: hotel->getProviders()){
        provider->print();
    }
    while(true){
        std::string input;
        try{
            if (input == "Back"){
                break;
            }
            else if (input == "Auto-buy"){

            }
            else if (input == "Buy"){

            }
            else if (input == "Help"){

            }
            else{

            }
        }
        catch(...){

        }
    }


}

void reservation(Hotel * hotel){
    system("CLS");
    string name, NIF, capacity, roomId, date, input, reservationId;
    int pos1;
    vector<int> pos;
    string type;
    while(true){
        cout << "Date: " << hotel->getDate() <<endl;
        cout << "Do you wish to make a reservation (Make) or to search for reservations by date (Search)?"<<std::endl;
        cin >> input;
        try{
            if (input == "Make"){
                cout << endl << "Input the name and NIF of the client making the reservation."<<endl;
                cout << "Name: "<<endl;
                cleanCinBuffer();
                getline(cin, name);
                cout << "NIF: "<<endl;
                cin >>NIF;

                pos1 = hotel->search(name,NIF, type ="Client");
                cout << "Insert the reservation size: "<<endl;
                cin>>capacity;
                checkIfPositiveInteger(capacity, "capacity");
                cout << "Choose Room (type in room ID): "<<endl;
                cin>>roomId;
                checkIfPositiveInteger(roomId, "roomId");
                cout << "Choose Check In date (in format day-month-year): "<<endl;
                cin>>date;
                Date* checkIn = new Date(date);
                cout << "Choose Check Out date (in format day-month-year): "<<endl;
                cin>>date;
                Date* checkOut = new Date(date);
                hotel->makeReservation(stoi(roomId),checkIn,checkOut,stoi(capacity),pos1,-1,false);
            }
            else if (input == "Search"){
                cout << "Do you want reservations for/from a specific date (Date), room (Room), a specific Id (ID) or all reservations (All)?"<<endl;
                cin >> type;

                if (type == "Date"){
                    cout << "Insert the date of the reservations you wish to find (dd-mm-yyyy):"<<endl;
                    cin >> date;
                    pos = hotel->searchReservations("Date", date);
                    std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation ID"
                              << std::setw(25) << "Reservation Size" <<std::setw(19)<< "Check In"<< std::setw(19)
                              << "Check Out"
                              << std::setw(8) << "Room ID"<<std::endl;
                    for (int position: pos){
                        hotel->getReservations()[position]->print();
                    }
                }
                else if (type == "Room"){
                    cout << "Insert the room ID of the reservations you wish to find:"<<endl;
                    cin >> roomId;
                    pos = hotel->searchReservations("Room", roomId);
                    std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation ID"
                              << std::setw(25) << "Reservation Size" <<std::setw(19)<< "Check In"<< std::setw(19)
                              << "Check Out"
                              << std::setw(8) << "Room ID"<<std::endl;
                    for (int position: pos){
                        hotel->getReservations()[position]->print();
                    }
                }
                else if (type == "All"){
                    std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation ID"
                              << std::setw(25) << "Reservation Size" <<std::setw(19)<< "Check In"<< std::setw(19)
                              << "Check Out"
                              << std::setw(8) << "Room ID"<<std::endl;
                    for (Reservation* reservation: hotel->getReservations()){
                        reservation->print();
                        cout << endl;
                    }
                }
                else if (type == "ID"){
                    cout << "Insert the room of the ID of the reservation you wish to find:"<<endl;
                    cin >> reservationId;
                    pos = hotel->searchReservations("ID", reservationId);
                    std::cout << std::left <<  std::setw(20) << std::setfill(' ') << "Reservation ID"
                              << std::setw(25) << "Reservation Size" <<std::setw(19)<< "Check In"<< std::setw(19)
                              << "Check Out"
                              << std::setw(8) << "Room ID"<<std::endl;
                    hotel->getReservations()[pos[0]]->print();
                }
                else{
                    cout << "Invalid command, please retry."<<endl;
                }
                pos.clear();
            }
            else if (input == "Back"){
                return;
            }
            else{
                cout << "Invalid command, please retry."<<endl;
            }
        }
        catch(RoomDoesNotExist& msg){
            cout << msg;
        }
        catch(ClientDoesNotExist&msg){
            cout << msg;
        }
        catch(NIFIsNotValid& msg){
            cout <<msg;
        }
        catch(ClientWithThisNIFAlreadyExists& msg){
            cout <<msg;
        }
        catch(ReservationHasInvalidDates& msg){
            cout << msg;
        }
        catch(RoomWithThisRoomIdOrRoomNumberAlreadyExists& msg){
            cout <<msg;
        }
        catch(RoomDoesNotHaveTheNecessaryCapacity& msg){
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
                cout << "Insert the Room ID of the room you wish to modify:"<<endl;
                cin >> roomId;

                cout << "Insert the Room Number of the room you wish to modify:"<<endl;
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
        catch(FloorDosNotExist& msg){
            cout << msg;
        }
        catch(InvalidRoomType& msg){
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
        hotel->checkIn(pos);
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
                cout << "Insert the type of sorting to be done. Options are: Name, NIF, Amount of future reservations, Amount of past reservations, Current reservations,"
                        " Amount of reservations, Most Recent Reservation"<<endl;
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
    string password, shift, wage;
    while(true){
        cout << "Date: " << hotel->getDate() <<endl;
        std::cout << std::left << std::setw(13) << "Position" <<  std::setw(22) << std::setfill(' ') << "Name" <<
                  std::setw(10) << "NIF" << std::setw(7) << "Wage" << std::setw(16) << "Years of work"
                  << std::setw(16) << "Floors assigned" << std::setw(7) << "Shift" << std::setw(12)<< "Evaluation"<<std::endl;
        for(Staff* staff: hotel->getStaff()){
            staff->print();
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

                cout << "Write the modification when prompted, if you do not wish to alter a specific camp write '.' "
                     << endl;

                cout << "New Name: " << endl;
                cleanCinBuffer();
                getline(cin, name);

                cout << "New NIF: " << endl;
                cin >> NIF;

                if (type == "Manager"){
                    cout << "New Password: " << endl;
                    cin >> password;
                }
                if (type == "Janitor"){
                    cout << "New Shift: " << endl;
                    cin >> shift;
                }
                hotel->modifyStaffMember(name,NIF,pos,type,shift,password);

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
                }
                hotel->addStaffMember(name,NIF,type,password,shift,wage);

            }
            else if (input == "Sort"){
                cout << "Insert the type of sorting to be done. Options are: Name, NIF, Wage, Position and Years of Service"<<endl;
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
        catch(ManagerAlreadyExists& msg){
            cout << msg;
        }
        catch(InvalidPosition& msg){
            cout<<msg;
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
            cout << "Valid commands are: Clients, Reservations, LogIn, LogOut, Staff, Providers, Countability, Reservations, Time and Exit"<<endl;
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

        }
        else if (input == "Countability"){

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

Hotel* createHotel(){
    while(true){
        string input;
        cout << "input the name of the hotel file (without .txt)"<< endl;
        cin >> input;
        system("CLS");
        cleanCinBuffer();
        try {
            Hotel *hotel = new Hotel(input);
            return hotel;
        }
        catch(FileNotFound& msg){
            cout <<msg;
        }
        catch(HotelFileHasWrongFormat& msg){
            cout << msg;
        }
        catch(NIFIsNotValid& msg){
            cout <<msg;
        }
    }
}

int main(){
    Hotel* hotel = createHotel();
    system(hotel);

    return 0;
}
