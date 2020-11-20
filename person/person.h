#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "../hotel/reservation.h"

///Represents a person
///
///Has a name and a NIF
class Person{
public:
    ///Person constructor
    ///
    /// \param name  person's name
    /// \param NIF   person's NIF
    Person(const std::string& name, const unsigned int & NIF);

    /// Returns the name
    ///
    /// \return name
    std::string getName() const;

    /// Returns the NIF
    ///
    /// \return NIF
    unsigned int getNIF() const;

    /// Changes the name
    ///
    /// \param name - new name
    void setName(const std::string& name);

    /// Changes the NIF
    ///
    /// \param NIF  new NIF
    void setNIF(const unsigned int & NIF);
    /// Prints person
    virtual void print();

    ///Modifies person
    ///
    /// if any of the parameters are '.' they are not modified
    /// \see Hotel#modifieStaffMember and Hotel#modifieClient
    /// \param name  new name
    /// \param NIF  new NIF
    virtual void personModify(const std::string& name, const std::string& NIF);

protected:
    ///name
    std::string name;
    ///NIF
    unsigned int NIF;
};

#endif