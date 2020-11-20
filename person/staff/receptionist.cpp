#include "staff.h"

Receptionist::Receptionist(const std::string& name, const unsigned int & NIF, const float& wage) : Staff(name,NIF,wage){
}

std::string Receptionist::getType() {
    return "Receptionist";
}

