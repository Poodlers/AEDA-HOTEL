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

/**
  \file "C:\Users\Joana\Documents\Uni\Algoritmos e Estruturas de dados\Projeto\aeda_hotel_projeto\cmake-build-debug\hotel_exemplo.txt"
  File used to build a hotel, must have the following format:
  ### Example
  ~~~~~~~~~~~~~~~~~~~.cpp
      //Hotel-File
      //#number of floors
      //#first floor with rooms
      //Rooms
      //#floor #room number #capacity #price #type (can be Suite, NoViewRoom or ViewRoom [case sensitive])
      //(...) more rooms
      //Staff
      //#name[can have spaces, only two names] #NIF[must be valid] #first year of work #wage #position (can be Janitor, Responsible, Receptionist or Manager[only one manager per hotel] [case sensitive]) if Janitor #shift (can be night or day [case sensitive]) else if Manager #password
      //(...) more staff
      //Client
      //#name[can have spaces, only two names] #NIF[must be valid] #reservations[separated by a space]
      //                                                          (#room ID,#Check In date[dd-mm-yyyy],#Check Out date[dd-mm-yyyy],#Reservation ID,#Reservation Size,#0 if in history or future 1 if in current reservations[client is currently at the hotel])-> no spaces in between
      //                                                           [-Can have no reservations]
      //(...) more clients
      //End
  ~~~~~~~~~~~~~~~~~~~
 */

typedef struct Transaction{
    float value;
    std::string description;
};

/// Class which represents a hotel
///
/// Holds the all the information of a hotel (clients, staff members, reservations, providers, rooms, products bought, floors, ...)
class Hotel{
public:
    /*HOTEL-BUILDING-AND-SAVING*/

    /// Hotel Initializer
    ///
    /// Creates a hotel from a .txt file with the correct format
    /// \see hotel_exemplo.txt
    /// \param hotelFile - name of the '.txt' file with out the '.txt', if it's not in the same directory as the .exe needs to be path\file
    /// \exception throws FileNotFound if it can't find the file.
    /// \exception throws HotelFileHasWrongFormat if the file's format is incorrect.
    Hotel(const std::string &hotelFile);

    /// Save Hotel
    ///
    /// Creates a .txt with the current hotel that can be read by the constructor
    /// \see hotel_exemplo.txt
    /// \param hotelFile - name of the '.txt' file with out the '.txt'
    void saveHotel(const std::string &hotelFile);
    /**/

    /*PROVIDERS*/
    void buyProducts();

    /// Adds a provider to providers
    ///
    /// \param provider to add
    void addProvider(Provider* provider);

    ///Returns the providers' vector
    ///
    /// \return providers
    std::vector<Provider*> getProviders () const;

    ///Auto buys a random number of the cheapest products
    void autoBuy();

    ///Buys the product with the product ID productId
    ///
    /// \param productId - product ID to find
    void buy(const unsigned int &productId);

    std::vector<Product*> getProductsBought() const;

    /**/

    /*PROFIT*/
    int getCosts() const;

    int getProfit() const;

    int getMoneyEarned() const;


    void payStaff();
    /**/

    /*RESERVATION*/
    ///Returns the vector reservations
    ///
    /// \return reservations vector
    std::vector<Reservation*> getReservations() const;

    ///Searches for reservations
    ///
    /// searches for reservations by searchCriteria which agree with value.
    /// \param searchCriteria - criteria used to search for reservations, can be "Date", "ID" or "Room".
    /// \param value - value that the reservation has to agree with
    /// \example searchReservations("Date",date1) will search for reservations with check in date equal to date1.
    /// \example searchReservations("ID",reservationId) will search for the reservation with ID reservationID.
    /// \example searchReservations("Room",roomID) will search for the reservations for the room with room ID roomId.
    /// \return list of positions in the vector reservations of the found objects.
    std::vector<int> searchReservations(const std::string& searchCriteria, const std::string & value);

    ///Makes a reservation
    ///
    ///Makes a reservation and ads it to the client's reservations an the reservations vector in the hotel
    /// \param roomId - ID of the room to be reserved
    /// \param checkIn - Check In date for the reservation
    /// \param checkOut - Check Out date for the reservation
    /// \param capacity - size of the reservation
    /// \param posClient - position in the vector clients of the client making the reservation
    /// \param reservationId - id of the reservation (only a real ID when first building the hotel, when making reservations after should be -1
    /// \param in - only true when building the hotel, adds the reservation to current reservations right away
    /// \exception throws ClientCantMakeThisReservation when client is trying to make a reservation for a Suite with no previous reservations
    /// \exception throws RoomDoesNotHaveTheNecessaryCapacity if the reservation size is bigger then the room's capacity
    /// \exception throws AnotherReservationForThisRoomAlreadyExistsAtThisTime if the room is reserved at the time intended
    /// \exception throws ReservationHasInvalidDates if the Check In date is after the Check Out date
    /// \exception throws RoomDoesNotExist is there is no room with room ID roomId
    void makeReservation(const unsigned int& roomId,Date* checkIn,Date* checkOut, const int& capacity, const int& posClient,const int& reservationId, const bool& in);
    /**/

    void deleteReservation(Reservation* reservation);

    /*ROOMS*/
    /// Adds a room
    ///
    /// \param floor - floor of the room
    /// \param roomNumber - room number
    /// \param roomId - room ID
    /// \param capacity - room capacity
    /// \param pricePerNight - price per night of the room
    /// \param type - room type
    /// \exception throws RoomAlreadyExists> if the room already exist
    /// \exception throws NotAnInt if floor is not an integer
    /// \exception throws NotAPositiveInt if capacity is a not a positive integer
    /// \exception throws FloorDosNotExist if floor is not a floor of the hotel
    /// \exception throws NotAPositiveFloat if price is not a positive float
    void addRoom(const std::string &floor, const std::string & roomNumber ,const std::string & roomId, const std::string & capacity, const std::string &pricePerNight, const std::string& type);

    ///Checks if floor is valid
    ///
    /// \param floor - floor to check
    /// \exception throws FloorDosNotExist if floor doesn't exist in the hotel
    void checkIfFloorIsValid(const unsigned int& floor);

    ///Searches for a specific room
    ///
    /// \param roomId - room ID of the room to find
    /// \param roomNumber - room Number of the room to find
    /// \return position of the room found
    /// \exception throws NotAPositiveInt if capacity is a not a positive integer if roomId or roomNumber
    /// \exception throws RoomWithThisRoomIdOrRoomNumberAlreadyExists if has only the same ID or only the same number
    /// \exception throws RoomDoesNotExist is room does not exist
    int searchForRoom(const std::string& roomId, const std::string& roomNumber);

    ///Searches for room by its roomID
    ///
    /// \param roomId - room ID of the room to find
    /// \return position of the room found
    /// \exception throws RoomDoesNotExist if no room with RoomId exists
    int searchForRoomByRoomId(const unsigned int& roomId);

    ///Returns rooms vector
    ///
    /// \return rooms vector
    std::vector <Room*>& getRooms();

    ///Modifies a room
    ///
    /// Changes the room's capacity and price per night
    /// \param capacity - room capacity, if '.' doesn't change
    /// \param pricePerNight - price per night, if '.' doesn't change
    /// \param pos - position of the room to modify in the vector rooms
    /// \exception throws NotAPositiveInt if capacity is a not a positive integer
    /// \exception throws NotAPositiveFloat if price is not a positive float
    void modifyRoom(const std::string& capacity, const std::string& pricePerNight, const int& pos);

    ///Sorts Rooms
    ///
    /// \param criteria - sorting criteria can be: Room ID, Room Number, Floor, Capacity, Price and Type
    /// \param order - sorting order can be: Ascending or Descending
    /// \exception throws SortingError if order or criteria is wrong
    void sortRooms(const std::string& criteria,const std::string& order);

    ///Activate Discount
    ///
    /// \param type - room type to activate the discount
    /// \exception throws AccessRestricted if someone not logged in tries to activate it
    /// \exception throws InvalidRoomType if type is not a valid room type
    void activateDiscount(const std::string& type);
    /**/

    /*DATE*/

    ///Returns the date
    ///
    /// \return date
    Date getDate() const;

    /// Increments the date by i days
    ///
    /// Archives expired reservations
    /// Restocks providers if it's the first day of the month
    /// \param i - number of days to increment
    /// \see Client#archiveExpiredReservations and Provider#restock
    void incrementDate(const int& i);

    /*PEOPLE*/
    ///Searches for a person
    ///
    /// \param name - name of the person to find
    /// \param NIF - NIF of the person to find
    /// \param type - can be "Client" for finding a client or "Staff" for finding a staff member
    /// \return position of the person in its vector
    /// \note for staff members return their position in the type variable
    /// \exception throws NIFIsNotValid if NIF is not valid
    /// \exception throws ClientWithThisNIFAlreadyExists if there is a client with NIF with a different name
    /// \exception throws ClientDoesNotExist if client does not exist
    /// \exception throws StaffMemberWithThisNIFAlreadyExists if is a staff member with NIF with a different name
    /// \exception throws StaffMemberDoesNotExist if staff member does not exist
    int search(const std::string& name, const std::string& NIF, std::string& type);
    /**/

    /*CLIENTS*/
    ///Returns the vector clients
    ///
    /// \return vector clients
    std::vector <Client*>& getClients();

    ///Check In
    ///
    /// \param pos - position of the client who wants to check In
    /// \see Client#checkIn
    /// \exception throws NoReservationsToCheckIn if there are no reservations of client in position pos to check In
    void checkIn(const int& pos);

    ///Check Out
    ///
    /// \param pos - position of the client who wants to check Out
    /// \see Client#checkOut
    /// \exception throws NoReservationsToCheckOut if there are no reservations to check Out
    void checkOut(const int& pos);

    ///Modifies a client
    ///
    /// Modifies the client in position pos
    /// \param name - name to change to, if '.' then doesn't change
    /// \param NIF  - NIF to change to, if '.' then doesn't change
    /// \param pos - position of the client in the vector clients
    /// \exception throws NIFIsNotValid if NIF is invalid
    void modifyClient(const std::string & name, std::string& NIF, const int& pos);

    ///Removes a client
    ///
    /// \param pos - position of the client to remove
    void removeClient(const int& pos);

    ///Adds Client
    ///
    /// \param name - name of the new client
    /// \param NIF  - NIF of the new client
    /// \exception throws ClientAlreadyExists if client already exists
    /// \exception throws ClientWithThisNIFAlreadyExists if a client already exists with the same NIF
    void addClient(const std::string& name, const std::string& NIF);

    ///Sorts vector clients
    ///
    /// \param criteria - sorting criteria can be: name, NIF, Amount of future reservations, Amount of past reservations, Current reservations, Amount of reservations and Most Recent Reservation
    /// \param order - ascending and descending can be: Ascending or Descending
    /// \exception throws SortingError if criteria or order is incorrect
    void clientSort(const std::string& criteria,const std::string& order);
    /**/

    /*Staff*/
    ///Returns the staff vector
    ///
    /// \return vector staff
    std::vector <Staff*>& getStaff();

    ///Modifies a Staff Member
    ///
    /// \param name - new name
    /// \param NIF - new NIF
    /// \param pos - position of the staff member in the vector staff
    /// \param type - type of staff member, can be: Janitor, Manager or something else if something else will act as if modifying a receptionist or a responsible
    /// \param shift - for Janitor, can be: night or day
    /// \param password - for manager
    /// \exception throws NIFIsNotValid if NIF is invalid
    void modifyStaffMember(const std::string & name, std::string& NIF, const int& pos, const std::string& type, const std::string& shift,const std::string& password);

    ///Removes a staff member
    ///
    /// \param pos - position of the staff member to remove
    void removeStaffMember(const int& pos);

    ///Adds a staff member
    ///
    /// \param name - name of the new staff member
    /// \param NIF  - NIF of the new staff member
    /// \param position - type of the new staff member, can be: Janitor, Manager, Receptionist or Responsible
    /// \param password - password for a manager
    /// \param shift - shift for a Janitor
    /// \param wage - wage of the new staff member
    /// \exception throws NotAPositiveFloat if wage is invalid
    /// \exception throws InvalidShift if the new staff member is a janitor and the shift isn't either night or day
    /// \exception throws InvalidPosition if type isn't one of the possible ones
    /// \exception throws StaffMemberAlreadyExists if staff member already exists
    void addStaffMember(const std::string& name, const std::string& NIF, const std::string& position, const std::string& password, const std::string& shift, const std::string& wage);

    ///Sorts vector staff
    ///
    /// \param criteria - sorting criteria can be: Name, NIF, Wage, Years of service and Position
    /// \param order - ascending and descending can be: Ascending or Descending
    /// \exception throws SortingError if criteria or order is incorrect
    void staffSort(const std::string& input,const std::string& order1);

    ///Reassigns or assigns for the first time floors between responsibles
    void assignFloorsToResponsibles();
    /**/

    /*LOGIN-LOGOUT*/
    ///Log In
    ///
    /// \param name - name to log In
    /// \param password - password to log in
    /// \exception throws IncorrectCredentials if name is not the mangers name and/or password is not the managers password
    /// \exception throws AlreadyLoggedIn if user is already logged in
    void logIn(const std::string& name, const std::string& password);

    ///Log Out
    ///
    ///\exception throws NotLoggedIn if user is not logged in
    void logOut();

    ///Gets the manager's name
    ///
    /// \return the managers name
    std::string getManagerName() const;

    ///Gets the manager's password
    ///
    /// \return the managers passwor
    std::string getManagerPassword() const;

    ///Checks if someone is logged in
    ///
    /// \return true if someone is logged in and false if not
    bool getLoggedInState() const;
    /**/

    int getNumberOfFloors() const;

    int getFirstFloor() const;

    void ReservationQualityControl(const unsigned int& roomId,Date* checkIn,Date* checkOut, const int& capacity,const int& reservationId,Client* client);
private:
    ///Vector of the hotel's clients
    std::vector <Client*> clients;
    ///Vector of the hotel's staff members
    std::vector<Staff* > staff;
    ///Vector of the hotel's rooms
    std::vector<Room*> rooms;
    ///Vector of the hotel's reservations
    std::vector<Reservation*> reservations;
    ///Vector of the hotel's providers
    std::vector<Provider*> providers;
    ///Vector of the products bought by the hotel
    std::vector<Product*> productsBought;
    ///Vector with the transactions make in the hotel
    std::vector<Transaction*> accountability;

    ///Logged in state
    ///True if the manager is logged in, false otherwise
    bool loggedIn = false;

    ///Number of floors of the hotel
    unsigned int numberOfFloors;
    ///Number of rooms of the hotel
    unsigned int numberOfRooms;
    ///Number of the first floor
    int firstFloor;

    ///Current date
    static Date date;
};


void edit(Client* client);
void edit(Receptionist* receptionist);
void edit(Responsible* responsible,Hotel* hotel);
void edit(Manager* manager);
void edit(Janitor* janitor);
void edit(Reservation* reservation,Hotel* hotel, Client* client);
void edit(Room* room,Hotel* hotel);

#endif
