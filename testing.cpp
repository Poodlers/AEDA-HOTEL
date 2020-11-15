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

void checkIn(Hotel* hotel){
    string name, NIF;
    int pos;

    cout << "Date: " << hotel->getDate() <<endl;
    cout << "Input the name and NIF of the client who wishes to check in."<<endl;
    cout << "Name: "<<endl;
    cleanCinBuffer();
    getline(cin, name);
    cout << "NIF: "<<endl;
    cin >>NIF;

    try{
        pos = hotel->search(name,NIF, "Client");
        hotel->getClients()[pos]->checkIn(hotel->getDate());
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

    cout << "Date: " << hotel->getDate() <<endl;
    cout << "Input the name and NIF of the client who wishes to check in."<<endl;
    cout << "Name: "<<endl;
    cleanCinBuffer();
    getline(cin, name);
    cout << "NIF: "<<endl;
    cin >>NIF;

    try{
        pos = hotel->search(name,NIF, "Client");
        hotel->getClients()[pos]->checkOut(hotel->getDate());
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

    cout << endl;
    int pos;
    string input;
    string name;
    string NIF;
    while(true){
        cout << "Date: " << hotel->getDate() <<endl;
        for(Client* client: hotel->getClients()){
            client->printConsole();
        }
        cout << "Write Help to see possible commands."<<endl;

        cin >> input;
        try{
            if (input == "Help"){
                cout << "Valid commands are: Modify, Remove, Add, Sort, Search, Time, Back and Help "<<endl;
            }
            else if(input == "Modify"){

                cout << "Insert the name of the client you wish to modify:"<<endl;

                cleanCinBuffer();
                getline(cin, name);

                cout << "Insert the NIF of the client you wish to modify:"<<endl;
                cin >> NIF;

                pos = (hotel->search(name, NIF, "Client"));

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

                pos = hotel->search(name,NIF,"Client");
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
                cout << "Insert the type of sorting to be done. Options are: name, NIF, Amount of future reservations, Amount of past reservations, Current reservations,"
                        " Amount of reservations, Most Recent Reservation"<<endl;
                string sorting,order;
                cin >> sorting;
                cout <<"Should the order by ascending or descending?"<<endl;
                cin>> order;

                hotel->clientSort(sorting,order);
            }
            else if (input == "Search"){
                cout << "Insert the name of the client you wish to find:"<<endl;

                cleanCinBuffer();
                getline(cin, name);

                cout << "Insert the NIF of the client you wish to find:"<<endl;
                cin >> NIF;

                validateNIF(NIF, name);

                pos = (hotel->search(name,NIF,"Client"));

                hotel->getClients()[pos]->printConsole();
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
        system("CLS");
    }
}

void Reservations(){
    //should display current reservations, allow to edit, remove or make make new reservations
    //option to sort by date or by client
}

void Rooms(){
    //should display rooms and their disponibility
    // be able to add rooms or remove them?
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

        }
        else if (input == "LogIn"){
            try{
                string username, password;
                cout << "Insert Username"<<endl;
                cin >> username;
                cleanCinBuffer();
                cout << "Insert Password"<<endl;
                cin >> password;
                cleanCinBuffer();
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
            cout << "Valid commands are: Clients, Reservations, LogIn, LogOut, Staff, Providers, Countability, Reservation, Time, CheckIn, CheckOut and Exit"<<endl;
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
        else if(input == "LogOut"){
            try{
                hotel->logOut();
            }
            catch(NotLoggedIn& msg){
                cout<<msg;
            }
        }
        else if(input == "Staff"){

        }
        else if (input =="Providers"){

        }
        else if (input == "Countability"){

        }
        else if (input == "Reservation"){

        }
        else if (input == "Exit"){
            break;
        }
        else{
            cout << "Invalid command. Write Help to see possible commands."<<endl;
        }
        system("CLS");
    }
}

Hotel* createHotel(){
    while(true){
        string input;
        cout << "input the name of the hotel file (without .txt)"<< endl;
        cin >> input;
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
