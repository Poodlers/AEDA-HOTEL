#include "person.h"
#include <iostream>
#include <iomanip>
#include "../exceptions/exceptions.h"

Person::Person(const std::string& name, const unsigned int & NIF){
    this->name = name;
    this->NIF = NIF;
}

std::string Person::getName() const {
    return this->name;
}

unsigned int Person::getNIF() const {
    return this->NIF;
}

void Person::print() {
    std::cout << std::setw(20) << std::setfill(' ') << this->getName() << std::setw(10) << this->getNIF();
}

void Person::printConsole() {
    std::cout << std::setw(20) << std::setfill(' ') << this->getName() << std::setw(10) << this->getNIF();
}

void Person::setName(const std::string &name){
    this->name = name;
}

void Person::setNIF(const unsigned int &NIF) {
    this->NIF = NIF;
}

void Person::personModify(const std::string& name, const std::string& NIF){
    if (name != "."){
        this->name = name;
    }
    if(NIF != "."){
        this->NIF =stoi(NIF);
    }
}

