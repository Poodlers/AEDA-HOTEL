#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>

struct Date{
    int year;
    int month;
    int day;
};

class Reservation{
public:
    Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId);
    Reservation(const std::string & reservation);

    Date buildDate(const int &day, const int &month, const int &year);


private:
    static int reservationId;
    int reservationNumber;
    int reservationSize;
    Date checkIn;
    Date checkOut;
    int roomId;
};


#endif
