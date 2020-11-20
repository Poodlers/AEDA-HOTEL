#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <map>
#include <string>
#include <vector>
#include "../exceptions/exceptions.h"
#include "../hotel/reservation.h"
#include "../hotel/date.h"


/// Struct which represents a transaction
///
/// Holds the value and the description of the transaction
typedef struct Transaction{
    ///value of the transaction
    float value;
    ///description of the transaction
    std::string description;
};


/// Check if input is integer
///
/// \param input  input to be checked
/// \param check  description of the input
/// \exception throw <NotAnInt> if input is not an int.
void checkIfInteger(std::string input, std::string check);

/// Check if input is a positive integer
///
/// \param input  input to be checked
/// \param check  description of the input
/// \exception throw <NotAPositiveInt> if input is not a positive int.
void checkIfPositiveInteger(std::string input, std::string check);

/// Check if price or wage is valid
///
/// \param input  price or wage
/// \param check  description of the input
/// \exception throw <checkIfValidPriceOrWage> if input is not a positive number (int or float)
void checkIfValidPriceOrWage(std::string input, std::string check);

/// Check if NIF is valid
///
/// \param NIF  NIF
/// \param name  person's name
/// \exception throw <NIFIsNotValid> if NIF is not valid
void validateNIF(const std::string& NIF,const std:: string& name);

///Cleans the cin buffer
/// To use before an std::getline(cin,variable)
void cleanCinBuffer();

#endif