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


void Clients(Hotel *hotel){
    for(Client* client: hotel->getClients()){
        client->printConsole();
    }
    cout << endl;
    int pos;
    string input;
    string name;
    string NIF;
    while(true){
        cout << "Write Help to see possible commands."<<endl;
        cleanCinBuffer();
        cin >> input;

        if (input == "Help"){
            cout << "Valid commands are: Modify, Remove, Add, Sort, Search, Back and Help "<<endl;
        }
        else if(input == "Modify"){
            cout << "Insert the name of the client you wish to modify:"<<endl;
            cleanCinBuffer();
            getline(cin, name);
            cout << "Insert the NIF of the client you wish to modify:"<<endl;
            cin >> NIF;
            if (!CheckIfInteger(NIF)) {
                throw NIFIsNotValid(name, -1);
            }
            pos = (hotel->search(name, stoi(NIF), "Client"));
            if (pos == -1) {
                throw ClientDoesNotExist(name, stoi(NIF));
            }
            cout << "Write the modification when prompted, if you do not wish to alter a specific camp write '.' "
            << endl;
            cout << "New Name: " << endl;
            getline(cin, name);
            cout << "New NIF: " << endl;
            cin >> NIF;
            if (!CheckIfInteger(NIF) && NIF != ".") {
                throw NIFIsNotValid(name, -1);
            }
            if (!validateNIF(NIF)) {
                throw NIFIsNotValid(name, stoi(NIF));
            }
            for (Client *client1: hotel->getClients()) {
                if (client1->getNIF() == stoi(NIF)) {
                    throw ClientWithThisNIFAlreadyExists(name, stoi(NIF));
                }
            }
            hotel->getClients()[pos]->personModify(name, NIF);
        }
        else if(input == "Remove"){
            cout << "Insert the name of the client you wish to remove:"<<endl;
            cleanCinBuffer();
            getline(cin, name);
            cleanCinBuffer();
            cout << "Insert the NIF of the client you wish to remove:"<<endl;
            cin >> NIF;
            cleanCinBuffer();

            if (!CheckIfInteger(NIF)){
                throw NIFIsNotValid(name, -1);
            }
            pos = (hotel->search(name,stoi(NIF),"Client"));
            if (pos == -1){
                throw ClientDoesNotExist(name,stoi(NIF));
            }
            delete hotel->getClients()[pos];
        }
        else if (input == "Add"){
            cout << "Insert the name of the client you wish to add:"<<endl;
            cleanCinBuffer();
            getline(cin, name);
            cout << "Insert the NIF of the client you wish to add:"<<endl;
            cin >> NIF;
            if (!CheckIfInteger(NIF)){
                throw NIFIsNotValid(name, -1);
            }
            pos = (hotel->search(name,stoi(NIF),"Client"));
            if (pos == -1){
                for (Client* client1: hotel->getClients()){
                    if (client1->getNIF() == stoi(NIF)){
                        throw ClientWithThisNIFAlreadyExists(name, stoi(NIF));
                    }
                }
                Client* client = new Client(name,stoi(NIF));
                hotel->addClient(client);
                }
            else throw ClientAlreadyExists(name,stoi(NIF));
        }

        else if (input == "Sort"){
            cleanCinBuffer();

        }
        else if (input == "Search"){
            cout << "Insert the name of the client you wish to find:"<<endl;
            cleanCinBuffer();
            getline(cin, name);
            cout << "Insert the NIF of the client you wish to find:"<<endl;
            cin >> NIF;

            if (!CheckIfInteger(NIF)){
                throw NIFIsNotValid(name, -1);
            }
            pos = (hotel->search(name,stoi(NIF),"Client"));
            if (pos == -1){
                throw ClientDoesNotExist(name,stoi(NIF));
            }
            hotel->getClients()[pos]->printConsole();
        }
        else if(input == "Back"){
            return;
        }
        else{
            cout << "Invalid command. Write Help to see possible commands."<<endl;
        }
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
        cout << "Write Help to see commands"<<endl;
        getline(cin,input);

        if (input == "Clients"){
            try{
                Clients(hotel);
            }
            catch(NIFIsNotValid& msg){
                cout << msg;
            }
            catch (ClientWithThisNIFAlreadyExists& msg){
                cout << msg;
            }
            catch(ClientDoesNotExist& msg){
                cout << msg;
            }
            catch(ClientAlreadyExists& msg){
                cout << msg;
            }
            input ="Clients";
        }
        else if (input == "Rooms"){

        }
        else if (input == "LogIn"){
            try{
                if(hotel->getLoggedInState()){
                    throw AlreadyLoggedIn();
                }
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
        }
        else if (input == "Help"){
            cout << "Valid commands are: Clients, Reservations, LogIn, LogOut, Staff, Providers, Countability, Reservatio, CheckIn, CheckOut and Exit"<<endl;
        }
        else if(input == "CheckIn"){

        }
        else if (input == "CheckOut"){

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

    }
}

Hotel* createHotel(){
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

int main(){

    Hotel* hotel = createHotel();

    try{
        system(hotel);
    }
    catch(AlreadyLoggedIn& msg){
        cout << msg;
    }

    return 0;
}
