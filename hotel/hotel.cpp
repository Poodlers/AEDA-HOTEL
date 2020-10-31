#include "hotel.h"
#include<fstream>
#include<sstream>

Hotel::Hotel(const std::string &hotelFile) {
    std::ifstream file;
    std::string getData;
    std::stringstream ss;

    file.open(hotelFile +".txt");
    //throw exception if file can't be opened

    getline(file,getData);
    //if getData != Hotel-File throw exception file is wrong

    getline(file,getData);
    //if getData <0 or == Rooms or not int or file ends throw exception
    this->floors = std::stoi(getData);

    getline(file,getData);
    //if == Rooms or not int or file ends throw exception
    this->firstFloor = std::stoi(getData);

    getline(file,getData);
    //if not Rooms or end of file throw exception

    int floor;
    unsigned int roomNumber;
    unsigned int roomId;
    unsigned int capacity;
    float price;
    std::string type;

    while(getline(file,getData) && getData!="Staff"){
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
    }
    this->freeRooms = rooms.size();
    this->numberOfRooms = rooms.size();
    ss.clear();

    getline(file,getData);
    //if not Staff or end of file throw exception

    std::string name;
    unsigned int NIF;
    float salary;
    std::string position;
    std::string shift;
    bool shift1;
    std::string password;

    while(getline(file,getData) && getData!="Client"){
        ss<<getData;
        ss >> name >> NIF >> salary >> position;
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
    }

    getline(file,getData);
    //if not Client or end of file throw exception

    std::string reserv;
    Reservation reserv1;
    Date dateIn, dateOut;


    while(getline(file,getData)){
        ss<<getData;
        ss>>name>>NIF;
        Client* client = new Client(name,NIF);
        
    }

    file.close();

}
