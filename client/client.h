#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
#include "../hotel/reservation.h"

class Client{
public:
    Client(const std::string &name, const unsigned int &NIF);

    std::string getName() const;
    unsigned int getNIF() const;
    std::vector<Reservation*> getHistory() const;

    void setName(const std::string &name);
    void setNIF(const unsigned int &NIF);
    void addToHistory(Reservation &reservation);

private:
    std::string name;
    unsigned int NIF;
    std::vector<Reservation*> history;
    std::vector<Reservation*> currentReservations;
};
#endif
