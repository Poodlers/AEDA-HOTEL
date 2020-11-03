#include "human.h"
#include <iostream>
#include <iomanip>
#include "../GUI/utils.h"

Human::Human(const std::string& name, const unsigned int & NIF){
    this->name = name;
    this->NIF = NIF;
}

std::string Human::getName() const {
    return this->name;
}

unsigned int Human::getNIF() const {
    return this->NIF;
}

void Human::print() {
    std::cout << std::setw(20) << std::setfill(' ') << this->getName() << std::setw(10) << this->getNIF();
}

void Human::setName(const std::string &name){
    this->name = name;
}

void Human::setNIF(const unsigned int &NIF){
    this->NIF = NIF;
}

void Human::edit() {
    std::string edit;
    std::cout << "Edit the client's information as follows: " << std::endl;
    std::cout << "Note: If you do not wish to edit the current camp, type '.' \n" << std::endl;
    std::cout << "Name: " << std::endl;
    getStringInput(edit, 6, 3);
    if (edit != ".") this->setName(edit);
    gotoxy(0, 5);
    edit = "";
    std::cout << "NIF: " << std::endl;
    edit = GetNumberInput(5,5,CheckIfInteger);
    if(edit != ".") this->setNIF(std::stoi(edit));
}
