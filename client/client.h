#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>

typedef struct Date{
    int year;
    int month;
    int day;
};

struct Reservation{
    int reservationSize; 
    Date checkIn;
    Date checkOut;
    int roomId;
};

class Client{
public:
    Client(const std::string &name, const unsigned int &NIF);

    Date buildDate(const int &year, const int &month, const int &day);
    Reservation buildReservation(const int &reservationSize, const Date & checkIn, const Date & checkOut, const int & roomId);

    std::string getName() const;
    unsigned int getNIF() const;
    std::vector<Reservation*> getHistory() const;

    void setName(const std::string &name);
    void setNIF(const unsigned int &NIF);
    void addToHistory(const Reservation &reservation);

private:
    std::string name;
    unsigned int NIF;
    std::vector<Reservation*> history;
};
#endif
