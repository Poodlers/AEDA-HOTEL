#ifndef STAFF_H
#define STAFF_H
#include <string>
#include <vector>
#include "../person.h"

class Staff: public Person {
public:
    ///
    /// \param name - employee's name
    /// \param NIF - employee's NIF
    /// \param wage - employee's wage
    Staff(const std::string& name, const unsigned int & NIF, const float& wage);
    ///
    /// \return employee's wage
    float getWage() const;
    ///
    /// \return employee's years of work
    int getYearsOfService() const;
    ///
    /// \return "staff"
    virtual std::string getType();
    ///
    /// \param wage - new wage to set for staff member
    void setWage(const float wage);
    ///
    /// \param yearsOfService - years of service to set for staff member
    void setYearsOfService(const int yearsOfService);
    ///
    virtual void print() override;

protected:
    /// employee's wage
    float wage;
    /// employee's years of work
    unsigned int yearsOfService;
};


class Receptionist : public  Staff{
public:
    ///
    /// \param name - receptionist's name
    /// \param NIF - receptionist's NIF
    /// \param wage - receptionist's wage
    Receptionist(const std::string& name, const unsigned int & NIF, const float& wage);
    ///
    /// \return "Receptionist"
    std::string getType() override;
};

class Responsible : public Receptionist{
public:
    ///
    /// \param name - responsible's name
    /// \param NIF - responsible's NIF
    /// \param wage - responsible's wage
    Responsible(const std::string& name, const unsigned int & NIF, const float& wage);
    ///
    /// \param floor - floor to be assigned to the floor monitor
    void assignFloor(const unsigned int & floor);
    /// clears floor monitor's assigned floors
    void clearAssignedFloors();
    ///
    /// \return number of floors being monitored by the floor monitor
    int getNumberOfFloorsBringMonitored() const;
    ///
    /// \return vector of floors assigned to the floor monitor
    std::vector<int> getFloorsAssigned() const;
    ///
    /// \return "Responsible"
    std::string getType() override;
    ///
    void print() override;

private:
    /// number of floors being monitored by the floor monitor
    int numberOfFloorsBeingMonitored;
    /// vector of floors assigned to the floor monitor
    std::vector<int> floorsAssigned;
};

class Janitor : public Staff{
public:
    ///
    /// \param shift - janitor's shift
    /// \param name - janitor's name
    /// \param NIF - janitor's NIF
    /// \param wage - janitor's wage
    Janitor(const bool & shift,const std::string& name, const unsigned int & NIF, const float& wage);
    ///
    /// \return true for day shift, false for night shift
    bool getShift() const;
    ///
    /// \param shift - janitor's new shift
    void setShift(const bool& shift);
    ///
    /// \return "Janitor"
    std::string getType() override;
    ///
    void print() override;
    ///
    /// \param name - janitor's name
    /// \param NIF - janitor's NIF as string
    /// \param shift - janitor's shift
    void janitorModify(const std::string& name, const std::string& NIF, const std::string& shift);

private:
    /// true for day, false for night
    bool shift;
};

class Manager : public Staff{
public:
    ///
    /// \param name - manager's name
    /// \param NIF - manager's NIF
    /// \param wage - manager's wage
    /// \param password - manager's password
    Manager(const std::string& name, const unsigned int & NIF, const float& wage, const std::string & password);
    ///
    /// \return manager's evaluation
    unsigned int getEvaluation() const;
    ///
    /// \param evaluation - manager's new evaluation
    void setEvaluation(const unsigned int &evaluation);
    ///
    /// \return "Manager"
    std::string getType() override;
    ///
    /// \return manager's password
    std::string getPassword();
    ///
    void print() override;
    ///
    /// \param name - manager's name
    /// \param NIF - manager's NIF as string
    /// \param password - manager's password as string
    void managerModify(const std::string& name, const std::string& NIF, const std::string & password);

private:
    /// manager's evaluation: 0 if manager has not been evaluated, else number between 1 and 5 (included)
    unsigned int evaluation;
    /// manager's password
    std::string password;
};

#endif