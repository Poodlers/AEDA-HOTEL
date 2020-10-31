#ifndef HUMAN_H
#define HUMAN_H
#include <string>
#include "../hotel/reservation.h"

class Human{
public:
    Human(const std::string& name, const unsigned int & NIF);
    std::string getName() const;
    unsigned int getNIF() const;
    void setName(const std::string& name);
    void setNIF(const unsigned int & NIF);

private:
    std::string name;
    unsigned int NIF;
};

#endif