#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
#include "../../hotel/reservation.h"
#include "../person.h"
#include "../../exceptions/exceptions.h"

/// \class Client
/// represents a client
///
/// Is made up of a NIF, a name, a vector with the history of the client's reservations, a vector with the client's future reservations and a vector
/// for current reservations i.e. the client is at the hotel at the moment
class Client: public Person{
public:
    ///Client constructor
    ///
    /// \param name  client's name
    /// \param NIF  client's NIF
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
    /// \param reservation  reservation to add
    void addToHistory(Reservation *reservation);

    ///Adds reservation to new reservations
    ///
    /// \param reservation  reservation to add
    void addNewReservation(Reservation *reservation);

    ///Adds reservation to current reservations
    ///
    /// \param reservation  reservation to add
    void addCurrentReservation(Reservation *reservation);


    /// Check Out
    ///
    /// Goes through the vector current reservations and if the date is bigger or equal to the check out date proceeds
    /// to remove it from the current reservations vector and put it in the client's history.
    /// \param date  current date
    /// \return positions of the reservations that were checked out
    /// \exception throws NoReservationsToCheckOut if there are no reservations from the client to check out currently
    std::vector<int> checkOut (Date* date);

    /// Check In
    ///
    /// Goes through the vector future reservations and if the date is bigger or equal to the check in date proceeds
    /// to remove it from the future reservations vector and put it in the client's current reservations vector.
    /// \param date  current date
    /// \return positions of the reservations that were checked in
    /// \exception throws NoReservationsToCheckIn if there are no reservations from client to check in
    std::vector<int> checkIn (Date* date);

    /// Archives expired reservations
    ///
    /// If a reservation in future reservations expires on date (i.e. check out date <= current date) it is removed from
    /// the future reservations vector and appended to the client's history
    /// \param date  current sate
    void archiveExpiredReservations(Date* date);

    /// Prints clients in the format:
    ///
    ///NIF: nif Name: name
    ///Client History: (if empty does not print)
    ///...
    ///Current Reservations: (if empty does not print)
    ///...
    ///Future Reservations: (if empty does not print)
    ///...
    void printConsole();

    ///overload for ==
    ///
    /// \param client
    /// \return this-> == client
    bool operator==(Client* client);

private:
    /// Vector with past reservations
    std::vector<Reservation*> history;
    /// Vector with future reservations
    std::vector<Reservation*> futureReservations;
    /// Vector with current reservation i.e. the person is currently staying at the hotel
    std::vector<Reservation*> currentReservations;
};
#endif
