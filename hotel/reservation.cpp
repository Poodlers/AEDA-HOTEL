#include "reservation.h"
#include "../GUI/utils.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>


Date::Date(const int &day, const int &month, const int &year){
    if (day <= 0 || month <= 0 || year <= 0){
        throw DateIsNotValid("it can't have a negative day, month or year");
    }
    if(day > getDaysInMonth(month)){
        throw DateIsNotValid("the month doesn't contain that number of days");
    }
    this->day = day;
    this->month = month;
    this->year = year;
}
Date::Date(const std::string& date){
    std::stringstream ss;
    int day, month, year;
    char ignore;
    ss<<date;
    ss>>day>>ignore>>month>>ignore>>year;
    if (ss.fail()){
        throw DateIsNotValid("day, month and year have to be integers");
    }
    if (day <= 0 || month <= 0 || year <= 0){
        throw DateIsNotValid("it can't have a negative day, month or year");
    }
    if(day > getDaysInMonth(month)){
        throw DateIsNotValid("the month doesn't contain that number of days");
    }
    this->day = day;
    this->month = month;
    this->year = year;
}

std::ostream& operator<<(std::ostream& o, const Date& date){
    char a[19];
    sprintf(a,"%02d-%02d-%02d         ",date.getDay(),date.getMonth(),date.getYear());
    o << a;
    return o;
}

int Date::operator - (Date date){
    return (this->year * (365 +isInLeapYear()) - date.getYear() * ((365 + isInLeapYear()))) + (this->month * getDaysInMonth(this->month) - date.getMonth() * date.getDaysInMonth(date.getMonth())) + (this->day - date.getDay());
}

Date Date::operator+(const int& d) const {
    Date result = *this;
    result.day += d;
    while (result.day > result.getDaysInMonth(this->month)) {
        result.day -= result.getDaysInMonth(this->month);
        ++result.month;
        if (result.month > 12) {
            result.month = 1;
            ++result.year;
        }
    }
    return result;
}

int Date::getDaysInMonth(const int& month) const {
    switch (month) {
        case 1:case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return 28 + isInLeapYear();
    }
    throw DateIsNotValid("Invalid month");
}

bool Date::isInLeapYear() const {
    return this->year % 400 == 0 || (this->year % 4 == 0 && this->year % 100 != 0);
}
Date::Date(){
}

int Date::getDay() const{
    return this->day;
}
int Date::getMonth() const{
    return this->month;
}
int Date::getYear() const{
    return this->year;
}

bool Date::operator ==(Date date){
    return ((this->day == date.getDay()) && (this->month == date.getMonth())&& (this->year == date.getYear()));

}
bool Date::operator <(Date date){
    if(this->year == date.getYear()){
        if(this->month == date.getMonth()){
            if (this->day < date.getDay()) return true;
            else return false;
        }
        if(this->month < date.getMonth()) return true;
        else return false;
    }
    else if (this->year < date.getYear()) return true;
    else return false;
}

bool Date::operator >(Date date){
    if(this->year == date.getYear()){
        if(this->month == date.getMonth()){
            if (this->day > date.getDay()) return true;
            else return false;
        }
        if(this->month > date.getMonth()) return true;
        else return false;
    }
    else if (this->year > date.getYear()) return true;
    else return false;
}

Reservation::Reservation(const int &reservationSize,Date* checkIn,Date* checkOut, const int & roomId, const int& reservationId) {
    if (*checkOut < *checkIn) { throw ReservationHasInvalidDates(); }

    if (reservationId == -1){
        this->reservationId = this->ID;
        ID++;
    }
    else this->reservationId = reservationId;

    this->reservationSize = reservationSize;
    this->checkIn = *checkIn;
    this->checkOut = *checkOut;
    this->roomId =  roomId;

}

Reservation::Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId){
    try{
        Date checkIn(dayIn,monthIn,yearIn), checkOut(dayOut,monthOut,yearOut);
        if (checkOut < checkIn) { throw ReservationHasInvalidDates(); }
        this->reservationId = this->ID;
        ID++;

        this->reservationSize = reservationSize;

        this->roomId = roomId;

        this->checkIn = checkIn;
        this->checkOut = checkOut;
    }
    catch(...){
        throw;
    }

}


bool Date::operator <=(Date date){
    if(this->year == date.getYear()){
        if(this->month == date.getMonth()){
            if (this->day <= date.getDay()) return true;
            else return false;
        }
        if(this->month < date.getMonth()) return true;
        else return false;
    }
    else if (this->year < date.getYear()) return true;
    else return false;
}

Date Reservation::getCheckIn() const{
    return this->checkIn;
}

Date Reservation::getCheckOut() const{
    return this->checkOut;
}

int Reservation::getReservationId() const {
    return this->reservationId;
}

int Reservation::getReservationSize() const {
    return this->reservationSize;
}

int Reservation::getRoomId() const {
    return this->roomId;
}

void Reservation::print() {
    std::cout << std::left <<  std::setw(20) << std::setfill(' ') << this->getReservationId()
              << std::setw(25) << this->getReservationSize()<< this->getCheckIn()
               << this->getCheckOut()
              << std::setw(8) << this->getRoomId();
}

void Reservation::setReservationId(const int & reservationId){
    this->reservationId =reservationId;
}
void Reservation::setReservationSize(const int & reservationSize){
    this->reservationSize =reservationSize;
}
void Reservation::setCheckIn(const Date& checkIn){
    this->checkIn =checkIn;
}
void Reservation::setCheckOut(const Date& checkOut){
    this->checkOut =checkOut;
}


void Reservation::setID(const int& ID) const{
    this->ID = ID;
}

void Reservation::setRoomId(const int& roomId){
    this->roomId = roomId;
}

int Reservation::ID = 0;