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
    void saveHotel(const std::string &hotelFile);

    void addRoom(const Room& room);

    void checkIfFloorIsValid(unsigned int floors);
    int searchForRoom(unsigned int roomId, unsigned int roomNumber);

    void getCosts();
    void getProfit();

    void buyProducts();

    void makeReservation(const unsigned int& roomId,Date* checkIn,Date* checkOut, const int& capacity, const int& posClient,const int& reservationId, const bool& in);

    Date getDate() const;
    void incrementDate(const int& i);

    std::vector<Room*>& getRooms();

    /*PEOPLE*/
    int search(const std::string& name, const std::string& NIF,std::string& type);
    /**/

    /*CLIENTS*/
    std::vector<Client*>& getClients();

    void modifyClient(const std::string & name, std::string& NIF, const int& pos);
    void removeClient(const int& pos);
    void addClient(const std::string& name, const std::string& NIF);
    void clientSort(const std::string& input,const std::string& order1);
    /**/

    /*Staff*/
    std::vector<Staff*>& getStaff();

    void modifyStaffMember(const std::string & name, std::string& NIF, const int& pos, const std::string& type, const std::string& shift,const std::string& password);
    void removeStaffMember(const int& pos);
    void addStaffMember(const std::string& name, const std::string& NIF, const std::string& type, const std::string& password, const std::string& shift, const std::string& wage);
    void staffSort(const std::string& input,const std::string& order1);
    void assignFloorsToResponsibles();
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
