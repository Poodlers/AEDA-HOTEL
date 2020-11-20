#ifndef STAFF_H
#define STAFF_H
#include <string>
#include <vector>
#include "../person.h"

/// Represents a staff member
///
/// Defined by a wage, NIF and name
class Staff: public Person {
public:
    /// Staff's constructor
    ///
    /// \param name - employee's name
    /// \param NIF - employee's NIF
    /// \param wage - employee's wage
    Staff(const std::string& name, const unsigned int & NIF, const float& wage);

    /// Returns the wage
    ///
    /// \return employee's wage
    float getWage() const;

    /// Returns the years of service
    ///
    /// \return employee's years of work
    int getYearsOfService() const;

    /// Returns the staff type
    ///
    /// \return "staff"
    virtual std::string getType();

    /// Changes the staff's wage
    ///
    /// \param wage  new wage to set for staff member
    void setWage(const float wage);

    /// Changes the staff's years of service
    ///
    /// \param yearsOfService  years of service to set for staff member
    void setYearsOfService(const int yearsOfService);

    /// Prints the staff member's info
    ///
    virtual void printConsole();

    /// Modifies a staff member
    ///
    /// If any of the parameters are '.' it doesn't modify them
    /// \see Hotel#modifyStaffMember
    /// \param name
    /// \param NIF
    /// \param wage
    void modifyStaffMember(const std::string& name, const std::string& NIF, const std::string& wage);

protected:
    /// employee's wage
    float wage;
    /// employee's years of work
    unsigned int yearsOfService;
};

/// Represents a receptionist member
///
/// Defined by a wage, NIF and name
class Receptionist : public  Staff{
public:
    /// Receptionist's constructor
    ///
    /// \param name  receptionist's name
    /// \param NIF  receptionist's NIF
    /// \param wage  receptionist's wage
    Receptionist(const std::string& name, const unsigned int & NIF, const float& wage);

    /// Returns the staff type
    ///
    /// \return "Receptionist"
    std::string getType() override;
};


/// Represents a responsible
///
/// Defined by a wage, NIF, name and list of assigned floors
class Responsible : public Receptionist{
public:

    /// Responsible's constructor
    ///
    /// \param name  responsible's name
    /// \param NIF  responsible's NIF
    /// \param wage  responsible's wage
    Responsible(const std::string& name, const unsigned int & NIF, const float& wage);

    /// Assigns floor 'floor' to responsible
    ///
    /// \param floor  floor to be assigned to the responsible
    void assignFloor(const unsigned int & floor);

    /// Clears the responsible's assigned floors
    void clearAssignedFloors();

    /// Returns the number of floors being monitored
    ///
    /// \return number of floors being monitored by the responsible
    int getNumberOfFloorsBringMonitored() const;

    /// Returns the vector of the floors assigned
    ///
    /// \return vector of floors assigned to the responsible
    std::vector<int> getFloorsAssigned() const;

    /// Returns staff type
    ///
    /// \return "Responsible"
    std::string getType() override;

    /// Prints staff info
    void printConsole() override;

    /// Prints assigned floors
    void printFloors();

private:
    /// number of floors being monitored by the floor monitor
    int numberOfFloorsBeingMonitored;
    /// vector of floors assigned to the floor monitor
    std::vector<int> floorsAssigned;
};

/// Represents a janitor
///
/// Defined by a wage, NIF, name and shift
class Janitor : public Staff{
public:
    /// Janitor's constructor
    ///
    /// \param shift  janitor's shift
    /// \param name  janitor's name
    /// \param NIF  janitor's NIF
    /// \param wage  janitor's wage
    Janitor(const bool & shift,const std::string& name, const unsigned int & NIF, const float& wage);

    /// Returns the Janitor's shift
    ///
    /// \return true for day shift, false for night shift
    bool getShift() const;

    /// Changes the Janitor's shift to 'shift'
    ///
    /// \param shift  janitor's new shift
    void setShift(const bool& shift);

    /// Returns staff type
    ///
    /// \return "Janitor"
    std::string getType() override;

    /// Prints the Janitor's info
    void printConsole() override;

    /// Modifies the janitor
    ///
    /// if any of the parameters are '.' they are not modified
    /// \see Hotel#modifieStaffMember
    /// \param name  janitor's name
    /// \param NIF  janitor's NIF as string
    /// \param shift  janitor's shift
    void janitorModify(const std::string& name, const std::string& NIF,const std::string& wage, const std::string& shift);

private:
    /// true for day, false for night
    bool shift;
};

/// Represents a manager
///
/// Defined by a wage, NIF, name, evaluation and password
class Manager : public Staff{
public:
    /// Manager's constructor
    ///
    /// \param name  manager's name
    /// \param NIF  manager's NIF
    /// \param wage  manager's wage
    /// \param password  manager's password
    Manager(const std::string& name, const unsigned int & NIF, const float& wage, const std::string & password, const unsigned int & evaluation);

    /// Returns the manager's evaluation
    ///
    /// \return manager's evaluation
    unsigned int getEvaluation() const;

    /// Changes the manager's evaluation
    ///
    /// \param evaluation  manager's new evaluation
    void setEvaluation(const unsigned int &evaluation);

    /// Returns staff type
    ///
    /// \return "Manager"
    std::string getType() override;

    /// Returns the managers' password
    ///
    /// \return manager's password
    std::string getPassword();

    /// Prints the manager info
    void printConsole() override;

    /// Modifies the manger
    ///
    /// if any of the parameters are '.' they are not modified
    /// \see Hotel#modifieStaffMember
    /// \param name - manager's name
    /// \param NIF - manager's NIF as string
    /// \param password - manager's password as string
    void managerModify(const std::string& name, const std::string& NIF, const std::string& wage,const std::string & password, const std::string& evalution);

private:
    /// manager's evaluation: 0 if manager has not been evaluated, else number between 1 and 5 (included)
    unsigned int evaluation;
    /// manager's password
    std::string password;
};

#endif