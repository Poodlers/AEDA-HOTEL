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
    /*HOTEL-BUILDING-AND-SAVING*/
    Hotel(const std::string &hotelFile);
    void addRoom(Room* room);
    void addStaff(Staff* staff);
    void addClient(Client* client);
    void eraseClient(Client* client);
    void eraseStaff(Staff* staff);
    void eraseRoom(Room* room);
    void makeReservation(const Reservation& restart);
    void saveHotel(const std::string &hotelFile);
    /**/

    void getCosts();
    void getProfit();

    void buyProducts();

    /*RESERVATION*/
    std::vector<Reservation*> getReservations() const;
    std::vector<int> searchReservations(const std::string& type, const std::string & criteria);
    void makeReservation(const unsigned int& roomId,Date* checkIn,Date* checkOut, const int& capacity, const int& posClient,const int& reservationId, const bool& in);
    /**/
    /*ROOMS*/

    void addRoom(const std::string &floor, const std::string & roomNumber ,const std::string & roomId, const std::string & capacity, const std::string &pricePerNight, const std::string& type);
    void checkIfFloorIsValid(const unsigned int& floors);
    int searchForRoom(const std::string& roomId, const std::string& roomNumber);
    int searchForRoomByRoomId(const int& roomId);

    std::vector <Room*>& getRooms();
    void modifyRoom(const std::string& capacity, const std::string& pricePerNight, const int& pos);
    void sortRooms(const std::string& input,const std::string& order1);
    void activateDiscount(const std::string& type);
    /**/

    /*DATE*/
    Date getDate() const;
    void incrementDate(const int& i);


    /*PEOPLE*/
    int search(const std::string& name, const std::string& NIF,std::string& type);
    /**/

    /*CLIENTS*/
    std::vector <Client*>& getClients();

    void checkIn(const int& pos);
    void checkOut(const int& pos);
    void modifyClient(const std::string & name, std::string& NIF, const int& pos);
    void removeClient(const int& pos);
    void addClient(const std::string& name, const std::string& NIF);
    void clientSort(const std::string& input,const std::string& order1);
    /**/

    /*Staff*/
    std::vector <Staff*>& getStaff();

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
    std::vector <Client*> clients;
    std::vector<Staff* > staff;
    std::vector<Room*> rooms;
    std::vector<Reservation*> reservations;
    std::vector<Provider*> providers;
    std::vector<Product*> productsBought;

    bool loggedIn = false;

    unsigned int numberOfFloors;
    unsigned int numberOfRooms;
    int firstFloor;

    static Date date;
};


void edit(Client* client);
void edit(Receptionist* receptionist);
void edit(Responsible* responsible);
void edit(Manager* manager);
void edit(Janitor* janitor);
void edit(Reservation* reservation);
void edit(Room* room);

#endif
