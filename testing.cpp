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


void clientSort(const vector<Client>& clients){
    cout<< "Choose by which you wish to sort: Name, NIF, Total Number of Reservations, Number of Future Reservations, Number of Past Reservations, Current Reservations, Last Reservation."<<endl;

}

void searchClient(vector<Client*>* clients){
    string input;
    int nif, pos;
    cout << "Input the name and Nif of the client:"<<endl;
    cin>>input>>nif;
    Client* client = new Client(input,nif);
    pos = sequentialSearch(*clients,client);
    if (pos == -1){
        cout << " not found"<<endl;
    }
    (*clients)[pos]->print();
}

void clientModify(Client* client){
    cout << "Write the modification when prompted, if you do not wish to alter a specific camp write '.' "<<endl;
    string edit;
    int nif;
    cout << "New Name: " << endl;
    cin >>edit;
    cleanCinBuffer();
    if (edit != "."){
        client->setName(edit);
    }
    cout << "New NIF: " << endl;
    cin >>edit;
    cleanCinBuffer();
    if (edit != "."){
        client->setNIF(nif);
    }
}

void Clients(Hotel *hotel){
    for(Client* client: hotel->getClients()){
        client->print();
    }
    cout << endl;
    while(true){
        string input;
        cout << "Write Help to see possible commands."<<endl;
        cin >> input;
        cleanCinBuffer();
        int nif;
        if (input == "Help"){
            cout << "Valid commands are: Modify, Remove, Add, Sort, Search, Back and Help "<<endl;
        }
        else if(input == "Modify"){
            cout << "Insert the name and NIF of the client you wish to modify, name first and then NIF:"<<endl;
            cin >> input >> nif;
            cleanCinBuffer();
            Client* client = new Client(input,nif);
            int pos = sequentialSearch(hotel->getClients(), client);
            delete client;
            if (pos != -1)
                clientModify(hotel->getClients()[pos]);
            else cout << "No client found who matches the description"<<endl;
        }
        else if(input == "Remove"){
            cout << "Insert the name and NIF of the client you wish to remove, name first and then NIF:"<<endl;
            cin >> input >> nif;
            cleanCinBuffer();
            Client* client = new Client(input,nif);
            int pos = sequentialSearch(hotel->getClients(), client);
            delete client;
            if (pos != -1)
                delete(hotel->getClients()[pos]);
            else cout << "No client found who matches the description"<<endl;
        }
        else if (input == "Add"){
            cout << "Insert the name and NIF of the client you wish to add, name first (FirstName_..._LastName) and then NIF:"<<endl;
            cin >> input >>nif;
            cleanCinBuffer();
            Client* client = new Client(input,nif);
            hotel->addClient(client);
        }
        else if (input == "Sort"){

        }
        else if (input == "Search"){
            searchClient(&hotel->getClients());
            cout << "Press enter to proceed";
            cin.ignore();
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

bool LogIn(Hotel* hotel){
    string username, password;
    cout << "Insert Username"<<endl;
    cin >> username;
    cleanCinBuffer();
    cout << "Insert Password"<<endl;
    cin >> password;
    cleanCinBuffer();
    return hotel->logIn(username,password);
}

void system(Hotel* hotel){

    std::string input;

    while (true){
        cout << "Write Help to see commands"<<endl;
        getline(cin,input);

        if (input == "Clients"){
            Clients(hotel);
        }
        else if (input == "Rooms"){

        }
        else if (input == "LogIn"){
            if(LogIn(hotel)) continue;
            else cout<< "Invalid Password" << endl;
        }
        else if (input == "Help"){
            cout << "Valid commands are: Clients, Reservations, LogIn, LogOut, Staff, Providers, Countability, CheckIn, CheckOut and Exit"<<endl;
        }
        else if(input == "CheckIn"){

        }
        else if (input == "CheckOut"){

        }
        else if(input == "LogOut"){

        }
        else if(input == "Staff"){

        }
        else if (input =="Providers"){

        }
        else if (input == "Countability"){

        }
        else if (input == "Exit"){
            break;
        }
        else{
            cout << "Invalid command. Write Help to see possible commands."<<endl;
        }

    }
}

int main(){
    string input;
    while(true){
        cout << "input the name of the hotel file (without .txt)"<< endl;
        cin >> input;
        cleanCinBuffer();
        try {
            Hotel *hotel = new Hotel(input);
            system(hotel);
            break;
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
    return 0;
}
