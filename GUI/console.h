#ifndef AEDA_HOTEL_PROJETO_CONSOLE_H
#define AEDA_HOTEL_PROJETO_CONSOLE_H
#include "../hotel/hotel.h"

/// Accounting menu for console application.
///
/// Displays transactions, profit, costs and money earned.
/// \param hotel
/// \exception throws AccessRestricted if someone not logged in attempts to access this menu.
void accounting(Hotel* hotel);

/// Providers menu for console application.
///
/// Displays providers and their products, allows the user to buy products or automatically buy a random number of
/// the cheapest ones of the different categories.
/// \param hotel
/// \exception throws AccessRestricted if someone not logged in attempts to access this menu.
void providers(Hotel* hotel);

/// Reservations menu for console application.
///
/// Allows the user to create reservations or search for reservations by date, ID, Room or to see them all.
/// \param hotel
void reservation(Hotel * hotel);

/// Rooms menu for console application.
///
/// Allows the user to modify, add, sort and search for rooms as well as visualize all rooms.
/// Allows the manager to enable discounts for a certain type of room.
void rooms(Hotel * hotel);

/// CheckIn for console application.
///
/// To check In.
/// \param hotel
void checkIn(Hotel* hotel);

/// CheckOut for console application.
///
/// To check Out.
/// \param hotel
void checkOut(Hotel* hotel);

/// Clients menu for console application.
///
/// \see checkIn and checkOut
/// Displays clients and allows user to add, remove, modify, sort, search, check in, check out and advance time.
/// \param hotel
void clients(Hotel *hotel);

/// Staff menu for console application.
///
/// Displays staff members and allows the manager to add, modify, remove, sort and search staff members, to assign floors to responsibles
/// and to advance time.
/// \param hotel
/// \exception throws AccessRestricted if someone not logged in attempts to access this menu.
void staff(Hotel *hotel);

/// System for the hotel.
///
/// \see clients, staff, accounting, providers, rooms, reservation, Hotel#logIn, Hotel#logOut and Hotel#incrementDate
/// \param hotel
void system(Hotel* hotel);

/// Vehicle menu for console application.
///
/// Displays vehicles and allows to add, modify, remove, sort and search vehicles.
/// \param hotel
void vehicle(Hotel* hotel);

/// Products bought menu for console application.
///
/// Displays bought products and allows to modify, remove, search and get the best buys.
/// \param hotel
void buyProduct(Hotel* hotel);

/// Regular clients menu for console application
///
/// Displays regular clients and allows to sort and search regular clients.
/// \param hotel
void regularClients(Hotel* hotel);

#endif
