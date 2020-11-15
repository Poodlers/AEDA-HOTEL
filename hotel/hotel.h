#ifndef HOTEL_H
#define HOTEL_H
#include <string>
#include <vector>
#include "../person/client/client.h"
#include "../person/staff/staff.h"
#include "../room/room.h"
#include "../provider/provider.h"
#include "../product/product1.h"
#include "reservation.h"
#include "../GUI/utils.h"
#include <algorithm>

class Hotel{
public:
    Hotel(const std::string &hotelFile);
    void addRoom(const Room& room);
    void addStaff(const Staff& staff);


    void assignFloorsToResponsibles();

    void sortByStaffPosition();
    void sortStaffBySalary();
    void sortReservationsByDay();
    void sortCurrentReservations();
    void sortReservationsFromNewClients();

    void checkIfFloorIsValid(unsigned int floors);
    void searchForRoom(unsigned int roomId, unsigned int roomNumber);

    void getCosts();
    void getProfit();

    void buyProducts();

    Date getDate() const;
    void incrementDate(const int& i);

    std::vector<Staff*>& getStaff();
    std::vector<Room*>& getRooms();

    /*PEOPLE*/
    int search(const std::string& name, const std::string& NIF,const std::string& type);
    /**/

    /*CLIENTS*/
    std::vector<Client*>& getClients();

    void makeReservation(const Reservation& restart);

    void modifyClient(const std::string & name, std::string& NIF, const int& pos);
    void removeClient(const int& pos);
    void addClient(const std::string& name, const std::string& NIF);
    void clientSort(const std::string& input,const std::string& order1);
    /**/

    /*LOGIN-LOGOUT*/
    void logIn(const std::string& name, const std::string& password);
    void logOut();
    std::string getManagerName() const;
    std::string getManagerPassword() const;
    bool getLoggedInState() const;
    /**/

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

    unsigned int numberOfFloors;
    unsigned int numberOfRooms;
    int firstFloor;

    static Date date;
};

#endif
