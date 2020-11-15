#include "reservation.h"
#include "../GUI/utils.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

Date::Date(const int &day, const int &month, const int &year){
    this->day = day;
    this->month = month;
    this->year = year;
}
Date::Date(const std::string& date){
    std::stringstream ss;
    char ignore;
    ss<<date;
    ss>>this->day>>ignore>>this->month>>ignore>>this->year;

}

std::ostream& operator<<(std::ostream& o, const Date& date){
    o << std::left << std::setw(2) << std::setfill('0') << date.day << "/"  << std::setw(2) << date.month << "/" << std::setfill(' ') << std::setw(9) << date.year;
    return o;
}

int Date::operator - (const Date& date){
    if (this-> year == date.getYear() && this->month == date.getMonth())
        return this->day - date.getDay();
    else if (this->year == date.getYear()){
        return (this->month - date.getMonth()) * 30 - this->day + date.day ;
    }
    else
        return 365 * (this->year - date.getYear()) - (this->month - date.getMonth()) * 30 - this->day + date.day;
}
Date Date::operator+(int d) const {
    Date result = *this;
    result.day += d;
    while (result.day > result.getDaysInMonth()) {
        result.day -= result.getDaysInMonth();
        ++result.month;
        if (result.month > 12) {
            result.month = 1;
            ++result.year;
        }
    }
    return result;

}

int Date::getDaysInMonth() const {
    switch (this->month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return 28 + isInLeapYear();
    }
    return 0;
}

Date operator+(int daysToAdd, const Date& date) {
    return date + daysToAdd;
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

bool Date::operator ==(const Date& date){
    return ((this->day == date.getDay()) && (this->month == date.getMonth())&& (this->year == date.getYear()));

}
bool Date::operator <(const Date& date){
    if (this->year < date.getYear()){
        return true;
    }
    else if ((this->year == date.getYear()) && (this->month < date.getMonth())){
        return true;
    }
    else if ((this->year == date.getYear()) && (this->month == date.getMonth()) && (this->day < date.getDay())){
        return true;
    }
    return false;
}
bool Date::operator >(const Date& date){
    if (this->year > date.getYear()){
        return true;
    }
    else if ((this->year == date.getYear()) && (this->month > date.getMonth())){
        return true;
    }
    else if ((this->year == date.getYear()) && (this->month == date.getMonth()) && (this->day > date.getDay())){
        return true;
    }
    return false;
}

Reservation::Reservation(const int &reservationSize,const int& dayIn, const int&monthIn, const int &yearIn,const int& dayOut, const int&monthOut, const int &yearOut, const int & roomId){
    Date checkIn(dayIn,monthIn,yearIn), checkOut(dayOut,monthOut,yearOut);
    reservationId = rand();
    this->reservationId = reservationId;
    this->reservationSize = reservationSize;
    this->roomId = roomId;
    this->checkIn =checkIn;
    this->checkOut = checkOut;

}
Reservation :: Reservation(const std::string & reservation){
    //receives reservationSize,dayIn-monthIn-yearIn,dayOut-monthOut-yearOut,roomId,reservationId
    std::stringstream ss(reservation);
    std::string dates;
    int day, month, year, reservationId;
    char ignore;
    ss>>this->reservationSize>> ignore >>  day >> ignore >> month   >> ignore >>  year;
    Date dateIn(day,month,year);
    ss>> ignore >>  day  >> ignore >>  month >> ignore >> year >>ignore >>  this->roomId >> this->reservationId;
    Date dateOut(day,month,year);
    this->checkIn = dateIn;
    this->checkOut = dateOut;
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
void Reservation::setRoomId(const int& roomId){
    this->roomId =roomId;
}

/*
void Reservation::edit() {
    std::string edit;
    std::cout << "Edit the Reservation's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    std::cout << "Reservation Number: " << std::endl;
    edit = GetNumberInput(22,3,CheckIfInteger);
    if (edit != ".") this->setReservationNumber(std::stoi(edit));
    gotoxy(0,5);
    std::cout << "Check In Date (day/month/year): " << std::endl;
    getStringInput(edit,30,5);
    if (edit != ".") this->setCheckIn(Date(edit));
    gotoxy(0,7);
    std::cout << "Check Out Date (day/month/year): " << std::endl;
    getStringInput(edit,30,5);
    if (edit != ".") this->setCheckOut(Date(edit));
    gotoxy(0,9);
    std::cout << "Room Id: " << std::endl;
    edit = GetNumberInput(10,9,CheckIfInteger);
    if (edit != ".") this->setRoomId(std::stoi(edit));
}*/