#include <string>

using namespace std;

class Staff {
public:
    string getName() const;
    string getNIF() const;
    float getWage() const;
    int getyearsOfService() const;
    void setName(const string name) const;
    void setNIF(const string NIF) const;
    void setwage(const string name) const;
    void setyearsOfService(const string name) const;
private:
    string name;
    string NIF;
    float wage;
    int yearsOfService;
};


class Receptionist : public Staff(){
    
    
}

class Responsibles : public Receptionist(){
    
    
}

class Cleaning : public Staff(){
    
    
}

class Manager : public Staff(){
    
    
}