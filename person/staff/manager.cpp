#include "staff.h"
#include <iostream>
#include <iomanip>

Manager::Manager(const std::string& name, const unsigned int & NIF, const float& wage, const std::string & password): Staff(name,NIF,wage){
    this->evaluation = 0;
    this->password = password;
};

Manager::Manager():Staff() {
    this->evaluation = 0;
    this->password = "";
}

unsigned int Manager :: getEvaluation() const{
    return this->evaluation;
}
void Manager::setEvaluation(const unsigned int &evaluation){
    //throw exception if the evaluation given is invalid
    this->evaluation = evaluation;
}

std::string Manager::getType() {
    return "Manager";
}

std::string Manager::getPassword() {
    return this->password;
}

void Manager::print() {
    std::cout << std::left << std::setw(13) << this->getType() <<  std::setw(20) << std::setfill(' ') << this->getName() <<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(16) << this->getYearsOfService()
              << std::setw(16) << "" << std::setw(7) << " " << std::setw(12) << this->evaluation;
}


void Manager::managerModify(const std::string& name, const std::string& NIF, const std::string& password){
    if (name != "."){
        this->name = name;
    }
    if(NIF != "."){
        this->NIF =stoi(NIF);
    }
    if(password != "."){
        this->password = password;
    }
}