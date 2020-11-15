#include "staff.h"
#include <iostream>
#include "../../GUI/utils.h"
#include <iomanip>

Manager::Manager(const std::string& name, const unsigned int & NIF, const float& wage, const std::string & password): Staff(name,NIF,wage){
    this->evaluation = 0;
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
    std::cout << std::left << std::setw(13) << this->getType() <<  std::setw(20) << std::setfill(' ') << this->getName() <<
              std::setw(10) << this->getNIF() << std::setw(7) << this->getWage() << std::setw(16) << this->getYearsOfService()
              << std::setw(16) << "" << std::setw(7) << " " << std::setw(12) << this->evaluation;
}
/*
void Manager::edit() {
    std::string edit;
    std::cout << "Edit the Manager's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    std::cout << "Name: " << std::endl;
    getStringInput(edit,6,3);
    if (edit != ".") this->setName(edit);
    gotoxy(0,5);
    std::cout << "NIF: " << std::endl;
    edit = GetNumberInput(5,5,CheckIfInteger);
    if (edit != ".") this->setNIF(std::stoi(edit));
    gotoxy(0,7);
    std::cout << "Wage: " << std::endl;
    edit = GetNumberInput(12,7,CheckIfFloat);
    if (edit != ".") this->setWage(std::stof(edit));
    gotoxy(0,9);
    std::cout << "Years of Service: " << std::endl;
    edit = GetNumberInput(20,9,CheckIfInteger);
    if (edit != ".") this->setYearsOfService(std::stoi(edit));
    gotoxy(0,11);
    std::cout << "Evaluation: " << std::endl;
    edit = GetNumberInput(20,9,CheckIfInteger);
    if (edit != ".") this->setEvaluation(std::stoi(edit));

}*/