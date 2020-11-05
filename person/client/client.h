#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
#include "../../hotel/reservation.h"
#include "../person.h"

class Client: public Person{
public:
    Client(const std::string &name, const unsigned int &NIF);

    std::vector<Reservation*> getHistory() const;
    void addToHistory(Reservation &reservation);
    void printClient();

private:
    std::vector<Reservation*> history;
    std::vector<Reservation*> currentReservations;

};
#endif
