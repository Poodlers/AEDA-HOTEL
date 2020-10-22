#include <string>
#include <vector>
using namespace std;

typedef struct Date{
    int year;
    int month;
    int day;

};


struct Reservation{
    int reservationSize; 
    Date checkIn;
    Date checkOut;
    int roomId;
};

class Client{
    public:
        void setReservation();
    private:
        string name;
        string NIF;
        vector<Reservation*> reservation;
};