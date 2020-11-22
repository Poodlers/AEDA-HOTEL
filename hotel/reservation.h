#ifndef RESERVATION_H
#define RESERVATION_H
#include "date.h"

/// Represents a reservation.
///
/// Defined by a reservation ID, a reservation size, do room ID of the claimed room, the check in date and the check out date.
class Reservation{
public:
    ///Reservation constructor.
    ///
    /// \param reservationSize  size of the reservation.
    /// \param CheckIn  check in date.
    /// \param CheckOut  check out date.
    /// \param roomId  room ID.
    /// \param reservationId  reservation ID -> if -1 generates a new distinct ID using the static ID variable
    /// \exception throws ReservationHasInvalidDates if check out date < check in date.
    Reservation(const int &reservationSize,Date* CheckIn,Date* CheckOut, const int & roomId, const int& reservationId);

    /// Returns reservation ID.
    ///
    /// \return reservationId.
    int getReservationId() const;

    /// Reservation constructor.
    ///
    /// \param reservationSize  size of the reservation.
    /// \param dayIn  day of the check in.
    /// \param monthIn  month of the check in.
    /// \param yearIn  year of the check in.
    /// \param dayOut  day of the check out.
    /// \param monthOut  month of the check out.
    /// \param yearOut  year of the check out.
    /// \param roomId  ID of the claimed room.
    /// \exception throws ReservationHasInvalidDates if check out date < check in date.
    /// \exception throws DateIsNotValid if check in date or check out date are invalid.
    Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId);


    /// Return reservation size.
    ///
    /// \return reservation size.
    int getReservationSize() const;

    /// Returns check in date.
    ///
    /// \return check in date.
    Date getCheckIn() const;

    /// Returns check out date.
    ///
    /// \return check out date.
    Date getCheckOut() const;

    /// Returns room ID.
    ///
    /// \return room ID.
    int getRoomId() const;

    /// Changes check in date.
    ///
    /// \param checkIn  new check in date.
    void setCheckIn(Date* checkIn);

    /// Changes check ou date.
    ///
    /// \param checkOut  new check out date.
    void setCheckOut(Date* checkOut);

    /// Changes the static ID.
    ///
    /// Used after initializing the hotel to make sure we don't repeat reservation IDs.
    /// \param ID  new ID
    void setID(const int& ID) const;

    /// Prints the reservation in format:
    ///
    /// reservationId reservationSize checkIn checkOut roomId
    void print();

    /// Changes if reservation is current or not.
    ///
    /// \param isCurrent true or false depending on if a client is checkin in or checking out.
    void setIsCurrent(bool isCurrent);

    /// Returns is current
    ///
    /// \return isCurrent
    bool getIsCurrent() const;

    /// Changes room ID
    ///
    /// \param roomId new room ID
    void setRoomId(int roomId);

    /// Changes reservation size
    ///
    /// \param reservationSize new reservation Size
    void setReservationSize(int reservationSize);

private:
    /// Reservation ID.
    int reservationId;
    /// Reservation size.
    int reservationSize;
    /// Check in date.
    Date checkIn ;
    /// Check out date.
    Date checkOut;
    /// Room ID.
    int roomId;
    /// True if reservation is current i.e. is happening right now, false otherwise.
    bool isCurrent = false;
    /// Variable to avoid repeating reservation IDs.
    static int ID;
};


#endif
