#include "hotel.h"
#include<fstream>
#include<sstream>

Hotel::Hotel(const std::string &hotelFile) {
    std::ifstream file;
    std::string getData;
    std::stringstream ss;

    file.open(hotelFile +".txt");
    //throw exception if file can't be opened

    std::getline(file,getData);

    //if getData != Hotel-File throw exception file is wrong

    std::getline(file,getData);
    //if getData <0 or == Rooms or not int or file ends throw exception
    this->floors = std::stoi(getData);

    std::getline(file,getData);
    //if == Rooms or not int or file ends throw exception
    this->firstFloor = std::stoi(getData);

    std::getline(file,getData);
    //if not Rooms or end of file throw exception

    int floor;
    unsigned int roomNumber;
    unsigned int roomId;
    unsigned int capacity;
    float price;
    std::string type;

    while(std::getline(file,getData) && getData!="Staff"){
        ss<<getData;
        ss >> floor >> roomNumber >> roomId >> capacity>> price>>type;
        if (type == "Suite"){
            Suite* suite = new Suite(floor,roomNumber,roomId,capacity,price);
            rooms.push_back(suite);
            freeSuits ++;
        }
        else if(type == "ViewRoom"){
            ViewRoom* viewRoom = new ViewRoom(floor,roomNumber,roomId,capacity,price);
            rooms.push_back(viewRoom);
            freeRoomsWithView ++;
        }
        else if (type == "NoViewRoom"){
            NoViewRoom* noViewRoom = new NoViewRoom(floor,roomNumber,roomId,capacity,price);
            rooms.push_back(noViewRoom);
            freeRoomsWithOutView++;
        }
        else{
            //throw exception
        }
        ss.clear();
    }
    this->freeRooms = rooms.size();
    this->numberOfRooms = rooms.size();

    std::getline(file,getData);
    //if not Staff or end of file throw exception

    std::string name;
    unsigned int NIF;
    float salary;
    std::string shift;
    bool shift1;
    std::string password;

    while(std::getline(file,getData) && getData!="Client"){
        ss<<getData;
        ss >> name >> NIF >> salary >> type;
        //switch fixe aqui
        if (type == "Receptionist"){
            Receptionist* receptionist = new Receptionist(name,NIF,salary);
            staff.push_back(receptionist);

        }
        else if(type == "Responsible"){
            Responsible* responsible = new Responsible(name,NIF,salary);
            staff.push_back(responsible);
        }
        else if (type == "Janitor"){
            ss >> shift;

            if (shift == "night") shift1 == false;
            else if (shift == "day") shift1 = true;
            else {}//exception

            Janitor* janitor = new Janitor(shift1,name,NIF,salary);
            staff.push_back(janitor);
        }

        else if (type == "Manager"){
            ss >> password;

            Manager* manager = new Manager(name,NIF,salary,password);
            staff.push_back(manager);
        }
        ss.clear();
    }

    //if not Client or end of file throw exception

    std::string reservation1;

    while(std::getline(file,getData) && getData != "End"){
        ss<<getData;
        ss>>name>>NIF;
        Client* client = new Client(name,NIF);
        while(ss>>reservation1){
            Reservation* reservation = new Reservation(reservation1);
            client->addToHistory(reservation);
        }
        this->clients.push_back(client);
        ss.clear();
    }

    file.close();

}

bool Hotel::logIn(const std::string &name, const std::string &password) {
    if(name == getManagerName() && password == getManagerPassword()){
        loggedIn = true;
        return true;
    }
    return false;
}

void Hotel::logOut(){
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