#include <string>

using namespace std;

class Room{
    public:

    private:
    int floor;
    int roomNumber;
    int capacity;
    int pricePerNight;
};

class Suite: public Room{

};

class ViewRoom: public Room{

};

class NoViewRoom: public Room{
    
};