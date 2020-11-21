#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <string>
#include <vector>


/// Struct which represents a transaction.
///
/// Holds the value and the description of the transaction.
struct Transaction{
    /// Value of the transaction.
    float value;
    /// Description of the transaction.
    std::string description;
};


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

/// Check if NIF is valid.
///
/// \param NIF  NIF.
/// \param name  person's name.
/// \exception throw NIFIsNotValid if NIF is not valid.
void validateNIF(const std::string& NIF,const std:: string& name);

/// Cleans the cin buffer.
/// To use before an std::getline(cin,variable).
void cleanCinBuffer();

#endif