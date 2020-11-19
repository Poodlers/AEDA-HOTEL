#include "staff.h"
#include <iostream>
#include <iomanip>

Manager::Manager(const std::string& name, const unsigned int & NIF, const float& wage, const std::string & password, const unsigned int & evaluation): Staff(name,NIF,wage){
    this->evaluation = evaluation;
    this->password = password;
};


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
    std::cout << std::left << std::setw(13) << this->getType() <<  std::setw(22) << std::setfill(' ') << this->getName() <<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(19) << this->getYearsOfService()
              << std::setw(16) << "" << std::setw(7) << " " << std::setw(12) << this->evaluation;
}


void Manager::managerModify(const std::string& name, const std::string& NIF, const std::string& wage,const std::string & password, const std::string& evaluation){
    if (name != "."){
        this->name = name;
    }
    if(NIF != "."){
        this->NIF =stoi(NIF);
    }
    if(password != "."){
        this->password = password;
    }
    if(wage != "."){
        this->wage = stof(wage);
    }
    if(evaluation != "."){
        this->evaluation = stoi(evaluation);
    }
}