#include "staff.h"

Manager::Manager(const std::string& name, const unsigned int & NIF, const float& wage): Staff(name,NIF,wage){
    evaluation = 0;
};
unsigned int Manager :: getEvaluation() const{
    return this->evaluation;
}
void Manager::setEvaluation(const unsigned int &evaluation){
    //throw exception if the evaluation given is invalid
    this->evaluation = evaluation;
}