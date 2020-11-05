#include "hotel/hotel.h"
#include "provider/provider.h"
#include "product/product1.h"
#include "person/client/client.h"
#include "room/room.h"
#include "person/staff/staff.h"
#include <string>
#include<iostream>
using namespace std;

void Clients(Hotel *hotel){
    for(Client* client: hotel->getClients()){
        client->print();
    }
    while(true){
        string input;
        if (input == "Help"){
            cout << "Valid commands are: Modify, Remove, Add, Sort, Search, Back and Help "<<endl;
        }
        else if(input == "Modify"){

        }
        else if(input == "Remove"){

        }
        else if (input == "Add"){

        }
        else if (input == "Sort"){

        }
        else if (input == "Search"){

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
    cout << "Insert Password"<<endl;
    cin >> password;
    return hotel->logIn(username,password);
}
int main(){
    string input;

    cout << "input the name of the hotel file (without .txt)"<< endl;
    cin >> input;
    Hotel* hotel = new Hotel(input);

    while (true){
        cout << "Write Help to see commands"<<endl;
        getline(cin,input);
        if (!hotel->getLoggedInState()){
            if (input == "Clients"){

            }
            else if (input == "Rervations"){

            }
            else if (input == "Rooms"){

            }
            else if (input == "LogIn"){
                if(LogIn(hotel)) continue;
                else cout<< "Invalid Password" << endl;
            }
            else if (input == "Help"){
                cout << "Valid commands are: Clients, Reservations, Rooms, LogIn and Exit"<<endl;
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
