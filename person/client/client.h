#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
#include "../../hotel/reservation.h"
#include "../person.h"
#include "../../exceptions/exceptions.h"
#include "unordered_set"



/// \class Client
/// Class which represents a Client.
///
/// Is defined by a NIF and a name (inherited from class person), a vector with the history of the client's reservations, a vector with the client's future reservations and a vector
/// for current reservations i.e. the client is at the hotel at the moment.
class Client: public Person{
public:
    /// Client constructor.
    ///
    /// \param name  client's name.
    /// \param NIF  client's NIF.
    Client(const std::string &name, const unsigned int &NIF);

    /// Return history vector.
    ///
    /// \return history.
    std::vector<Reservation*>& getHistory();

    /// Return future reservations' vector.
    ///
    /// \return futureReservations.
    std::vector<Reservation*> getFutureReservations() const;

    /// Return the current reservations' vector.
    ///
    /// \return currentReservations.
    std::vector<Reservation*> getCurrentReservations() const;

    /// Adds reservation to history vector.
    ///
    /// \param reservation  reservation to add.
    void addToHistory(Reservation *reservation);

    /// Adds reservation to new reservations.
    ///
    /// \param reservation  reservation to add.
    void addNewReservation(Reservation *reservation);

    /// Adds reservation to current reservations.
    ///
    /// \param reservation  reservation to add.
    void addCurrentReservation(Reservation *reservation);
    /// deletes reservation.
    ///
    /// \param reservation reservation to delete.
    void deleteReservation(Reservation* reservation);
    /// Check Out.
    ///
    /// Goes through the vector 'currentReservations' and if the date is bigger or equal to the check out date for a specific reservation, proceeds
    /// to remove it from the vector 'currentReservations' and put it in the client's history.
    /// \param date  current date.
    /// \return positions of the reservations that were checked out.
    /// \exception throws NoReservationsToCheckOut if there are no reservations from the client to check out currently.
    std::vector<int> checkOut (Date* date);

    /// Check In.
    ///
    /// Goes through the vector 'futureReservations' and if the date is bigger or equal to the check in date for a specific reservation, proceeds
    /// to remove it from the vector 'futureReservations' vector and put it in the vector 'currentReservations'.
    /// \param date  current date.
    /// \return reservation IDs of the reservations that were checked in.
    /// \exception throws NoReservationsToCheckIn if there are no reservations from client to check in.
    std::vector<int> checkIn (Date* date);

    /// Archives expired reservations.
    ///
    /// If a reservation in 'futureReservations' expires on date (i.e. check out date <= current date) it is removed from
    /// the 'futureReservations' and appended to the client's history.
    /// \param date  current sate.
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

    /// Overload for ==.
    ///
    /// \param client
    /// \return this-> == client.
    bool operator==(Client* client);

    /// Return all reservation.
    ///
    /// \return all reservations.
    std::vector<Reservation*>& getAllReservations();

    /// Changes history
    ///
    /// \param history  new history
    void setHistory(const std::vector<Reservation*> &history);

    /// Changes future reservations
    ///
    /// \param futureReservations  new future reservations
    void setFutureReservations(const std::vector<Reservation*> &futureReservations);

    /// Changes current reservations
    ///
    /// \param currentReservations  new current reservations
    void setCurrentReservations(const std::vector<Reservation*> &currentReservations);

    /// Changes all reservations
    ///
    /// \param allReservations  all new reservations
    void setAllReservations(const std::vector<Reservation*> &allReservations);

private:
    /// Vector with past reservations
    std::vector<Reservation*> history;
    /// Vector with future reservations
    std::vector<Reservation*> futureReservations;
    /// Vector with current reservation i.e. the person is currently staying at the hotel
    std::vector<Reservation*> currentReservations;
    /// Vector with all reservations
    std::vector<Reservation*> allReservations;
};


/// Hash function fot hash table.
struct clientHash
{
    ///
    /// \param c Client.
    /// \return First letter of the client's name.
    int operator() (const Client& c) const
    {
        return c.getName()[0];
    }
    ///
    /// \param c1 Client 1.
    /// \param c2 Client 2.
    /// \return c1.getNIF() == c2.getNIF().
    bool operator() (const Client& c1, const Client& c2) const
    {
       return c1.getNIF() == c2.getNIF();
    }
};

typedef std::unordered_set<Client, clientHash, clientHash> ClientTable;


#endif
