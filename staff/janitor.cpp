#include "staff.h"

Janitor ::Janitor(const bool & shift,const std::string& name, const unsigned int & NIF, const float& wage) : Staff(name,NIF,wage){
    this->shift = shift;
}

bool Janitor:: getShift() const{
    return this->shift;
}
void Janitor:: setShift(const bool& shift){
    this->shift = shift;
}