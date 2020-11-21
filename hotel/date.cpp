#include "date.h"
#include <string>
#include <sstream>


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
    sprintf(a,"%02d-%02d-%02d      ",date.getDay(),date.getMonth(),date.getYear());
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