#ifndef PERSON_H
#define PERSON_H
#include <string>
#include "../hotel/reservation.h"

class Person{
public:
    Person(const std::string& name, const unsigned int & NIF);
    std::string getName() const;
    unsigned int getNIF() const;
    void setName(const std::string& name);
    void setNIF(const unsigned int & NIF);
    virtual void print();
    virtual void edit();
private:
    std::string name;
    unsigned int NIF;
};

#endif