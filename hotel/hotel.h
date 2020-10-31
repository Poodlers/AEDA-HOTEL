#ifndef HOTEL_H
#define HOTEL_H
#include <string>
#include <vector>
#include "../client/client.h"
#include "../staff/staff.h"
#include "../room/room.h"
#include "../provider/provider.h"

class Hotel{
public:
    Hotel(const unsigned int & floors, const unsigned int & numberOfRooms);
    void addRoom(const Room& room);
    void addStaff(const Staff& staff);

    void sortByPosition();
    void sortBySalary();
    void assignRoom();
    


private:
    std::vector<Client> clients;
    std::vector<Staff> staff;
    std::vector<Room> rooms;
    std::vector<Provider> providers;

    unsigned int freeRooms;
    unsigned int freeSuits;
    unsigned int freeRoomsWithView;
    unsigned int freeRoomsWithOutView;

    const unsigned int floors;
    const unsigned int numberOfRooms;
};
#endif
