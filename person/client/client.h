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

    std::vector<Reservation*>& getHistory();
    std::vector<Reservation*> getFutureReservations() const;
    std::vector<Reservation*> getCurrentReservations() const;

    void addToHistory(Reservation *reservation);
    void addNewReservation(Reservation *reservation);
    void addCurrentReservation(Reservation *reservation);
    void removeReservation(Reservation* reservation);
    void checkOut( Date date);
    void checkIn( Date date);

    std::vector<int> checkOut (Date* date);
    std::vector<int> checkIn (Date* date);
    void archiveExpiredReservations(Date date);
    void printConsole();
    bool operator==(Client* client);


private:
    std::vector<Reservation*> history;
    std::vector<Reservation*> futureReservations;
    std::vector<Reservation*> currentReservations;
};
#endif
