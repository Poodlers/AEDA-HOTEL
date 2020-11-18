#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
#include "../../hotel/reservation.h"
#include "../person.h"
#include "../../exceptions/exceptions.h"

class Client: public Person{
public:
    ///Client constructor
    ///
    /// \param name - client's name
    /// \param NIF - client's NIF
    Client(const std::string &name, const unsigned int &NIF);

    /// Return the history vector
    ///
    /// \return history
    std::vector<Reservation*>& getHistory();

    /// Return the future reservations vector
    ///
    /// \return futureReservations
    std::vector<Reservation*> getFutureReservations() const;

    /// Return the current reservations vector
    ///
    /// \return currentReservations
    std::vector<Reservation*> getCurrentReservations() const;

    /// Adds a reservation to history vector
    ///
    /// \param reservation - reservation to add
    void addToHistory(Reservation *reservation);

    ///Adds reservation to new reservations
    ///
    /// \param reservation - reservation to add
    void addNewReservation(Reservation *reservation);

    ///Adds reservation to current reservations
    ///
    /// \param reservation - reservation to add
    void addCurrentReservation(Reservation *reservation);

    ///Removes reservation from history
    ///
    /// \param reservation - reservation to remove
    void removeReservation(Reservation* reservation);


    std::vector<int> checkOut (Date* date);
    std::vector<int> checkIn (Date* date);
    void archiveExpiredReservations(Date* date);
    void printConsole();
    bool operator==(Client* client);


private:
    std::vector<Reservation*> history;
    std::vector<Reservation*> futureReservations;
    std::vector<Reservation*> currentReservations;
};
#endif
