#ifndef STAFF_H
#define STAFF_H
#include <string>
#include <vector>

class Staff {
public:
    Staff(const std::string& name, const unsigned int & NIF, const float& wage);

    std::string getName() const;
    unsigned int getNIF() const;
    float getWage() const;
    int getYearsOfService() const;

    void setName(const std::string name);
    void setNIF(const unsigned int NIF);
    void setWage(const float wage);
    void setYearsOfService(const int yearsOfService);

    virtual void print() const;

protected:
    std::string name;
    unsigned int NIF;
    float wage;
    int yearsOfService; //could be unsigned int!!!
    static unsigned int staffNumber; //counts the number of staff members
};


class Receptionist : public  Staff{
public:
    Receptionist(const std::string& name, const unsigned int & NIF, const float& wage);
    void print(){};
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
    void print(){};

private:
    bool shift; //true for day, false for night
};

class Manager : public Staff{
public:
    Manager(const std::string& name, const unsigned int & NIF, const float& wage, const std::string & password);
    unsigned int getEvaluation() const;
    void setEvaluation(const unsigned int &evaluation);
    void print(){};

private:
    unsigned int evaluation; //0 if manager has not been evaluated, 1 to 5 they have been evaluated
    std::string password;
};

#endif