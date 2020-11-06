#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
#include "../../hotel/reservation.h"
#include "../person.h"
#include "../../exceptions/exceptions.h"

class Client: public Person{
public:
    Client(const std::string &name, const unsigned int &NIF);

    std::vector<Reservation*> getHistory() const;
    void addToHistory(Reservation *reservation);
    std::vector<Reservation*> getFutureReservations() const;
    void addNewReservation(Reservation *reservation);
    bool checkOut( Date *date);
    bool checkIn( Date *date);
    void printClient();
    bool operator==(Client* client);

private:
    std::vector<Reservation*> history;
    std::vector<Reservation*> futureReservations;
    std::vector<Reservation*> currentReservations;
};
#endif
