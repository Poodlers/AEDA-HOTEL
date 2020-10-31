#ifndef STAFF_H
#define STAFF_H
#include <string>
#include <vector>

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
    Manager(const std::string& name, const unsigned int & NIF, const float& wage, const std::string & password);
    unsigned int getEvaluation() const;
    void setEvaluation(const unsigned int &evaluation);
private:
    unsigned int evaluation; //0 if manager has not been evaluated, 1 to 5 they have been evaluated
    std::string password;
};

class RoomAlreadyExists{
private:
    unsigned int roomNumber;
    unsigned int roomId;
public:
    RoomAlreadyExists(const unsigned int &roomNumber, const unsigned int &roomId){
        this->roomNumber = roomNumber;
        this->roomId = roomId;
    }
    unsigned int getRoomNumber() const {return this->roomNumber;}
    unsigned int getRoomId() const {return this-> roomId;}
};

class RoomWithThisRoomIdAlreadyExists{
private:
    unsigned int roomNumber;
    unsigned int roomId;
public:
    RoomWithThisRoomIdAlreadyExists(const unsigned int &roomNumber, const unsigned int &roomId){
        this->roomNumber = roomNumber;
        this->roomId = roomId;
    }
    unsigned int getRoomNumber() const {return this->roomNumber;}
    unsigned int getRoomId() const {return this-> roomId;}
};

#endif