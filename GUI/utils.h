#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <map>
#include <string>
#include <vector>
#include "../exceptions/exceptions.h"
#include "../hotel/reservation.h"
#include "../hotel/hotel.h"

/// Clears the screen
void clearscreen();

/// Prints time
///
/// \param date current date
/// \param map_month matches integers to month
void printTime(Date date, std::map<int,std::string> &map_month);

/// Sets the cursor position to (x,y)
///
/// \param x x coordinate
/// \param y y coordinate
void gotoxy(int x, int y);

/// Initializes console attributes
///
/// \param fdwMode
/// \param hin
/// \param hout
/// \param cci
void SetConsoleDefinitions(DWORD &fdwMode,HANDLE &hin,HANDLE &hout, CONSOLE_CURSOR_INFO &cci);

/// Initializes matching integers for each month of the year
///
/// \param map_month a map of months and integers
void fill_month_map(std::map<int,std::string> &map_month);

/// Gets a string input
///
/// \param input string returned by reference
/// \param x x coordinate
/// \param y y coordinate
void getStringInput(std::string& input, int x, int y);

/// Gets a number input
///
/// \param x x coordinate
/// \param y y coordinate
/// \param CheckCorrectType function which checks if input is an int
/// \return string input
std::string GetNumberInput(int x,int y,bool(*CheckCorrectType)(std::string input));

/// Asks for the name of the hotel file and creates the hotel.
///
/// \return hotel
Hotel* createHotel();

/// Check if input is integer.
///
/// \param input  input to be checked.
/// \return true if input is integer, false otherwise.
bool CheckIfInteger(std::string input);

/// Check if input is integer.
///
/// \param input  input to be checked.
/// \param check  description of the input.
/// \exception throw NotAnInt if input is not an integer.
void checkIfInteger(std::string input, std::string check);

/// Check if input is a positive integer.
///
/// \param input  input to be checked.
/// \param check  description of the input.
/// \exception throw NotAPositiveInt if input is not a positive integer.
void checkIfPositiveInteger(std::string input, std::string check);

/// Check if price or wage is valid.
///
/// \param input  price or wage.
/// \param check  description of the input.
/// \exception throw NotAPositiveFloat if input is not a positive number (int or float).
void checkIfValidPriceOrWage(std::string input, std::string check);

/// Overload for << for vectors.
/// \param o
/// \param v
/// \return o
std::ostream& operator<<(std::ostream &o, std::vector<int> v);

/// Check if NIF is valid.
///
/// \param NIF  NIF.
/// \param name  person's name.
/// \exception throw NIFIsNotValid if NIF is not valid.
void validateNIF(const std::string& NIF,const std:: string& name);

/// Cleans the cin buffer.
/// To use before an std::getline(cin,variable).
void cleanCinBuffer();

/// Asks for a client's name and NIF to perform an action
///
/// \return name and NIF in a vector
std::vector<std::string> askClient();

/// Sorts a particular reservation vector acording to a criteria and an order
///
/// \param reserv_vec vector of reservations
/// \param input criteria to order, can be "Room ID", "Check In" or "Check Out"
/// \param order1 order, can be "Ascending" or "Descending"
void sortReservations(std::vector<Reservation*>& reserv_vec,const std::string& input,const std::string& order1);

/// Asks for a staff member's name, NIF, wage, position, evaluation, shift and password to perform an action
///
/// \return name, NIF, wage, position, evaluation, shift and password in a vector
std::vector<std::string> askStaff();

/// Asks for a reservations info
///
/// \param roomId room ID of the reservation
/// \param checkIn check in date of the reservation
/// \param checkOut check out date of the reservation
/// \param capacity capacity of the reservation
/// \param reservationId reservation ID
void askReservation(unsigned int& roomId,Date& checkIn,Date& checkOut,int& capacity,int& reservationId);

std::vector<std::string> askmodifyReservation();

/// Asks for a room's capacity and price per night
///
/// \return capacity and price per nightin a vector
std::vector<std::string> askRoom();

/// Operator overload for << for a vector.
///
/// \param os
/// \param v
/// \return os
std::ostream& operator<<(std::ostream& os, const std::vector<int> v);

void checkIfValidPlate(const std::string& plate);

int checkIfIsNumber(const std::string& number);
#endif