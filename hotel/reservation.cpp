#include "reservation.h"
#include <sstream>


Reservation::Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId){
    Date dateIn, dateOut;

    this->reservationSize = reservationSize;
    this->roomId = roomId;
    this->checkIn = buildDate(dayIn,monthIn,yearIn);
    this->checkOut = buildDate(dayOut,monthOut,yearOut);

}
Reservation :: Reservation(const std::string & reservation){
    //receives reservationSize,dayIn-monthIn-yearIn,dayOut-monthOut-yearOut,roomId
    std::stringstream ss;
    std::string dates;
    Date dateIn, dateOut;

    char ignore;

    ss>>this->reservationSize>>dates>>this->roomId;
    ss<< dates;

    ss >> ignore >> dateIn.day >> ignore >> dateIn.month >>ignore >> dateIn.year >> ignore >> dateOut.day >> ignore >> dateOut.month >>ignore >> dateOut.year;
    this->checkIn = dateIn;
    this->checkOut = dateOut;
}

Date Reservation::buildDate(const int& day, const int& month, const int& year){
    Date date;

    date.day = day;
    date.month = month;
    date.year = year;
    return  date;

}