#include <string>

using namespace std;

class Staff {
public:
    string getName() const;
    string getNIF() const;
    float getWage() const;
    int getyearsOfService() const;
    void setName(const string name);
    void setNIF(const string NIF);
    void setwage(const float wage);
    void setyearsOfService(const int yearsOfService);
private:
    string name;
    string NIF;
    float wage;
    int yearsOfService;
};


class Receptionist : public Staff{
    
    
};

class Responsibles : public Receptionist{
    
    
};

class Cleaning : public Staff{
    
    
};

class Manager : public Staff{
    
    
};