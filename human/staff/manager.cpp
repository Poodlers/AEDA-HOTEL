#include "staff.h"

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