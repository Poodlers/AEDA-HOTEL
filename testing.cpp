#include "hotel/hotel.h"
#include "provider/provider.h"
#include "product/product1.h"
#include "person/client/client.h"
#include "room/room.h"
#include "person/staff/staff.h"
#include <string>
#include<iostream>
using namespace std;

template <class Comparable>
int sequentialSearch(const vector<Comparable> &v, Comparable x)
{
    for (unsigned int i = 0; i < v.size(); i++)
        if (v[i] == x)
            return i;   // encontrou
    return -1;     // não encontrou
}

void cleanCinBuffer(){
    cin.clear();
    cin.ignore(1000000000,'\n');
}

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
    //should display rooms and their desponibility
    //be able to add rooms or remove them?
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
int main(){
    string input;

    cout << "input the name of the hotel file (without .txt)"<< endl;
    cin >> input;
    cleanCinBuffer();

    Hotel* hotel = new Hotel(input);

    while (true){
        cout << "Write Help to see commands"<<endl;
        getline(cin,input);
        if (!hotel->getLoggedInState()){
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
                cout << "Valid commands are: Clients, Reservations, LogIn and Exit"<<endl;
            }
            else if (input == "Exit"){
                break;
            }
            else{
                cout << "Invalid command. Write Help to see possible commands."<<endl;
            }
        }
        else{

        }

    }
    return 0;
}
