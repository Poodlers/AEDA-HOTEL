#ifndef HOTEL_H
#define HOTEL_H
#include <string>
#include <vector>
#include "../human/client/client.h"
#include "../human/staff/staff.h"
#include "../room/room.h"
#include "../provider/provider.h"
#include "../product/product1.h"

class Hotel{
public:
    Hotel(const std::string &hotelFile);
    void addRoom(const Room& room);
    void addStaff(const Staff& staff);
    void addClient(const Client& client);
    void makeReservation(const Reservation& restart);

    void assignFloorsToResponsibles();

    void sortByStaffPosition();
    void sortStaffBySalary();
    void sortReservationsByDay();
    void sortCurrentReservations();
    void sortReservationsFromNewClients();

    void getCosts();
    void getProfit();

    void buyProducts();
    std::vector<Client*>& getClients();
    std::vector<Staff*>& getStaff();
    std::vector<Room*>& getRooms();
    std::string getManagerName();
    std::string getManagerPassword();

    bool logIn(const std::string& name, const std::string& password);
    void logOut();

private:
    std::vector<Client*> clients;
    std::vector<Staff*> staff;
    std::vector<Room*> rooms;
    std::vector<Provider*> providers;
    std::vector<Product*> productsBought;

    bool loggedIn = false;

    unsigned int freeRooms;
    unsigned int freeSuits = 0;
    unsigned int freeRoomsWithView = 0;
    unsigned int freeRoomsWithOutView = 0;

    unsigned int floors;
    unsigned int numberOfRooms;
    int firstFloor;
};

#endif
