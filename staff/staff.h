#ifndef STAFF_H
#define STAFF_H
#include <string>
#include <vector>

class StaffMemberAlreadyExists{
private:
    std::string name;
    unsigned int NIF;
public:
    StaffMemberAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    std::string getName() const{ return this->name; }
    unsigned int getNIF() const{ return this->NIF; }
};

class StaffWithThisNIFAlreadyExists{
private:
    std::string name;
    unsigned int NIF;
public:
    StaffWithThisNIFAlreadyExists(const std::string &name, const unsigned int& NIF){
        this->name = name;
        this->NIF = NIF;
    }
    std::string getName() const{ return this->name; }
    unsigned int getNIF() const{ return this->NIF; }
};

class FloorDosNotExist{
private:
    unsigned int floor;
public:
    FloorDosNotExist(const unsigned int &floor){ this->floor = floor; }
    unsigned int getFloor() const{ return this->floor; }
};

class InvalidEvaluation{
private:
    unsigned int evaluation;
public:
    InvalidEvaluation(const unsigned int & evaluation) { this->evaluation = evaluation; }
    unsigned int getEvaluation() const{ return this->evaluation; }
};

class Staff {
public:
    std::string getName() const;
    unsigned int getNIF() const;
    float getWage() const;
    int getyearsOfService() const;
    void setName(const std::string name);
    void setNIF(const unsigned int NIF);
    void setwage(const float wage);
    void setyearsOfService(const int yearsOfService);
    Staff(const std::string& name, const unsigned int & NIF, const float& wage);
protected:
    std::string name;
    unsigned int NIF;
    float wage;
    int yearsOfService;
};


class Receptionist : public  Staff{
public:
    Receptionist();
};

class Responsible : public Receptionist{
public:
    Responsible(const std::string& name, const unsigned int & NIF, const float& wage);
    void assignFloor(const unsigned int & floor);
    int getNumberOfFloorsBringMonitored() const;
    std::vector<int> getFloorsAssigned() const;

private:
    int numberOfFloorsBeingMonitored;
    std::vector<int> floorsAssigned;
};

class Janitor : public Staff{
public:
    Janitor(const bool & shift,const std::string& name, const unsigned int & NIF, const float& wage);
    bool getShift() const;
    void setShift(const bool& shift);

private:
    bool shift; //true for day, false for night
};

class Manager : public Staff{
public:
    Manager(const std::string& name, const unsigned int & NIF, const float& wage);
    unsigned int getEvaluation() const;
    void setEvaluation(const unsigned int &evaluation);
private:
    unsigned int evaluation; //0 if manager has not been evaluated, 1 to 5 they have been evaluated
};
#endif