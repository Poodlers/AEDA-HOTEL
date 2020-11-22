#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <map>
#include <string>
#include <vector>
#include "../exceptions/exceptions.h"
#include "../hotel/reservation.h"
#include "../hotel/hotel.h"


char waitForCharInput( int mili_seconds );
void clearscreen();
void printTime(Date date, std::map<int,std::string> &map_month);
void gotoxy(int x, int y);
void SetConsoleDefinitions(DWORD &fdwMode,HANDLE &hin,HANDLE &hout, CONSOLE_CURSOR_INFO &cci);
void fill_month_map(std::map<int,std::string> &map_month);
void getStringInput(std::string& input, int x, int y);
std::string GetNumberInput(int x,int y,bool(*CheckCorrectType)(std::string input));

/// Asks for the name of the hotel file and creates the hotel.
Hotel* createHotel();

/// Check if input is integer.
///
/// \param input  input to be checked.
/// \return true if input is integer, false otherwise.
bool CheckIfInteger(std::string input);

/// Check if input is float.
///
/// \param input  input to be checked.
/// \return true if input is float, false otherwise.
bool CheckIfFloat(std::string input);

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

std::vector<std::string> askClient();
void sortReservations(std::vector<Reservation*>& reserv_vec,const std::string& input,const std::string& order1);
std::vector<std::string> askStaff();
void askReservation(unsigned int& roomId,Date& checkIn,Date& checkOut,int& capacity,int& reservationId);
std::vector<std::string> askRoom();
std::vector<std::string> createRoom();
void BuildProvider(Provider* provider);
std::ostream& operator<<(std::ostream& os, const std::vector<int> v);

#endif