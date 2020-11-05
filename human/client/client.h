#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
#include "../../hotel/reservation.h"
#include "../human.h"

class Client: public Human{
public:
    Client(const std::string &name, const unsigned int &NIF);

    std::vector<Reservation*>& getHistory() const;
    void addToHistory(Reservation &reservation);

private:
    std::vector<Reservation*> history;
    std::vector<Reservation*> currentReservations;
};
#endif
