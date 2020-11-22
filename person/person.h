#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "../hotel/reservation.h"

/// Represents a Person.
///
/// Defined by a name and a NIF.
class Person{
public:
    /// Person constructor.
    ///
    /// \param name  person's name.
    /// \param NIF   person's NIF.
    Person(const std::string& name, const unsigned int & NIF);

    /// Returns name.
    ///
    /// \return name.
    std::string getName() const;

    /// Returns NIF.
    ///
    /// \return NIF.
    unsigned int getNIF() const;

    /// Changes name.
    ///
    /// \param name  new name.
    void setName(const std::string& name);

    /// Changes NIF
    ///
    /// \param NIF  new NIF
    void setNIF(const unsigned int& NIF);

    /// Prints person in format:
    ///
    /// name NIF
    virtual void print();

    /// Prints person (for console) in format:
    ///
    /// name NIF
    virtual void printConsole();

    /// Modifies person.
    ///
    /// If any of the parameters are '.' they are not modified.
    /// \see Hotel#modifieStaffMember and Hotel#modifieClient
    /// \param name  new name.
    /// \param NIF  new NIF.
    virtual void personModify(const std::string& name, const std::string& NIF);

protected:
    /// Name.
    std::string name;
    /// NIF.
    unsigned int NIF;
};

#endif