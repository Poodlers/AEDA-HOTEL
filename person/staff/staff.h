#ifndef STAFF_H
#define STAFF_H
#include <string>
#include <vector>
#include "../person.h"

/// Represents a Staff member.
///
/// Defined by a NIF and name by inheritance from Person and wage.
class Staff: public Person {
public:
    /// Staff's constructor.
    ///
    /// \param name  employee's name.
    /// \param NIF  employee's NIF.
    /// \param wage  employee's wage.
    Staff(const std::string& name, const unsigned int & NIF, const float& wage);

    /// Returns wage.
    ///
    /// \return employee's wage.
    float getWage() const;

    /// Returns years of service.
    ///
    /// \return employee's years of work.
    int getYearsOfService() const;

    /// Returns staff member type.
    ///
    /// \return "Staff".
    virtual std::string getType();

    /// Changes staff member's wage.
    ///
    /// \param wage  new wage to set for staff member.
    void setWage(const float wage);

    /// Changes staff members' years of service.
    ///
    /// \param yearsOfService  new years of service for staff member.
    void setYearsOfService(const int yearsOfService);

    /// Modifies staff member.
    ///
    /// If any of the parameters are '.' it doesn't modify them
    /// \see Hotel#modifyStaffMember
    /// \param name
    /// \param NIF
    /// \param wage
    void modifyStaffMember(const std::string& name, const std::string& NIF, const std::string& wage);

    /// Prints staff member's info in format:
    ///
    /// type name NIF wage yearsOfService
    void print() override;

    /// Prints staff member's (for console) info in format:
    ///
    /// type name NIF wage yearsOfService
    void printConsole() override;

protected:
    /// employee's wage.
    float wage;
    /// employee's years of work.
    unsigned int yearsOfService;
};

/// Represents a Receptionist.
///
/// Defined by a wage, NIF and name by inheritance from Staff.
class Receptionist : public  Staff{
public:
    /// Receptionist's constructor.
    ///
    /// \param name  receptionist's name.
    /// \param NIF  receptionist's NIF.
    /// \param wage  receptionist's wage
    Receptionist(const std::string& name, const unsigned int & NIF, const float& wage);

    /// Returns the staff type.
    ///
    /// \return "Receptionist".
    std::string getType() override;
};


/// Represents a Responsible.
///
/// Defined by a wage, NIF and name by inheritance from Receptionist and a vector of assigned floors.
class Responsible : public Receptionist{
public:

    /// Responsible's constructor.
    ///
    /// \param name  responsible's name.
    /// \param NIF  responsible's NIF.
    /// \param wage  responsible's wage.
    Responsible(const std::string& name, const unsigned int & NIF, const float& wage);

    /// Assigns floor 'floor' to responsible.
    ///
    /// \param floor  floor to be assigned to the responsible.
    void assignFloor(const unsigned int & floor);

    /// Clears the responsible's assigned floors.
    void clearAssignedFloors();

    /// Returns floors assigned.
    ///
    /// \return floors assigned.
    std::vector<int> getFloorsAssigned() const;

    /// Returns number of floors assigned
    ///
    /// \return number of floors assigned
    int getNumFloorsAssigned() const;

    /// sets floors assigned and number of floors assigned
    ///
    /// \param floorsAssigned  new assigned floors
    void setFloorsAssigned(const std::vector<int> &floorsAssigned);

    /// Returns staff type.
    ///
    /// \return "Responsible".
    std::string getType() override;

    /// Prints responsible info in format:
    ///
    /// type name NIF wage yearsOfService assigned rooms
    void print() override;

    /// Prints responsible info (for console) in format:
    ///
    /// type name NIF wage yearsOfService assigned rooms
    void printConsole() override;

private:
    /// Number of floors being monitored by the responsible
    int numberOfFloorsBeingMonitored;
    /// Vector of floors assigned to the responsible
    std::vector<int> floorsAssigned;
};

/// Represents a Janitor.
///
/// Defined by a wage, NIF and name by inheritance from Staff and shift.
class Janitor : public Staff{
public:
    /// Janitor's constructor.
    ///
    /// \param shift  janitor's shift.
    /// \param name  janitor's name.
    /// \param NIF  janitor's NIF.
    /// \param wage  janitor's wage.
    Janitor(const bool & shift,const std::string& name, const unsigned int & NIF, const float& wage);

    /// Returns the Janitor's shift.
    ///
    /// \return true for day shift, false for night shift.
    bool getShift() const;

    /// sets shift
    ///
    /// \param shift  new shift
    void setShift(const bool &shift);

    /// Returns staff type.
    ///
    /// \return "Janitor".
    std::string getType() override;

    /// Prints the janitor's info in format
    ///
    ///  type name NIF wage yearsOfService (free space) shift
    void print() override;

    /// Prints the janitor's (for console) info in format
    ///
    ///  type name NIF wage yearsOfService (free space) shift
    void printConsole() override;

    /// Modifies janitor.
    ///
    /// if any of the parameters are '.' they are not modified.
    /// \see Hotel#modifieStaffMember
    /// \param name  janitor's name.
    /// \param NIF  janitor's NIF.
    /// \param shift  janitor's shift.
    /// \param wage janitor's wage
    void janitorModify(const std::string& name, const std::string& NIF,const std::string& wage, const std::string& shift);

private:
    /// true for day, false for night.
    bool shift;
};

/// Represents a manager.
///
/// Defined by a wage, NIF and name by inheritance from staff, evaluation and password.
class Manager : public Staff{
public:
    /// Manager's constructor.
    ///
    /// \param name  manager's name.
    /// \param NIF  manager's NIF.
    /// \param wage  manager's wage.
    /// \param password  manager's password.
    Manager(const std::string& name, const unsigned int & NIF, const float& wage, const std::string & password, const unsigned int & evaluation);

    /// Returns manager's evaluation.
    ///
    /// \return manager's evaluation.
    unsigned int getEvaluation() const;

    /// Returns staff type.
    ///
    /// \return "Manager".
    std::string getType() override;

    /// Returns managers' password.
    ///
    /// \return manager's password.
    std::string getPassword();

    /// sets evaluation
    ///
    /// \param evaluation  new evaluation
    void setEvaluation(const unsigned int &evaluation);

    /// sets password
    ///
    /// \param password  new password
    void setPassword(const std::string &password);

    /// Prints the manager info in format:
    ///
    /// type name NIF wage yearsOfService (free space) (free space) evaluation
    void print() override;

    /// Prints the manager (for console) info in format:
    ///
    /// type name NIF wage yearsOfService (free space) (free space) evaluation
    void printConsole() override;

    /// Modifies manager.
    ///
    /// if any of the parameters are '.' they are not modified.
    /// \see Hotel#modifieStaffMember
    /// \param name  manager's name.
    /// \param NIF  manager's NIF as string.
    /// \param password  manager's password as string.
    /// \param evaluation manager's evaluation.
    /// \param wage manager's wage.
    void managerModify(const std::string& name, const std::string& NIF, const std::string& wage,const std::string & password, const std::string& evaluation);

private:
    /// Manager's evaluation: 0 if manager has not been evaluated, else number between 1 and 5 (included)
    unsigned int evaluation;
    /// Manager's password
    std::string password;
};

#endif