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
#include "bst.h"
#include "date.h"
#include "../Vehicles/vehicles.h"
#include <algorithm>

/// Struct which represents a transaction.
///
/// Holds the value and the description of the transaction.
struct Transaction{
    /// Value of the transaction.
    float value;
    /// Description of the transaction.
    std::string description;

    void print();
};

/// \class Hotel
/// Class which represents a hotel.
///
///
/// Defined by clients, staff members, reservations, providers, accounting, rooms, first floor, number of
/// rooms, number of floors, hotel necessities, current date and if the manger is logged in or not).
class Hotel{
public:
    /*HOTEL-BUILDING-AND-SAVING*/

    /// \fn Hotel::Hotel(const std::string &hotelFile)
    /// Hotel Constructor.
    ///
    /// Creates a hotel from a '.txt' file with the correct format.
    /// \see hotel_exemplo.txt
    /// \param hotelFile  name of the '.txt' file without the '.txt' extension, if it's not in the same directory as the '.exe' hotelFile needs to be the whole path to the file.
    /// \exception throws FileNotFound if it can't find the file.
    /// \exception throws HotelFileHasWrongFormat if the file's format is incorrect.
    Hotel(const std::string &hotelFile);

    /// Save Hotel.
    ///
    /// Creates a '.txt' file with the current hotel that can be read by the constructor.
    /// \see hotel_exemplo.txt
    /// \param hotelFile  name of the '.txt' file without the '.txt' extension.
    void saveHotel(const std::string &hotelFile);
    /**/

    /*VEHICLES*/
    void addVehicle(const std::string& plate,const std::string& kmsTravelled,const std::string& capacity);


    /**/

    /*PROVIDERS*/

    /// Adds provider to providers.
    ///
    /// \param provider  provider to add.
    void addProvider(Provider* provider);

    /// Returns providers' vector.
    ///
    /// \return providers.
    std::vector<Provider*> getProviders () const;

    /// Auto buys products so that the hotel's necessities are met.
    void autoBuy();

    /// Buys the product with the product ID productId.
    ///
    /// \param productId  product ID to find.
    /// \exception throws ProductDoesNotExist if product with productId does not exist.
    void buy(const unsigned int &productId);

    /**/

    /*PROFIT*/
    /// Returns costs of running the hotel.
    ///
    /// \return cost of running the hotel (paying salaries + buying products).
    float getCosts() const;

    /// Returns profit of running the hotel.
    ///
    /// \return profit of running the hotel.
    float getProfit() const;

    /// Returns money earned from running the hotel.
    ///
    /// \return money earned by the hotel (payed by clients who checked in).
    float getMoneyEarned() const;

    /// Returns accounting vector.
    ///
    /// \return accounting.
    std::vector<Transaction*> getAccounting() const;

    /// Pays staff.
    void payStaff();
    /**/

    /*RESERVATION*/
    /// Returns reservations' vector.
    ///
    /// \return reservations.
    std::vector<Reservation*>& getReservations();

    /// Searches for reservations.
    ///
    /// Searches for reservations by searchCriteria which agree with value.
    /// \param searchCriteria  criteria used to search for reservations, can be "Date", "ID" or "Room".
    /// \param value  value that the reservation has to agree with.
    /// \example searchReservations("Date",date1) will search for reservations with check in date equal to date1.
    /// \example searchReservations("ID",reservationId) will search for the reservation with ID reservationID.
    /// \example searchReservations("Room",roomID) will search for the reservations for the room with room ID roomId.
    /// \return list of positions in the vector reservations of the found reservations.
    /// \exception throws DateIsNotValid if searching by Date and the value is not a correct date.
    std::vector<int> searchReservations(const std::string& searchCriteria, const std::string & value);

    /// Removes reservation.
    ///
    /// \param reservation pointer to the reservation to remove.
    void deleteReservation(Reservation* reservation);

    /// Removes reservation.
    ///
    /// \param pos position of the reservation to remove.
    void removeReservation(const int& pos);

    /// Makes a reservation.
    ///
    /// Makes a reservation and adds it to the client's reservations and the reservations vector in the hotel.
    /// \param roomId  ID of the room to be occupied.
    /// \param checkIn  check in date for the reservation.
    /// \param checkOut  check out date for the reservation.
    /// \param capacity  size of the reservation.
    /// \param posClient  position in the vector clients of the client making the reservation.
    /// \param reservationId  ID of the reservation (only a real ID when first building the hotel, when making reservations afterwards should be -1 to generate a distinct reservation ID).
    /// \param in  only 1 or -1 when building the hotel, adds the reservation to current reservations or past reservations right away.
    /// \exception throws ClientCantMakeThisReservation when client is trying to make a reservation for a Suite with no previous reservations registered.
    /// \exception throws RoomDoesNotHaveTheNecessaryCapacity if the reservation size is bigger than the room's capacity.
    /// \exception throws AnotherReservationForThisRoomAlreadyExistsAtThisTime if the room is claimed at the time intended for the reservation.
    /// \exception throws ReservationHasInvalidDates if the check in date is after the check out date.
    /// \exception throws RoomDoesNotExist is there is no room with room ID roomId.
    /// \exception throws NoReservationsToCheckIn if when creating the hotel from the file a reservation is marked as checkIn but in reality it can't be checked in.
    void makeReservation(const unsigned int& roomId,Date* checkIn,Date* checkOut, const int& capacity, const int& posClient,const int& reservationId, const int& in);

    void modifyReservation(Reservation *reservation,std::string &roomId, std::string checkIn, std::string checkOut,
                           std::string &capacity, int posClient);
    /**/

    /*ROOMS*/
    /// Adds room.
    ///
    /// \param floor  floor of the room.
    /// \param roomNumber  room number.
    /// \param roomId  room ID.
    /// \param capacity  room capacity.
    /// \param pricePerNight  price per night of the room.
    /// \param type  room type, can be 'Suite', 'NoViewRoom' or 'ViewRoom'.
    /// \exception throws RoomAlreadyExists if the room already exist.
    /// \exception throws NotAnInt if floor is not an integer.
    /// \exception throws NotAPositiveInt if capacity is not a positive integer.
    /// \exception throws FloorDoesNotExist if floor is not a floor of the hotel.
    /// \exception throws NotAPositiveFloat if price is not a positive float.
    /// \exception throws InvalidRoomType if room type is not valid.
    void addRoom(const std::string &floor, const std::string & roomNumber ,const std::string & roomId, const std::string & capacity, const std::string &pricePerNight, const std::string& type);

    /// Removes Room
    ///
    /// \param room pointer to room to remove.
    void removeRoom(Room* room);

    /// Checks if floor is valid.
    ///
    /// \param floor  floor to check.
    /// \exception throws FloorDoesNotExist if floor doesn't exist in the hotel.
    void checkIfFloorIsValid(const unsigned int& floor);

    /// Searches for a specific room.
    ///
    /// \param roomId  room ID of the room to find.
    /// \param roomNumber  room Number of the room to find.
    /// \return position of the room found.
    /// \exception throws NotAPositiveInt if roomId or roomNumber are not positive integers.
    /// \exception throws RoomWithThisRoomIdOrRoomNumberAlreadyExists if there is a room with only the same ID or only the same room number.
    /// \exception throws RoomDoesNotExist if room does not exist.
    int searchForRoom(const std::string& roomId, const std::string& roomNumber);

    /// Searches for room by its roomID.
    ///
    /// \param roomId  room ID of the room to find.
    /// \return position of the room found.
    /// \exception throws RoomDoesNotExist if no room with RoomId does not exist.
    int searchForRoomByRoomId(const unsigned int& roomId);

    /// Returns rooms' vector.
    ///
    /// \return rooms.
    std::vector <Room*>& getRooms();

    /// Modifies room.
    ///
    /// Changes the room's capacity and/or price per night.
    /// \param capacity  new room capacity. If '.' doesn't change.
    /// \param pricePerNight  new price per night. If '.' doesn't change.
    /// \param pos  position of the room to modify in the vector rooms.
    /// \exception throws NotAPositiveInt if capacity is a not a positive integer.
    /// \exception throws NotAPositiveFloat if price is not a positive float.
    void modifyRoom(const std::string& capacity, const std::string& pricePerNight, const int& pos);

    /// Sorts Rooms.
    ///
    /// \param criteria  sorting criteria, can be "Room ID", "Room Number", "Floor", "Capacity", "Price" or "Type".
    /// \param order  sorting order, can be "Ascending" or "Descending".
    /// \exception throws SortingError if order or criteria is wrong.
    void sortRooms(const std::string& criteria,const std::string& order);

    /// Activates Discount.
    ///
    /// \param type  room type to activate discount.
    /// \exception throws AccessRestricted if someone not logged in tries to activate it.
    /// \exception throws InvalidRoomType if type is not a valid room type.
    void activateDiscount(const std::string& type);
    /**/

    /*DATE*/

    /// Returns date.
    ///
    /// \return date.
    Date getDate() const;

    /// Increments date by i days and updates necessary categories.
    ///
    /// Archives expired reservations (check out date has passed).
    /// Restocks providers (first day of the month).
    /// Adds an year to the years of work of all staff members (first day of january of the year).
    /// Checks every five days if the hotel is in need of buying products and warns the user.
    /// If there are products missing every six days it automatically buys them.
    /// Pays staff (last day of the month).
    /// \param i  number of days to increment.
    /// \see Client#archiveExpiredReservations, Provider#restock, payStaff and autoBuy
    void incrementDate(const int& i);

    /*PEOPLE*/

    /// Searches for a person
    ///
    /// \param name  name of the person to find.
    /// \param NIF  NIF of the person to find.
    /// \param type  can be "Client" for finding a client or "Staff" for finding a staff member.
    /// \return position of the person in their own vector.
    /// \note for staff members it returns their position ('Manager', 'Receptionist', 'Respondible' or 'Janitor') in the type variable.
    /// \exception throws NIFIsNotValid if NIF is not valid.
    /// \exception throws ClientWithThisNIFAlreadyExists if there is a client with the selected NIF but a different name.
    /// \exception throws ClientDoesNotExist if client does not exist.
    /// \exception throws StaffMemberWithThisNIFAlreadyExists if there is a staff member with the selected NIF but a different name.
    /// \exception throws StaffMemberDoesNotExist if staff member does not exist.
    int search(const std::string& name, const std::string& NIF, std::string& type);
    /**/

    /*CLIENTS*/
    /// Returns clients' vector.
    ///
    /// \return clients.
    std::vector <Client*>& getClients();

    /// Check in.
    ///
    /// If the client has any reservations to check in at the time it does so.
    /// Increases the hotel necessities according to the number of days of the reservation checked in.
    /// \param pos  position of the client who wants to check in.
    /// \see Client#checkIn
    /// \exception throws NoReservationsToCheckIn if there are no reservations of client in position pos to check in.
    void checkIn(const int& pos);

    /// Check out.
    ///
    /// If the client has any reservations to check out at the time it does so.
    /// \param pos  position of the client who wants to check out.
    /// \see Client#checkOut
    /// \exception throws NoReservationsToCheckOut if there are no reservations to check out.
    void checkOut(const int& pos);

    /// Modifies client.
    ///
    /// Modifies client in position pos.
    /// \param name  new name. If '.' then doesn't change.
    /// \param NIF  new NIF. If '.' then doesn't change.
    /// \param pos  position of the client in the vector clients.
    /// \exception throws NIFIsNotValid if NIF is invalid.
    void modifyClient(const std::string & name, std::string& NIF, const int& pos);

    /// Removes Client.
    ///
    /// \param pos  position of the client to remove.
    void removeClient(int pos);

    /// Removes Client.
    ///
    /// \param client pointer to the client to remove.
    void removeClient(Client* client);

    /// Adds Client.
    ///
    /// \param name  name of the new client.
    /// \param NIF   NIF of the new client.
    /// \exception throws ClientAlreadyExists if client already exists.
    /// \exception throws ClientWithThisNIFAlreadyExists if client already exists with the same NIF.
    void addClient(const std::string& name, const std::string& NIF);

    /// Sorts clients
    ///
    /// \param criteria  sorting criteria, can be "Name", "NIF", "Future reservations", "Past reservations", "Current reservations", "Amount of reservations" or "Most recent reservation".
    /// \param order  sorting order, can be "Ascending" or "Descending".
    /// \exception throws SortingError if criteria or order is incorrect.
    void clientSort(const std::string& criteria,const std::string& order);
    /**/

    /*Staff*/
    /// Returns staff's vector.
    ///
    /// \return staff.
    std::vector <Staff*>& getStaff();

    /// Modifies Staff Member.
    ///
    /// \param name  new name.  If '.' then doesn't change.
    /// \param NIF  new NIF.  If '.' then doesn't change.
    /// \param wage new Wage.  If '.' then doesn't change.
    /// \param pos  position of the staff member in the vector staff.  If '.' then doesn't change.
    /// \param type  type of staff member, can be "Janitor", "Manager" or something else. If something else, will act as if modifying a "Receptionist" or a "Responsibles".
    /// \param shift  for Janitor, can be "night" or "day".  If '.' then doesn't change.
    /// \param evaluation for Manager, can be a number between 1 and 5.  If '.' then doesn't change.
    /// \param password  for Manager.  If '.' then doesn't change.
    /// \exception throws NIFIsNotValid if NIF is invalid.
    /// \exception throws InvalidEvaluation if evaluation is invalid.
    /// \exception throws NotAnInt if evaluation is not an integer.
    /// \exception throws NotAPositiveFloat if wage is not a positive number.
    /// \exception throws InvalidShift if type is Janitor and the shift isn't either night or day.
    void modifyStaffMember(const std::string & name, std::string& NIF, std::string& wage,const int& pos, const std::string& type, const std::string& shift,const std::string& password, const std::string& evaluation);

    /// Removes staff member.
    ///
    /// \param staff pointer to staff member to remove.
    /// \exception throws CantRemoveManager if user tries to remove the manager.
    void removeStaffMember(Staff* staff);

    /// Removes staff member.
    ///
    /// \param pos  position of the staff member to remove.
    /// \exception throws CantRemoveManager if user tries to remove the manager.
    void removeStaffMember(int pos);

    /// Adds staff member
    ///
    /// \param name  name of the new staff member
    /// \param NIF   NIF of the new staff member
    /// \param position  type of the new staff member, can be "Janitor", "Manager", "Receptionist" or "Responsible".
    /// \param password  password for Manager.
    /// \param shift  shift for a Janitor.
    /// \param wage  wage of the new staff member.
    /// \param evaluation evaluation of the Manager.
    /// \exception throws NotAPositiveFloat if wage is not a positive number.
    /// \exception throws InvalidShift if the new staff member is a janitor and the shift isn't either night or day.
    /// \exception throws InvalidPosition if type isn't one of the possible ones.
    /// \exception throws StaffMemberAlreadyExists if staff member already exists.
    /// \exception throws InvalidEvaluation if evaluation is invalid.
    /// \exception throws NotAnInt if evaluation is not an integer.
    /// \warning adding a manager switches out the current manager for the new one.
    void addStaffMember(const std::string& name, const std::string& NIF, const std::string& type,const std::string& password, const std::string& shift, const std::string& wage, const std::string& evaluation);

    /// Sorts staff.
    ///
    /// \param criteria  sorting criteria, can be "Name", "NIF", "Wage", "Years of service" or "Position".
    /// \param order  sorting order, can be "Ascending" or "Descending".
    /// \exception throws SortingError if criteria or order is incorrect.
    void staffSort(const std::string& input,const std::string& order1);

    ///Reassigns or assigns for the first time floors between responsibles.
    void assignFloorsToResponsibles();
    /**/

    /*LOGIN-LOGOUT*/
    /// Log in.
    ///
    /// \param name  name to log In.
    /// \param password  password to log in.
    /// \exception throws IncorrectCredentials if name is not the mangers name and/or password is not the managers password.
    /// \exception throws AlreadyLoggedIn if user is already logged in.
    void logIn(const std::string& name, const std::string& password);

    /// Log out.
    ///
    /// \exception throws NotLoggedIn if user is not logged in.
    void logOut();

    /// Returns manager's name.
    ///
    /// \return managers name.
    std::string getManagerName() const;

    /// Returns manager's password.
    ///
    /// \return managers password.
    std::string getManagerPassword() const;

    /// Checks if someone is logged in.
    ///
    /// \return true if someone is logged in and false if not.
    bool getLoggedInState() const;
    /**/

    /// Reduces the necessity of type 'type' by one.
    ///
    /// \param type type of the necessity.
    void reduceNecessity(std::string type);

    /// Returns the cleaning necessity.
    ///
    /// \return cleaningNecessity.
    unsigned int getCleaningNecessity() const;

    /// Returns the catering necessity.
    ///
    /// \return cateringNecessity.
    unsigned int getCateringNecessity() const;

    /// Returns the other necessity.
    ///
    /// \return otherNecessity.
    unsigned int getOtherNecessity() const;

    /// Adds transaction.
    ///
    /// \param transaction transaction to add.
    void addTransaction(Transaction* transaction);

    /// Remove transaction.
    ///
    /// \param pos position of the transaction to remove.
    void removeTransaction(const int& pos);

    /// Adds reservation.
    ///
    /// \param reservation reservation to add
    void addReservation(Reservation* reservation);

    /// Remove provider.
    ///
    /// \param pos position of the provider to remove.
    void removeProvider(const int & pos);

    /// Change logged in state.
    ///
    /// \param state state to change to.
    void setLoggedInState(const bool& state);

    /// Change cleaning necessity.
    ///
    /// \param necessity necessity to change to.
    void setSetCleaningNecessity(const int& necessity);

    /// Change catering necessity.
    ///
    /// \param necessity necessity to change to.
    void setSetCateringNecessity(const int& necessity);

    /// Change other necessity.
    ///
    /// \param necessity necessity to change to.
    void setSetOtherNecessity(const int& necessity);

    /// Returns number of floors.
    ///
    /// \return number of floors.
    int getNumberOfFloors() const;

    /// Returns number of rooms.
    ///
    /// \return number of rooms.
    int getNumberOfRooms() const;

    /// Returns first floor.
    ///
    /// \return first floor.
    int getFirstFloor() const;

private:
    /// Vector of the hotel's clients.
    std::vector <Client*> clients;
    /// Vector of the hotel's staff members.
    std::vector<Staff* > staff;
    /// Vector of the hotel's rooms.
    std::vector<Room*> rooms;
    /// Vector of the hotel's reservations.
    std::vector<Reservation*> reservations;
    /// Vector of the hotel's providers.
    std::vector<Provider*> providers;
    /// Vector of the transactions made by the hotel.
    std::vector<Transaction*> accounting;

    BST<Vehicle> fleet;
    /// Logged in state.
    /// True if the manager is logged in, false otherwise.
    bool loggedIn = false;

    /// Cleaning necessity.
    int cleaningNecessity;
    /// Catering necessity.
    int cateringNecessity;
    /// Other necessity.
    int otherNecessity;
    /// Number of floors of the hotel.
    unsigned int numberOfFloors;
    /// Number of rooms of the hotel.
    unsigned int numberOfRooms;
    /// Number of the first floor.
    int firstFloor;

    /// Current date.
    Date date;
};


/**
  \file "..\cmake-build-debug\hotel_exemplo.txt"
  File used to build a hotel, must have the following format:
  ### Example
  ~~~~~~~~~~~~~~~~~~~.cpp
      //Hotel-File
      //"in program date of the state of the hotel"
      //"number of floors"
      //"first floor with rooms"
      //Rooms
      //"floor" "room number" "capacity" "price" "type"
      //(...) more rooms
      //Staff
      //"name" "NIF" "first year of work" "wage" "position" "shift"/"password"/nothing "evaluation"/nothing
      //(...) more staff
      //Client
      //"name" "NIF" "reservation" (… more reservations)
      //(...) more clients
      //Transactions
      //"value" "description"
      //Necessities
      //"cleaning necessity"
      //"catering necessity"
      //"other necessity"
      //End

      //"reservation" :"room ID","Check In date","Check Out date","Reservation ID","Reservation Size","Vector marker"(without spaces)
  ~~~~~~~~~~~~~~~~~~~
 */



#endif
